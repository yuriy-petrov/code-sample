#ifndef STAGES_H
#define STAGES_H

#include <QMap>
#include <stage.h>

namespace Player
{

class Stages : public QMap<Model::HystatMode::Type, Stage>
{
public:
    Stages()
        : QMap<Model::HystatMode::Type, Stage>()
    {}

    virtual ~Stages()
    {}

    QString toString() const;
    static Stages fromString(const QString& string);

    QJsonValue toJsonValue() const;
    static Stages fromJsonValue(const QJsonValue& value);

    QDataStream& operator >>(QDataStream& stream) const;
    QDataStream& operator <<(QDataStream& stream);

    QDebug& operator >>(QDebug& debug) const;
};

inline QDataStream& operator <<(QDataStream& stream, const Stages& v)
{
    return v >> stream;
}

inline QDataStream& operator >>(QDataStream& stream, Stages& v)
{
    return v << stream;
}

inline QDebug& operator <<(QDebug debug, const Stages& v)
{
    return v >> debug;
}

}

Q_DECLARE_METATYPE( Player::Stages )

#endif // STAGES_H
