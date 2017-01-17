#include "KosTypesHelper.h"

extern KosTypesHelper * KosTypesHelper::m_instance = NULL;

KosTypesHelper * KosTypesHelper::instance()
{
    if (m_instance == NULL)
    {
        m_instance = new KosTypesHelper();
    }

    return m_instance;
}

QHash<KosTypes::SubstanceType, QString> KosTypesHelper::substanceTypeTitles() const
{
    return m_substanceTypeTitles;
}

QHash<KosTypes::ValveType, QString> KosTypesHelper::valveTypeTitles() const
{
    return m_valveTypeTitles;
}

QHash<KosTypes::BasicElementType, QString> KosTypesHelper::basicElementTypeTitles() const
{
    return m_basicElementTypeTitles;
}

QHash<KosTypes::PipelineState, QString> KosTypesHelper::pipelineStateTitles() const
{
    return m_pipelineStateTitles;
}

QHash<KosTypes::LevelElementType, QString> KosTypesHelper::levelElementTypeTitles() const
{
    return m_levelElementTypeTitles;
}

QHash<KosTypes::SubstanceType, QColor> KosTypesHelper::substanceTypeColors() const
{
    return m_substanceTypeColors;
}

KosTypesHelper::KosTypesHelper() :
    QObject()
{
    m_substanceTypeTitles.insert(KosTypes::Nothing, tr("Nothing"));
    m_substanceTypeTitles.insert(KosTypes::Oxygen, tr("Oxygen"));
    m_substanceTypeTitles.insert(KosTypes::Hydrogen, tr("Hydrogen"));
    m_substanceTypeTitles.insert(KosTypes::Nitrogen, tr("Nitrogen"));
    m_substanceTypeTitles.insert(KosTypes::Water, tr("Water"));
    m_substanceTypeTitles.insert(KosTypes::Alkali, tr("Alkali"));

    m_valveTypeTitles.insert(KosTypes::NonReturnValve, tr("Non return valve"));
    m_valveTypeTitles.insert(KosTypes::DirectionBallValve, tr("Direction ball valve"));
    m_valveTypeTitles.insert(KosTypes::NeedleValve, tr("Needle valve"));
    m_valveTypeTitles.insert(KosTypes::PneumaticValve, tr("Pneumatic valve"));
    m_valveTypeTitles.insert(KosTypes::Way3Valve, tr("3 way valve"));
    m_valveTypeTitles.insert(KosTypes::Way4Valve, tr("4 way valve"));
    m_valveTypeTitles.insert(KosTypes::SafetyReliefValve, tr("Safety relief valve"));
    m_valveTypeTitles.insert(KosTypes::DirectionMagneticValve, tr("Direction magnetic valve"));
    m_valveTypeTitles.insert(KosTypes::DirectionHandValve, tr("Direction hand valve"));
    m_valveTypeTitles.insert(KosTypes::PressureControlValve, tr("Pressure control valve"));
    m_valveTypeTitles.insert(KosTypes::BackPressureRegulator, tr("Back pressure regulator"));
    m_valveTypeTitles.insert(KosTypes::BallValve, tr("Ball valve"));
    m_valveTypeTitles.insert(KosTypes::HandValve, tr("Hand valve"));
    m_valveTypeTitles.insert(KosTypes::Valve, tr("Valve"));

    m_basicElementTypeTitles.insert(KosTypes::Pump, tr("Pump"));
    m_basicElementTypeTitles.insert(KosTypes::Flexible, tr("Flexible"));
    m_basicElementTypeTitles.insert(KosTypes::ConnectedToPLC, tr("Connected to PLC"));
    m_basicElementTypeTitles.insert(KosTypes::Motorized, tr("Motorized"));
    m_basicElementTypeTitles.insert(KosTypes::InterConnectionPoint, tr("Interconnection point"));
    m_basicElementTypeTitles.insert(KosTypes::DeoxoDehydro, tr("Deoxo/Dehydro"));
    m_basicElementTypeTitles.insert(KosTypes::HeatExchanger, tr("Heat exchanger"));
    m_basicElementTypeTitles.insert(KosTypes::RotaflowIndicator, tr("Rotaflow indicator"));
    m_basicElementTypeTitles.insert(KosTypes::SampleConditioning, tr("Sample conditioning"));
    m_basicElementTypeTitles.insert(KosTypes::Filter, tr("Filter"));
    m_basicElementTypeTitles.insert(KosTypes::MoistureSeparator, tr("Moisture separator"));
    m_basicElementTypeTitles.insert(KosTypes::Heating, tr("Heating"));
    m_basicElementTypeTitles.insert(KosTypes::CoalescentFilter, tr("Coalescent filter"));
    m_basicElementTypeTitles.insert(KosTypes::CellStack, tr("Cell stack"));
    m_basicElementTypeTitles.insert(KosTypes::Rinser, tr("Rinser"));
    m_basicElementTypeTitles.insert(KosTypes::Receiver, tr("Receiver"));
    m_basicElementTypeTitles.insert(KosTypes::Manometer, tr("Manometer"));

    m_pipelineStateTitles.insert(KosTypes::PipelineState::Normal, tr("Normal"));
    m_pipelineStateTitles.insert(KosTypes::PipelineState::Corked, tr("Corked"));
    m_pipelineStateTitles.insert(KosTypes::PipelineState::Teared, tr("Teared"));

    m_levelElementTypeTitles.insert(KosTypes::LevelElementType::WaterLock, tr("Water lock"));
    m_levelElementTypeTitles.insert(KosTypes::LevelElementType::GasSeparator, tr("Gas separator"));

    m_substanceTypeColors.insert(KosTypes::Nothing, QColor("white"));
    m_substanceTypeColors.insert(KosTypes::Oxygen, QColor("#3D5AA8"));
    m_substanceTypeColors.insert(KosTypes::Hydrogen, QColor("#F5B918"));
    m_substanceTypeColors.insert(KosTypes::Nitrogen, QColor("gray"));
    m_substanceTypeColors.insert(KosTypes::Water, QColor("#4B9872"));
    m_substanceTypeColors.insert(KosTypes::Alkali, QColor("#92268F"));
}
