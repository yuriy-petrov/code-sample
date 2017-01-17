#include <QMediaPlayer>
#include <QWidget>
#include <QPixmap>

#include <log.h>

#include "alarmcontroller.h"
#include "StringsKeys.h"
#include "ModelTypesExtractor.h"

AlarmController::AlarmController(QObject *parent)
    : QObject(parent)
    , m_player(new QMediaPlayer(this))
    , m_emergencyLightWidget(NULL)
    , m_alarmTimerId(-1)
    , m_isAlarm(false)
    , m_alarmState(false)
{
}

void AlarmController::setSnapshotStorage(SnapshotStorage::Pointer storage)
{
    m_snapshotStorage = storage;
    connect(m_snapshotStorage.data(), &SnapshotStorage::changed,
            this, &AlarmController::snapshotChanged);
}

void AlarmController::loadConfig(SettingsStorage * storage)
{
    m_sound = storage->value(SettingsKeys::ALARM_SOUND).toString();

    if(m_sound.isEmpty()) {
        LOG << "AlARM SOUND IS NOT SET !!!";
    } else if (m_player) {
        m_player->setMedia(QUrl::fromLocalFile(m_sound));
        m_player->setVolume(storage->value(SettingsKeys::ALARM_SOUND_VOLUME).toInt());
    }
}

void AlarmController::setEmergencyLightWidget(QWidget *widget)
{
    m_emergencyLightWidget = widget;
    m_emergencyLightWidget->installEventFilter(this);
}

bool AlarmController::eventFilter(QObject *o, QEvent *e)
{
    if(o == m_emergencyLightWidget) {
        switch(e->type()) {
            case QEvent::Paint:
            {
                if(m_alarmState) {
                    QPainter painter(m_emergencyLightWidget);
                    drawEmergencyLight(&painter, static_cast<QPaintEvent*>(e));
                }
                return false;
            }
        }
    }

    return QObject::eventFilter(o, e);
}

void AlarmController::drawEmergencyLight(QPainter *painter, const QPaintEvent *event)
{
    QPixmap pixmap = QPixmap(":/resources/images/orange-light-alarm-md.png").scaled(QSize(50, 50),
                                                                              Qt::KeepAspectRatio,
                                                                              Qt::SmoothTransformation);

    painter->drawPixmap(event->rect().bottomRight().x() - pixmap.width(),
                        event->rect().bottomRight().y() - pixmap.height(),
                        pixmap);
}

void AlarmController::startAlarmTimer()
{
    if(m_alarmTimerId == -1) {
        m_alarmTimerId = startTimer(1000);
    }

    m_isAlarm = true;
}

void AlarmController::stopAlarmTimer()
{
    if(m_alarmTimerId != -1) {
        killTimer(m_alarmTimerId);
        m_alarmTimerId = -1;
    }

    m_isAlarm = false;
    m_alarmState = false;
}

void AlarmController::snapshotChanged(const Snapshot &snapshot)
{
    Model::TypesExtractor helper(snapshot);

    if(helper.condition(Model::Power::Switch)) {
        if(helper.condition(Model::ALARM)) {
            LOG << "STATE:" << m_player->state();
            if(m_player && m_player->state() != QMediaPlayer::PlayingState) {
                m_player->play();
            }
            startAlarmTimer();
        } else if (m_player) {
            m_player->stop();
            stopAlarmTimer();
        }
    }
}

void AlarmController::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == m_alarmTimerId) {
        if(m_emergencyLightWidget != NULL) {
            m_alarmState = !m_alarmState;
            m_emergencyLightWidget->update();
        }
    }
}
