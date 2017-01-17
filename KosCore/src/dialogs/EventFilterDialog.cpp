#include "EventFilterDialog.h"
#include "ui_EventFilterDialog.h"

#include "AbstractEventFilter.h"
#include "AbstractEventFilterWidget.h"
#include "SnapshotConditionModel.h"
#include "SnapshotCondition.h"
#include "comboboxitemdelegate.h"
#include "modelvaluesdelegate.h"

#include <QMessageBox>

EventFilterDialog::EventFilterDialog(AbstractEventFilter * prevEventFilter,
                                     QWidget * parent) :
    QDialog(parent),
    ui(new Ui::EventFilterDialog),
    m_prevEventFilter(prevEventFilter),
    m_nextEventFilter(NULL),
    m_eventFilterWidget(NULL)
{
    ui->setupUi(this);

    ui->tbSnapshotConditionAppend->setIcon( QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton) );
    ui->tbSnapshotConditionRemove->setIcon( QApplication::style()->standardIcon(QStyle::SP_DialogCloseButton) );

    m_snapshotCondition = new SnapshotCondition;

    if (prevEventFilter)
    {
        ui->cbType->setCurrentIndex(m_prevEventFilter->eventLogType());
        if (m_eventFilterWidget)
        {
            m_eventFilterWidget->load(m_prevEventFilter);
        }
        *m_snapshotCondition = *m_prevEventFilter->snapshotCondition();
    }

    m_snapshotConditionModel = new SnapshotConditionModel(this);
    m_snapshotConditionModel->setSnapshotCondition(m_snapshotCondition);
    ui->tvSnapshotConditions->setModel(m_snapshotConditionModel);

    ui->tvSnapshotConditions->setItemDelegateForColumn(SnapshotConditionModel::Key, new ComboboxItemDelegate(ui->tvSnapshotConditions));
    ui->tvSnapshotConditions->setItemDelegateForColumn(SnapshotConditionModel::Type, new ComboboxItemDelegate(ui->tvSnapshotConditions));
    ui->tvSnapshotConditions->setItemDelegateForColumn(SnapshotConditionModel::ValueMin, new ModelValuesDelegate(ui->tvSnapshotConditions));
    ui->tvSnapshotConditions->setItemDelegateForColumn(SnapshotConditionModel::ValueMax, new ModelValuesDelegate(ui->tvSnapshotConditions));
    ui->tvSnapshotConditions->setItemDelegateForColumn(SnapshotConditionModel::Inverse, new ComboboxItemDelegate(ui->tvSnapshotConditions));
    ui->tvSnapshotConditions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

EventFilterDialog::~EventFilterDialog()
{
    delete m_snapshotCondition;
    delete ui;
}

AbstractEventFilter * EventFilterDialog::prevEventFilter() const
{
    return m_prevEventFilter;
}

AbstractEventFilter * EventFilterDialog::nextEventFilter() const
{
    return m_nextEventFilter;
}

void EventFilterDialog::on_buttonBox_accepted()
{
    if (ui->cbType->currentIndex() == AbstractEventLogElement::EventLogType::Invalid)
    {
        QMessageBox::warning(this, tr("Warning..."), tr("Type of event is invalid."));
        return;
    }

    if (m_eventFilterWidget != NULL)
    {
        if (m_eventFilterWidget->isValid())
        {
            m_eventFilterWidget->save(m_nextEventFilter);
        }
        else
        {
            QMessageBox::warning(this, tr("Warning..."), m_eventFilterWidget->errorText());
            return;
        }
    }

    if (m_nextEventFilter)
    {
        *m_nextEventFilter->snapshotCondition() = *m_snapshotCondition;
    }

    foreach (SnapshotCondition::Condition condition, m_snapshotCondition->conditions())
    {
        if (condition.key.isEmpty())
        {
            QMessageBox::warning(this, tr("Warning..."), tr("Condition key is empty."));
            return;
        }
    }

    accept();
}

void EventFilterDialog::on_buttonBox_rejected()
{
    clear();
    reject();
}

void EventFilterDialog::on_cbType_currentIndexChanged(int index)
{
    clear();

    if (index != AbstractEventLogElement::EventLogType::Invalid)
    {
        m_nextEventFilter = AbstractEventFilter::createByEventLogType((AbstractEventLogElement::EventLogType)index);
        if (m_nextEventFilter)
        {
            if (m_prevEventFilter)
            {
                m_nextEventFilter->setTitle( m_prevEventFilter->title() );
            }

            m_eventFilterWidget = AbstractEventFilterWidget::createByEventLogType((AbstractEventLogElement::EventLogType)index, this);
            if (m_eventFilterWidget)
            {
                m_eventFilterWidget->load(m_nextEventFilter);
                ui->lWidget->addWidget(m_eventFilterWidget);
            }
        }
    }
}

void EventFilterDialog::clear()
{
    if (m_nextEventFilter != NULL)
    {
        delete m_nextEventFilter;
        m_nextEventFilter = NULL;
    }

    if (m_eventFilterWidget != NULL)
    {
        delete m_eventFilterWidget;
        m_eventFilterWidget = NULL;
    }

}

void EventFilterDialog::on_tbSnapshotConditionAppend_clicked()
{
    m_snapshotConditionModel->insertRow(m_snapshotConditionModel->rowCount());
}

void EventFilterDialog::on_tbSnapshotConditionRemove_clicked()
{
    QModelIndex index = ui->tvSnapshotConditions->selectionModel()->currentIndex();
    if (index.isValid())
    {
        m_snapshotConditionModel->removeRow(index.row());
    }
}
