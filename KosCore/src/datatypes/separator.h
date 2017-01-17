#ifndef SEPARATOR_H
#define SEPARATOR_H

#include <QMetaType>
#include <QDataStream>
#include <QDebug>

#include <KosTypes.h>

namespace Model
{

    class Separator
    {
    public:
        Separator()
        {}

        Separator(KosTypes::SubstanceType fluid,
                  KosTypes::SubstanceType gas,
                  int fluidLevel)
            : m_FluidSubstance(fluid)
            , m_GasSubstance(gas)
            , m_FluidLevel(fluidLevel)
        {}

        inline KosTypes::SubstanceType fluid() const;
        void setFluid(KosTypes::SubstanceType substance);

        inline KosTypes::SubstanceType gas() const;
        void setGas(KosTypes::SubstanceType substance);

        inline int fluidLevel() const;
        void setFluidLevel(int value);

    public:
        inline QVariant toVariant() const;

        QDataStream& operator <<(QDataStream& stream);
        QDataStream& operator >>(QDataStream& stream) const;
        QDebug& operator >>(QDebug& debug) const;

    private:
        KosTypes::SubstanceType m_FluidSubstance;
        KosTypes::SubstanceType m_GasSubstance;
        int m_FluidLevel;
    };

    KosTypes::SubstanceType Separator::fluid() const
    {
        return m_FluidSubstance;
    }

    KosTypes::SubstanceType Separator::gas() const
    {
        return m_GasSubstance;
    }

    int Separator::fluidLevel() const
    {
        return m_FluidLevel;
    }

    QVariant Separator::toVariant() const
    {
        return QVariant::fromValue<Model::Separator>(*this);
    }

}

Q_DECLARE_METATYPE( Model::Separator )

static QDataStream& operator <<(QDataStream& stream, const Model::Separator v)
{
    return v >> stream;
}

static QDataStream& operator >>(QDataStream& stream, Model::Separator& v)
{
    return v << stream;
}

static QDebug& operator <<(QDebug& debug, const Model::Separator& v)
{
    return v >> debug;
}

#endif // SEPARATOR_H
