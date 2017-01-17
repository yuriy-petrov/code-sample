#ifndef MODELTYPESEXTRACTOR_H
#define MODELTYPESEXTRACTOR_H

#include <snapshot.h>
#include <modeltypes.h>

namespace Model {

    class TypesExtractor
    {
    public:

        TypesExtractor(const Snapshot& snapshot)
            : m_snapshot(snapshot)
        {}

        inline qint64 simulationTime() const;

        inline bool condition(const Snapshot::Key& key) const;
        inline double value(const Snapshot::Key& key) const;
        inline Separator separator(const Snapshot::Key& key) const;
        inline Separator waterLock(const Snapshot::Key& key) const;
        inline Valve valve(const Snapshot::Key& key) const;
        inline Pipe pipe(const Snapshot::Key& key) const;
        inline HeatExchanger heatExchanger(const Snapshot::Key& key) const;
        inline Rinser rinser(const Snapshot::Key& key) const;
        inline CoalescentFilter coalescentFilter(const Snapshot::Key& key) const;

    private:

        const Snapshot& m_snapshot;
    };

    qint64 TypesExtractor::simulationTime() const
    {
        return m_snapshot.simulationTime_msec();
    }

    bool TypesExtractor::condition(const Snapshot::Key &key) const
    {
        return m_snapshot.value(key).toBool();
    }

    double TypesExtractor::value(const Snapshot::Key &key) const
    {
        return m_snapshot.value(key).toDouble();
    }

    Separator TypesExtractor::separator(const Snapshot::Key &key) const
    {
        return m_snapshot.value(key).value<Separator>();
    }

    Separator TypesExtractor::waterLock(const Snapshot::Key &key) const
    {
        return separator(key);
    }

    Valve TypesExtractor::valve(const Snapshot::Key &key) const
    {
        return m_snapshot.value(key).value<Valve>();
    }

    Pipe TypesExtractor::pipe(const Snapshot::Key &key) const
    {
        return m_snapshot.value(key).value<Pipe>();
    }

    HeatExchanger TypesExtractor::heatExchanger(const Snapshot::Key &key) const
    {
        return m_snapshot.value(key).value<HeatExchanger>();
    }

    Rinser TypesExtractor::rinser(const Snapshot::Key &key) const
    {
        return m_snapshot.value(key).value<Rinser>();
    }

    CoalescentFilter TypesExtractor::coalescentFilter(const Snapshot::Key &key) const
    {
        return m_snapshot.value(key).value<CoalescentFilter>();
    }

}

#endif // MODELTYPESEXTRACTOR_H
