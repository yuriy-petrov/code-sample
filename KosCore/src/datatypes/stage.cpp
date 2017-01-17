#include "stage.h"

#include <filedatastorage.h>
#include <log.h>

static const QChar VALUES_SEPARATOR(',');

using namespace Player;

Player::Stage::Stage()
{
}

Stage::Stage(Model::HystatMode::Type mode, const QString &dataPath)
    : m_mode(mode)
    , m_dataPath(dataPath)
{
}

void Player::Stage::setName(const QString &name)
{
    m_name = name;
}

void Player::Stage::setDataPath(const QString &path)
{
    m_dataPath = path;
}

void Stage::setMode(Model::HystatMode::Type mode)
{
    m_mode = mode;
}

void Stage::loadData()
{
    if(m_dataPath.isEmpty()) {
        return;
    }

    FileDataStorage storage;
    storage.setDbPath(m_dataPath);

    m_data = QSharedPointer<QList<Snapshot> >(new QList<Snapshot>(storage.load()));
}

QString Stage::toString() const
{
    QStringList list = QStringList()
            << QString::number(static_cast<int>(m_mode))
            << m_name
            << m_dataPath;
    return list.join(VALUES_SEPARATOR);
}

Stage Stage::fromString(const QString &string)
{
    Stage v;
    QStringList values = string.split(VALUES_SEPARATOR, QString::KeepEmptyParts);

    if(values.size() == 3) {
        v.setMode(static_cast<Model::HystatMode::Type>(values.at(0).toInt()));
        v.setName(values.at(1));
        v.setDataPath(values.at(2));
    }

    return v;
}

QDataStream &Stage::operator >>(QDataStream &stream) const
{
    return stream
            << m_mode
            << m_name
            << m_dataPath;
}

QDataStream &Stage::operator <<(QDataStream &stream)
{
    return stream
            >> m_mode
            >> m_name
            >> m_dataPath;
}

QDebug &Stage::operator >>(QDebug &debug) const
{
    return debug << toString();
}
