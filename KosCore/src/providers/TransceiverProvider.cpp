#include "TransceiverProvider.h"

#include <QTcpSocket>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>

TransceiverProvider::TransceiverProvider(QTcpSocket * tcpSocket,
                                         QObject * parent) :
    QObject(parent),
    m_tcpSocket(tcpSocket),
    m_blockSize(0)
{
    QObject::connect(m_tcpSocket, &QTcpSocket::readyRead,
                     this, &TransceiverProvider::readyRead);
}

void TransceiverProvider::sendMessage(const QJsonObject &jsonObject)
{
    QByteArray data = QJsonDocument(jsonObject).toBinaryData();

    quint32 size = (quint32)data.size();

    char * buffer = new char[sizeof(quint32)];
    memset(buffer, '\0', sizeof(quint32));
    memcpy(buffer, &size, sizeof(quint32));

    QByteArray  block;
    block.append(buffer, sizeof(quint32));
    block.append(data);

    delete [] buffer;

    m_tcpSocket->write(block);
}

void TransceiverProvider::readyRead()
{
    while (true)
    {
        if (m_blockSize == 0)
        {
            if (m_tcpSocket->bytesAvailable() < sizeof(quint32))
            {
                break;
            }

            char * buffer = new char[sizeof(quint32)];
            memset(buffer, '\0', sizeof(quint32));
            m_tcpSocket->read(buffer, sizeof(quint32));
            memcpy(&m_blockSize, buffer, sizeof(quint32));
            delete [] buffer;
        }

        if (m_data.size() < m_blockSize)
        {
            if (m_tcpSocket->bytesAvailable() > 0)
            {
                QByteArray data = m_tcpSocket->read(qMin(m_tcpSocket->bytesAvailable(), (qint64)(m_blockSize - m_data.size())));
                m_data.append(data);
            }
            else
            {
                break;
            }
        }

        if (m_data.size() == m_blockSize)
        {
            QByteArray data = m_data;
            m_blockSize = 0;
            m_data.clear();

            emit receivedMessage(QJsonDocument::fromBinaryData(data).object());
        }
    }
}
