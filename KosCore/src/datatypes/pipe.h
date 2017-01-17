#ifndef PIPE_H
#define PIPE_H

#include <QMetaType>
#include <QDataStream>
#include <QDebug>

#include <KosTypes.h>

namespace Model {

    class Pipe
    {
    public:
        Pipe();

        Pipe(KosTypes::SubstanceType substance)
            : m_Substance(substance)
        {}

        inline KosTypes::SubstanceType substance() const;
        void setSubstance(KosTypes::SubstanceType type);

    public:
        inline QVariant toVariant() const;

        QDataStream& operator <<(QDataStream& stream);
        QDataStream& operator >>(QDataStream& stream) const;
        QDebug& operator >>(QDebug& debug) const;

    private:
        KosTypes::SubstanceType m_Substance;
    };

    KosTypes::SubstanceType Pipe::substance() const
    {
        return m_Substance;
    }

    QVariant Pipe::toVariant() const
    {
        return QVariant::fromValue<Model::Pipe>(*this);
    }
}

Q_DECLARE_METATYPE( Model::Pipe )

static QDataStream& operator <<(QDataStream& stream, const Model::Pipe v)
{
    return v >> stream;
}

static QDataStream& operator >>(QDataStream& stream, Model::Pipe& v)
{
    return v << stream;
}

static QDebug& operator <<(QDebug& debug, const Model::Pipe& v)
{
    return v >> debug;
}

#endif // PIPE_H
