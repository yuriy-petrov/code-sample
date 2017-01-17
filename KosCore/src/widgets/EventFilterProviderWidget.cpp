#include "EventFilterProviderWidget.h"
#include "ui_EventFilterProviderWidget.h"

#include "EventFilterProvider.h"
#include "stageeventfiltermodel.h"
#include "blockeventfiltermodel.h"
#include "eventfiltermodel.h"
#include "EventFilterDialog.h"
#include "comboboxitemdelegate.h"
#include "SettingsStorage.h"
#include "multilinedelegate.h"

#include <log.h>

EventFilterProviderWidget::EventFilterProviderWidget(QWidget * parent)
    : QWidget(parent)
    , ui(new Ui::EventFilterProviderWidget)
    , m_settingsStorage(NULL)
    , m_eventFilterProvider(NULL)
{
    ui->setupUi(this);

    ui->tbStageAdd->setIcon( QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton) );
    ui->tbStageEdit->setIcon( QApplication::style()->standardIcon(QStyle::SP_DialogHelpButton) );
    ui->tbStageRemove->setIcon( QApplication::style()->standardIcon(QStyle::SP_DialogCloseButton) );

    ui->tbBlockAdd->setIcon( QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton) );
    ui->tbBlockRemove->setIcon( QApplication::style()->standardIcon(QStyle::SP_DialogCloseButton) );

    ui->tbEventFilterAdd->setIcon( QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton) );
    ui->tbEventFilterEdit->setIcon( QApplication::style()->standardIcon(QStyle::SP_DialogHelpButton) );
    ui->tbEventFilterRemove->setIcon( QApplication::style()->standardIcon(QStyle::SP_DialogCloseButton) );

    m_stageEventFilterModel = new StageEventFilterModel(this);
    m_stageEventFilterModel->setEventFilterProvider(m_eventFilterProvider);
    ui->tvStages->setModel(m_stageEventFilterModel);
    ui->tvStages->setItemDelegate(new MultilineDelegate(ui->tvStages));
    ui->tvStages->installEventFilter(this);

    m_blockEventFilterModel = new BlockEventFilterModel(this);
    m_blockEventFilterModel->setStageEventFilter(NULL);
    ui->tvBlocks->setModel(m_blockEventFilterModel);
    ui->tvBlocks->setItemDelegate(new MultilineDelegate(ui->tvBlocks));
    ui->tvBlocks->setItemDelegateForColumn(BlockEventFilterModel::COL_OPERATION, new ComboboxItemDelegate(ui->tvBlocks));
    ui->tvBlocks->setItemDelegateForColumn(BlockEventFilterModel::COL_TIME_INTERVAL_TYPE, new ComboboxItemDelegate(ui->tvBlocks));
    ui->tvBlocks->installEventFilter(this);

    m_eventFilterModel = new EventFilterModel(this);
    m_eventFilterModel->setBlockEventFilter(NULL);
    ui->tvEventFilters->setModel(m_eventFilterModel);
    ui->tvEventFilters->setItemDelegate(new MultilineDelegate(ui->tvEventFilters));
    ui->tvEventFilters->installEventFilter(this);

    QObject::connect(ui->tvStages->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                     this, SLOT(stagesCurrentChanged(QModelIndex,QModelIndex)));
    QObject::connect(ui->tvBlocks->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                     this, SLOT(blocksCurrentChanged(QModelIndex,QModelIndex)));
    QObject::connect(ui->tvEventFilters->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                     this, SLOT(filtersCurrentChanged(QModelIndex,QModelIndex)));

    restoreState();
}

EventFilterProviderWidget::~EventFilterProviderWidget()
{
    saveState();
    delete ui;
}

void EventFilterProviderWidget::setSettingsStorage(SettingsStorage *settingsStorage)
{
    m_settingsStorage = settingsStorage;
    restoreState();
}

void EventFilterProviderWidget::setEventFilterProvider(EventFilterProvider * eventFilterProvider)
{
    m_eventFilterProvider = eventFilterProvider;
    m_stageEventFilterModel->setEventFilterProvider(m_eventFilterProvider);
    ui->tvStages->resizeRowsToContents();
}

void EventFilterProviderWidget::stagesCurrentChanged(const QModelIndex & next, const QModelIndex & prev)
{
    Q_UNUSED(next);
    Q_UNUSED(prev);

    updateStagesBox();
}

void EventFilterProviderWidget::blocksCurrentChanged(const QModelIndex &next, const QModelIndex &prev)
{
    Q_UNUSED(next);
    Q_UNUSED(prev);

    updateBlocksBox();
}

void EventFilterProviderWidget::filtersCurrentChanged(const QModelIndex &next, const QModelIndex &prev)
{
    Q_UNUSED(next);
    Q_UNUSED(prev);

    updateFiltesBox();
}

void EventFilterProviderWidget::on_tbStageAdd_clicked()
{
    QModelIndex modelIndex = ui->tvStages->selectionModel()->currentIndex();
    if (modelIndex.isValid())
    {
        m_stageEventFilterModel->insertRows(modelIndex.row() + 1, 1);
    }
    else
    {
        m_stageEventFilterModel->insertRows(0, 1);
    }
}

void EventFilterProviderWidget::on_tbStageEdit_clicked()
{
    QModelIndex modelIndex = ui->tvStages->selectionModel()->currentIndex();
    if (modelIndex.isValid())
    {
        StageEventFilter * stageEventFilter = m_eventFilterProvider->stageEventFilterList().at(modelIndex.row());

        AbstractEventFilter * prevEventFilter = stageEventFilter->eventFilter();
        EventFilterDialog eventFilterDialog(prevEventFilter, this);
        if (eventFilterDialog.exec() == QDialog::Accepted)
        {
            stageEventFilter->setEventFilter(eventFilterDialog.nextEventFilter());
        }
    }
}

void EventFilterProviderWidget::on_tbStageRemove_clicked()
{
    QModelIndex modelIndex = ui->tvStages->selectionModel()->currentIndex();
    if (modelIndex.isValid())
    {
        m_stageEventFilterModel->removeRows(modelIndex.row(), 1);
    }
}

void EventFilterProviderWidget::on_tbBlockAdd_clicked()
{
    QModelIndex modelIndex = ui->tvBlocks->selectionModel()->currentIndex();
    if (modelIndex.isValid())
    {
        m_blockEventFilterModel->insertRows(modelIndex.row() + 1, 1);
    }
    else
    {
        m_blockEventFilterModel->insertRows(0, 1);
    }
}

void EventFilterProviderWidget::on_tbBlockRemove_clicked()
{
    QModelIndex modelIndex = ui->tvBlocks->selectionModel()->currentIndex();
    if (modelIndex.isValid())
    {
        m_blockEventFilterModel->removeRows(modelIndex.row(), 1);
    }
}

void EventFilterProviderWidget::on_tbEventFilterAdd_clicked()
{
    QModelIndex stageIndex = ui->tvStages->selectionModel()->currentIndex();
    QModelIndex blockIndex = ui->tvBlocks->selectionModel()->currentIndex();
    QModelIndex filterIndex = ui->tvEventFilters->selectionModel()->currentIndex();

    if (!stageIndex.isValid() || !blockIndex.isValid())
    {
        return;
    }

    if (filterIndex.isValid())
    {
        m_eventFilterModel->insertRows(filterIndex.row() + 1, 1);
    }
    else
    {
        m_eventFilterModel->insertRows(0, 1);
    }

    ui->tvEventFilters->resizeRowsToContents();
}

void EventFilterProviderWidget::on_tbEventFilterEdit_clicked()
{
    QModelIndex modelIndex = ui->tvEventFilters->selectionModel()->currentIndex();
    if (modelIndex.isValid())
    {
        StageEventFilter * stageEventFilter = m_eventFilterProvider->stageEventFilterList().at(ui->tvStages->selectionModel()->currentIndex().row());
        BlockEventFilter * blockEventFilter = stageEventFilter->blockEventFilterList().at(ui->tvBlocks->selectionModel()->currentIndex().row());
        AbstractEventFilter * eventFilter = blockEventFilter->eventFilterList().at(modelIndex.row());

        EventFilterDialog eventFilterDialog(eventFilter, this);
        if (eventFilterDialog.exec() == QDialog::Accepted)
        {
            blockEventFilter->replaceEventFilter(eventFilterDialog.nextEventFilter(), modelIndex.row());
            delete eventFilter;
            ui->tvEventFilters->resizeRowsToContents();
        }
    }
}

void EventFilterProviderWidget::on_tbEventFilterRemove_clicked()
{
    QModelIndex modelIndex = ui->tvEventFilters->selectionModel()->currentIndex();
    if (modelIndex.isValid())
    {
        m_eventFilterModel->removeRows(modelIndex.row(), 1);
    }
}

void EventFilterProviderWidget::updateStagesBox()
{
    QModelIndex next = ui->tvStages->selectionModel()->currentIndex();

    if (next.isValid())
    {
        m_blockEventFilterModel->setStageEventFilter( m_eventFilterProvider->stageEventFilterList().at(next.row() ));
        ui->tvBlocks->setCurrentIndex(m_blockEventFilterModel->index(0, 0));
    }
    else
    {
        m_blockEventFilterModel->setStageEventFilter(NULL);
    }

    ui->gbBlocks->setEnabled(next.isValid());
    ui->tbBlockAdd->setEnabled(next.isValid());
    ui->tbStageEdit->setEnabled(next.isValid());
    ui->tbStageRemove->setEnabled(next.isValid());

    ui->tvBlocks->resizeRowsToContents();

    updateBlocksBox();
}

void EventFilterProviderWidget::updateBlocksBox()
{
    QModelIndex next = ui->tvBlocks->selectionModel()->currentIndex();

    if (next.isValid())
    {
        m_eventFilterModel->setBlockEventFilter( m_eventFilterProvider->stageEventFilterList().at(ui->tvStages->selectionModel()->currentIndex().row())->blockEventFilterList().at(next.row() ));
        ui->tvEventFilters->setCurrentIndex(m_eventFilterModel->index(0, 0));
    }
    else
    {
        m_eventFilterModel->setBlockEventFilter(NULL);
    }

    ui->gbEventFilters->setEnabled(next.isValid());
    ui->tbEventFilterAdd->setEnabled(next.isValid());
    ui->tbBlockRemove->setEnabled(next.isValid());

    updateFiltesBox();
}

void EventFilterProviderWidget::updateFiltesBox()
{
    QModelIndex next = ui->tvEventFilters->selectionModel()->currentIndex();

    if (next.isValid())
    {
        // TODO: Здесь создавать виджет редактирования фильтра
    }
    else
    {
    }

    ui->tbEventFilterEdit->setEnabled(next.isValid());
    ui->tbEventFilterRemove->setEnabled(next.isValid());

    ui->tvEventFilters->resizeRowsToContents();
}

void EventFilterProviderWidget::restoreState()
{
    if(m_settingsStorage == NULL) {
        return;
    }

    ui->splitter->restoreState(m_settingsStorage->rawValue("splitter", ui->splitter->saveState(), objectName()).toByteArray());
    ui->tvStages->horizontalHeader()->restoreState(m_settingsStorage->rawValue("stages_header", ui->tvStages->horizontalHeader()->saveState(), objectName()).toByteArray());
    ui->tvBlocks->horizontalHeader()->restoreState(m_settingsStorage->rawValue("blocks_header", ui->tvBlocks->horizontalHeader()->saveState(), objectName()).toByteArray());
    ui->tvEventFilters->horizontalHeader()->restoreState(m_settingsStorage->rawValue("filters_header", ui->tvEventFilters->horizontalHeader()->saveState(), objectName()).toByteArray());
}

void EventFilterProviderWidget::saveState()
{
    if(m_settingsStorage == NULL) {
        return;
    }

    m_settingsStorage->setRawValue("splitter", ui->splitter->saveState(), objectName());
    m_settingsStorage->setRawValue("stages_header", ui->tvStages->horizontalHeader()->saveState(), objectName());
    m_settingsStorage->setRawValue("blocks_header", ui->tvBlocks->horizontalHeader()->saveState(), objectName());
    m_settingsStorage->setRawValue("filters_header", ui->tvEventFilters->horizontalHeader()->saveState(), objectName());
}

bool EventFilterProviderWidget::eventFilter(QObject *o, QEvent *e)
{
    if( (o == ui->tvStages) ||
        (o == ui->tvBlocks) ||
        (o == ui->tvEventFilters)
        )
    {
        switch(e->type()) {
            case QEvent::Resize:
            case QEvent::Timer:
            {
                QTableView * tv = qobject_cast<QTableView*>(o);
                if(tv) {
                    tv->resizeRowsToContents();
                }
                break;
            }
        }
    }

    return false;
}
