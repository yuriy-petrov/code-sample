#ifndef VALVE_H
#define VALVE_H

#include <QMetaType>
#include <QDataStream>
#include <QDebug>

#include <KosTypes.h>

namespace Model
{
    class Valve
    {
    public:
        enum Status {
            Normal,
            Faulted
        };

    public:
        Valve()
            : m_ClosingLevel(100)
            , m_Status(Normal)
            , m_SubstanceType(KosTypes::Nothing)
        {}

        static Valve opened(KosTypes::SubstanceType substance)
        {
            Valve v;
            v.setSubstanceType(substance);
            v.open();
            return v;
        }

        static Valve closed(KosTypes::SubstanceType substance)
        {
            Valve v;
            v.setSubstanceType(substance);
            v.close();
            return v;
        }

        inline bool isOpen() const
        { return m_ClosingLevel != 100; }

        void open()
        { m_ClosingLevel = 0; }

        void close()
        { m_ClosingLevel = 100; }

        inline int closingLevel() const
        { return m_ClosingLevel; }

        void setClosingLevel(int value)
        { m_ClosingLevel = qBound(0, value, 100); }

        inline bool isBroken() const
        { return m_Status != Model::Valve::Normal; }

        inline Status status() const
        { return m_Status; }

        void setStatus(Status value)
        { m_Status = value; }

        inline KosTypes::SubstanceType substanceType() const
        { return m_SubstanceType; }

        void setSubstanceType(KosTypes::SubstanceType value)
        { m_SubstanceType =  value; }

        QVariant toVariant() const
        { return QVariant::fromValue<Model::Valve>(*this); }

    public:
        inline QDataStream& operator <<(QDataStream& stream)
        {
            int status;
            int substance;
            stream
                    >> m_ClosingLevel
                    >> status
                    >> substance;
            m_Status = static_cast<Valve::Status>(status);
            m_SubstanceType = static_cast<KosTypes::SubstanceType>(substance);
            return stream;
        }

        inline QDataStream& operator >>(QDataStream& stream) const
        {
            return stream
                    << m_ClosingLevel
                    << (int)m_Status
                    << (int)m_SubstanceType;
        }

        QDebug& operator >>(QDebug& debug) const
        {
            debug.nospace()
                    << (isOpen() ? "OPENED " : "CLOSED ")
                    << "(" << closingLevel() << "%) "
                    << (status() == Faulted ? "FAULTED" : "")
                       ;
            return debug.space();
        }

    private:
        int m_ClosingLevel;
        Status m_Status;
        KosTypes::SubstanceType m_SubstanceType;
    };
}

Q_DECLARE_METATYPE( Model::Valve )

static QDataStream& operator <<(QDataStream& stream, const Model::Valve v)
{
    return v >> stream;
}

static QDataStream& operator >>(QDataStream& stream, Model::Valve& v)
{
    return v << stream;
}

static QDebug& operator <<(QDebug& debug, const Model::Valve& v)
{
    return v >> debug;
}

#endif // VALVE_H
