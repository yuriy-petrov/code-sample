#include "separator.h"

void Model::Separator::setFluid(KosTypes::SubstanceType substance)
{
    m_FluidSubstance = substance;
}

void Model::Separator::setGas(KosTypes::SubstanceType substance)
{
    m_GasSubstance = substance;
}

void Model::Separator::setFluidLevel(int value)
{
    m_FluidLevel = value;
}

QDataStream &Model::Separator::operator <<(QDataStream &stream)
{
    return stream
            >> m_FluidSubstance
            >> m_GasSubstance
            >> m_FluidLevel;
}

QDataStream &Model::Separator::operator >>(QDataStream &stream) const
{
    return stream
            << m_FluidSubstance
            << m_GasSubstance
            << m_FluidLevel;
}

QDebug &Model::Separator::operator >>(QDebug &debug) const
{
    return debug << "Separator( Level:" << m_FluidLevel
                 << "Fluid:" << m_FluidSubstance
                 << "Gas:" << m_GasSubstance << ")";
}
