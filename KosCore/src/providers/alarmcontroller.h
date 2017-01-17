#ifndef ALARMCONTROLLER_H
#define ALARMCONTROLLER_H

#include <QObject>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QPainter>
#include <snapshotstorage.h>
#include <SettingsStorage.h>

class QMediaPlayer;

class AlarmController : public QObject
{
    Q_OBJECT
public:
    explicit AlarmController(QObject *parent = 0);

    void setSnapshotStorage(SnapshotStorage::Pointer storage);

    void loadConfig(SettingsStorage * storage);

    void setEmergencyLightWidget(QWidget * widget);

protected:

    bool eventFilter(QObject *o, QEvent *e);
    void drawEmergencyLight(QPainter * painter, const QPaintEvent * event);
    void startAlarmTimer();
    void stopAlarmTimer();

private slots:

    void snapshotChanged(const Snapshot& snapshot);

private:

    void timerEvent(QTimerEvent * e);

private:
    SnapshotStorage::Pointer m_snapshotStorage;
    QMediaPlayer * m_player;
    QString m_sound;
    QWidget * m_emergencyLightWidget;
    int m_alarmTimerId;
    bool m_isAlarm;
    bool m_alarmState;
};

#endif // ALARMCONTROLLER_H
