#ifndef POWERROOMWIDGETPRIVATE_H
#define POWERROOMWIDGETPRIVATE_H

#include <QObject>

#include <snapshotstorage.h>
#include <AbstractEventLogElement.h>

namespace Ui {
class PowerRoomWidget;
}

class PowerRoomWidgetPrivate : public QObject
{
    Q_OBJECT
public:
    explicit PowerRoomWidgetPrivate(QWidget *parent = 0);
    virtual ~PowerRoomWidgetPrivate();

signals:
    void mainPowerChanged(bool isPowerOn);

private slots:
    void setSnapshot(const Snapshot& snapshot);

    void powerStateChanged(bool isPoweron);

private:
    Ui::PowerRoomWidget *ui;
    SnapshotStorage::Pointer m_storage;

    friend class PowerRoomWidget;
};

#endif // POWERROOMWIDGETPRIVATE_H
