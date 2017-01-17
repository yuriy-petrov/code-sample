#ifndef STAGE_H
#define STAGE_H

#include <QMap>
#include <QString>
#include <QSharedPointer>

#include <modeltypes.h>
#include <snapshot.h>

namespace Player
{

class Stage
{
public:
    Stage();
    Stage(Model::HystatMode::Type mode, const QString& dataPath);

    ~Stage()
    {}

    inline const QString& name() const;
    void setName(const QString& name);

    inline const QString& dataPath() const;
    void setDataPath(const QString& path);

    inline Model::HystatMode::Type mode() const;
    void setMode(Model::HystatMode::Type mode);

    inline const QList<Snapshot>& data() const;

    inline bool isLoaded() const;

    void loadData();

public:
    QString toString() const;
    static Stage fromString(const QString& string);

    QDataStream& operator >>(QDataStream& stream) const;
    QDataStream& operator <<(QDataStream& stream);

    QDebug& operator >>(QDebug& debug) const;

private:
    QString m_name;
    QString m_dataPath;
    Model::HystatMode::Type m_mode;
    QSharedPointer<QList<Snapshot> > m_data;
};

const QString &Stage::name() const
{
    return m_name;
}

const QString &Stage::dataPath() const
{
    return m_dataPath;
}

Model::HystatMode::Type Stage::mode() const
{
    return m_mode;
}

const QList<Snapshot> &Stage::data() const
{
    return *m_data.data();
}

bool Stage::isLoaded() const
{
    return !m_data.isNull();
}

inline QDataStream& operator <<(QDataStream& stream, const Stage& v)
{
    return v >> stream;
}

inline QDataStream& operator >>(QDataStream& stream, Stage& v)
{
    return v << stream;
}

inline QDebug& operator <<(QDebug debug, const Stage& v)
{
    return v >> debug;
}

} // namespace Player

#endif // STAGE_H
