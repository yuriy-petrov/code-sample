#ifndef KOSTYPES_H
#define KOSTYPES_H

#include <QMetaType>
#include <QDataStream>

namespace KosTypes
{
    enum HorizontalAlignment
    {
        Left = 0,
        HCenter = 1,
        Right = 2
    };

    enum VerticalAlignment
    {
        Top = 0,
        VCenter = 1,
        Bottom = 2
    };

    enum SubstanceType
    {
        Invalid = -1,
        Nothing = 0,
        Oxygen = 1,
        Hydrogen = 2,
        Nitrogen = 3,
        Water = 4,
        Alkali = 5
    };

    enum ValveType
    {
        NonReturnValve = 0,
        BallValve = 1,
        NeedleValve = 2,
        PneumaticValve = 3,
        Way3Valve = 4,
        Way4Valve = 5,
        SafetyReliefValve = 6,
        MagneticValve = 7,
        HandValve = 8,
        PressureControlValve = 9,
        BackPressureRegulator = 10,
        DirectionBallValve = 11,
        DirectionHandValve = 12,
        Valve = 13,
        DirectionMagneticValve = 14
    };

    enum BasicElementType
    {
        Pump = 0,
        Flexible = 1,
        ConnectedToPLC = 2,
        Motorized = 3,
        InterConnectionPoint = 4,
        DeoxoDehydro = 5,
        HeatExchanger = 6,
        RotaflowIndicator = 7,
        SampleConditioning = 8,
        Filter = 9,
        MoistureSeparator = 10,
        Heating = 11,
        CoalescentFilter = 12,
        CellStack = 13,
        Rinser = 14,
        Receiver = 15,
        Manometer = 16
    };

    enum LevelElementType
    {
        WaterLock = 0,
        GasSeparator = 1
    };

    enum PipelineState
    {
        Normal = 0,
        Corked = 1,
        Teared = 2
    };
}

Q_DECLARE_METATYPE( KosTypes::SubstanceType )

static QDataStream& operator <<(QDataStream& stream, const KosTypes::SubstanceType v)
{
    quint16 value = static_cast<quint16>(v);
    return stream << value;
}

static QDataStream& operator >>(QDataStream& stream, KosTypes::SubstanceType& v)
{
    quint16 value;
    stream >> value;
    v = static_cast<KosTypes::SubstanceType>(value);
    return stream;
}

#endif // KOSTYPES_H
