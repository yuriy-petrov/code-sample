#include "equipmentroomwidget.h"
#include "ui_equipmentroomwidget.h"
#include "equipmentroomwidgetprivate.h"

EquipmentRoomWidget::EquipmentRoomWidget(QWidget *parent) :
    QWidget(parent),
    m_private(new EquipmentRoomWidgetPrivate(this))
{
    connect(m_private, SIGNAL(eventLogGenerated(AbstractEventLogElement*)),
            SIGNAL(eventLogGenerated(AbstractEventLogElement*)));
}

EquipmentRoomWidget::~EquipmentRoomWidget()
{
}

void EquipmentRoomWidget::setSnapshotStorage(SnapshotStorage::Pointer storage)
{
    m_private->m_storage = storage;

    m_private->update(storage->snapshot());

    connect(m_private->m_storage.data(), SIGNAL(changed(Snapshot)),
            m_private, SLOT(update(Snapshot)));
}
