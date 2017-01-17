#ifndef EQUIPMENTROOMWIDGET_H
#define EQUIPMENTROOMWIDGET_H

#include <QWidget>

#include <snapshotstorage.h>
#include <AbstractEventLogElement.h>

class EquipmentRoomWidgetPrivate;

class EquipmentRoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EquipmentRoomWidget(QWidget *parent = 0);
    ~EquipmentRoomWidget();

    void setSnapshotStorage(SnapshotStorage::Pointer storage);

signals:
    void eventLogGenerated(AbstractEventLogElement * eventLogElement);

private:
    EquipmentRoomWidgetPrivate* m_private;
};

#endif // EQUIPMENTROOMWIDGET_H
