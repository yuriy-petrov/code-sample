#ifndef MODELTYPES_H
#define MODELTYPES_H

#include <QMetaType>
#include <QDataStream>

#include <valve.h>
#include <pipe.h>
#include <separator.h>

namespace Model {

    namespace HystatMode {
        typedef enum {
            Invalid = -1,
            Error,
            StandbyN2Purge,
            N2Purge,
            StandbyH2Purge,
            H2Purge,
            StandbyH2Production,
            H2ProductionToAtmosphere,
            H2Production,
            Depressurization,
            Depressurized,
            EmergencyDepressurization
        } Type;
    }

    typedef enum  { Off, On } HwSwitchPos;

    typedef Pipe Rinser;
    typedef Pipe HeatExchanger;
    typedef Pipe CoalescentFilter;

} // namespace Model

Q_DECLARE_METATYPE( Model::HystatMode::Type )
Q_DECLARE_METATYPE( Model::HwSwitchPos )

static QDataStream& operator <<(QDataStream& stream, const Model::HystatMode::Type value)
{
    return stream << (int)value;
}

static QDataStream& operator >>(QDataStream& stream, Model::HystatMode::Type& value)
{
    int _value;
    stream >> _value;
    value = static_cast<Model::HystatMode::Type>(_value);
    return stream;
}

static QDataStream& operator <<(QDataStream& stream, const Model::HwSwitchPos value)
{
    return stream << (int)value;
}

static QDataStream& operator >>(QDataStream& stream, Model::HwSwitchPos& value)
{
    int v;
    stream >> v;
    value = static_cast<Model::HwSwitchPos>(v);
    return stream;
}

#endif // MODELTYPES_H
