#ifndef EVENTFILTERPROVIDERWIDGET_H
#define EVENTFILTERPROVIDERWIDGET_H

class EventFilterProvider;
class StageEventFilterModel;
class BlockEventFilterModel;
class EventFilterModel;
class SettingsStorage;

#include <QWidget>
#include <QMap>
#include <QPair>

namespace Ui
{
    class EventFilterProviderWidget;
}

class EventFilterProviderWidget : public QWidget
{

    Q_OBJECT

public:

    explicit EventFilterProviderWidget(QWidget * parent = 0);
    ~EventFilterProviderWidget();

    void setSettingsStorage(SettingsStorage * settingsStorage);

public slots:

    void setEventFilterProvider(EventFilterProvider * eventFilterProvider);

private slots:

    void stagesCurrentChanged(const QModelIndex & next, const QModelIndex & prev);
    void blocksCurrentChanged(const QModelIndex & next, const QModelIndex & prev);
    void filtersCurrentChanged(const QModelIndex & next, const QModelIndex & prev);

    void on_tbStageAdd_clicked();
    void on_tbStageEdit_clicked();
    void on_tbStageRemove_clicked();

    void on_tbBlockAdd_clicked();
    void on_tbBlockRemove_clicked();

    void on_tbEventFilterAdd_clicked();
    void on_tbEventFilterEdit_clicked();
    void on_tbEventFilterRemove_clicked();

private:

    void updateStagesBox();
    void updateBlocksBox();
    void updateFiltesBox();

    void restoreState();
    void saveState();

    bool eventFilter(QObject *o, QEvent *e);

private:

    Ui::EventFilterProviderWidget * ui;

    SettingsStorage * m_settingsStorage;

    EventFilterProvider * m_eventFilterProvider;
    StageEventFilterModel * m_stageEventFilterModel;
    BlockEventFilterModel * m_blockEventFilterModel;
    EventFilterModel * m_eventFilterModel;

};

#endif // EVENTFILTERPROVIDERWIDGET_H
