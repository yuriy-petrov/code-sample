#ifndef MODELPARAMETERS_H
#define MODELPARAMETERS_H

#include <QMap>
#include <QString>
#include <QJsonValue>
#include <QMetaType>
#include <QDebug>

// FIXME : Создать базовый класс для хранения QMap<QString,double>
//         Унаследовать этот и NoiseVariance от него
namespace Model
{
    namespace Parameters
    {
        class Type : public QMap<QString,double>
        {
        public:
            QString toString() const;
            static Model::Parameters::Type fromString(const QString& string);

            QJsonValue toJsonValue() const;
            static Model::Parameters::Type fromJsonValue(const QJsonValue& value);

            QDataStream& operator >>(QDataStream& stream) const;
            QDataStream& operator <<(QDataStream& stream);

            QDebug& operator >>(QDebug& debug) const;
        };
    }
}

Q_DECLARE_METATYPE( Model::Parameters::Type )

inline QDataStream& operator <<(QDataStream& stream, const Model::Parameters::Type& v)
{
    return v >> stream;
}

inline QDataStream& operator >>(QDataStream& stream, Model::Parameters::Type& v)
{
    return v << stream;
}

inline QDebug& operator <<(QDebug debug, const Model::Parameters::Type& v)
{
    return v >> debug;
}

#endif // MODELPARAMETERS_H
