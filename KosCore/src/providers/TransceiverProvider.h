#ifndef TRANSCEIVERPROVIDER_H
#define TRANSCEIVERPROVIDER_H

class QTcpSocket;

#include <QObject>

class TransceiverProvider : public QObject
{

    Q_OBJECT

public:

    TransceiverProvider(QTcpSocket * tcpSocket,
                        QObject * parent = 0);

    void sendMessage(const QJsonObject & jsonObject);

signals:

    void receivedMessage(const QJsonObject & jsonObject);

private slots:

    void readyRead();

private:

    QTcpSocket * m_tcpSocket;

    quint32 m_blockSize;
    QByteArray m_data;

};

#endif // TRANSCEIVERPROVIDER_H
