#ifndef SCHEMESNAPSHOTCONTROLLERPRIVATE_H
#define SCHEMESNAPSHOTCONTROLLERPRIVATE_H

#include <snapshot.h>
#include <GroupSchemeSceneManager.h>

#include <QObject>

class SchemeSnapshotControllerPrivate : public QObject
{

    Q_OBJECT

    friend class SchemeSnapshotController;

public:

    explicit SchemeSnapshotControllerPrivate(QObject * parent = 0);

    void updateScheme();

private:

    void updateValves();
    void updatePipes();
    void updateSeparators(const QStringList& keys);
    void updateWaterLocks();
    void updateCoalescentFilters();
    void updateRinsers();
    void updateHeatExchangers();
    void updateManometers();

private:

    GroupSchemeSceneManager * m_groupSchemeSceneManager;

    Snapshot m_snapshot;

};

#endif // SCHEMESNAPSHOTCONTROLLERPRIVATE_H
