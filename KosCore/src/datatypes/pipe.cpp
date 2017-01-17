#include "pipe.h"


Model::Pipe::Pipe()
    : m_Substance(KosTypes::Nothing)
{

}

void Model::Pipe::setSubstance(KosTypes::SubstanceType type)
{
    m_Substance = type;
}

QDataStream &Model::Pipe::operator <<(QDataStream &stream)
{
    int substance;
    stream
            >> substance;
    m_Substance = static_cast<KosTypes::SubstanceType>(substance);
    return stream;
}

QDataStream &Model::Pipe::operator >>(QDataStream &stream) const
{
    return stream
            << (int)m_Substance;
}

QDebug &Model::Pipe::operator >>(QDebug &debug) const
{
    return debug << "Pipe(" << m_Substance <<")";
}
