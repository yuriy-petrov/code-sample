#ifndef POWERROOMWIDGET_H
#define POWERROOMWIDGET_H

#include <QWidget>

#include <snapshotstorage.h>
#include <AbstractEventLogElement.h>

class PowerRoomWidgetPrivate;


class PowerRoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PowerRoomWidget(QWidget *parent = 0);
    ~PowerRoomWidget();

    void setSnapshotStorage(SnapshotStorage::Pointer storage);

    void initMainPower(bool isPowerOn);

    QWidget* cimrexUI() const;

signals:
    void mainPowerChanged(bool isPowerOn);
    void eventLogGenerated(AbstractEventLogElement * eventLogElement);

private:
    PowerRoomWidgetPrivate* m_private;
};

#endif // POWERROOMWIDGET_H
