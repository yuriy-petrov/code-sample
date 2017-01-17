#include "powerroomwidget.h"
#include "powerroomwidgetprivate.h"
#include "ui_powerroomwidget.h"

#include <StringsKeys.h>

PowerRoomWidget::PowerRoomWidget(QWidget *parent) :
    QWidget(parent),
    m_private(new PowerRoomWidgetPrivate(this))
{
    connect(m_private, &PowerRoomWidgetPrivate::mainPowerChanged,
            this, &PowerRoomWidget::mainPowerChanged);
}

PowerRoomWidget::~PowerRoomWidget()
{

}

void PowerRoomWidget::setSnapshotStorage(SnapshotStorage::Pointer storage)
{
    m_private->m_storage = storage;

    // устанавливаем начальное значение выключателя питания
    initMainPower(storage->snapshot().value(Model::Power::Switch).toBool());

    connect(m_private->m_storage.data(), SIGNAL(changed(Snapshot)),
            m_private, SLOT(setSnapshot(Snapshot)));
}

void PowerRoomWidget::initMainPower(bool isPowerOn)
{
    isPowerOn ?
                m_private->ui->wPowerSwitch->powerOn() :
                m_private->ui->wPowerSwitch->powerOff();
}

QWidget *PowerRoomWidget::cimrexUI() const
{
    return m_private->ui->CimrexWidget;
}
