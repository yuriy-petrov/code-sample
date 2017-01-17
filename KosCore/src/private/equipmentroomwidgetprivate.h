#ifndef EQUIPMENTROOMWIDGETPRIVATE_H
#define EQUIPMENTROOMWIDGETPRIVATE_H

#include <QObject>
#include <QPainter>

#include <snapshotstorage.h>
#include <AbstractEventLogElement.h>
#include <StringsKeys.h>
#include <modeltypes.h>

namespace Ui {
class EquipmentRoomWidget;
}

class EquipmentRoomWidgetPrivate : public QObject
{
    Q_OBJECT
public:
    explicit EquipmentRoomWidgetPrivate(QWidget *parent = 0);
    virtual ~EquipmentRoomWidgetPrivate();

    bool eventFilter(QObject *o, QEvent *e);

signals:
    void eventLogGenerated(AbstractEventLogElement * eventLogElement);

private:
    void drawNVerticalPipesMount(QPainter& painter, const QRect& rect, int count);
    void drawNVerticalPipes(QPainter& painter, const QRect& rect, int count);
    void drawPipesBottom(QPainter& painter, const QRect& rect);
    void drawMagneticValve(QPainter& painter, const QRect& rect);

private slots:
    void update(const Snapshot& snapshot);

    void bv_n1_changed(int closurePercent, bool isFinal);
    void bv_n3_changed(int closurePercent, bool isFinal);
    void hv_n_changed(int closurePercent, bool isFinal);

private:
    void sendValveToLog(const QString& key, const Model::Valve& valve, bool stateChanged);

private:
    Ui::EquipmentRoomWidget *ui;
    SnapshotStorage::Pointer m_storage;

    bool m_IsBV_N1adjustement;
    bool m_IsBV_N3adjustement;
    bool m_IsHV_Nadjustement;

    friend class EquipmentRoomWidget;
};

#endif // EQUIPMENTROOMWIDGETPRIVATE_H
