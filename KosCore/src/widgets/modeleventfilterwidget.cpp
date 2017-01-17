#include "modeleventfilterwidget.h"
#include "ui_modeleventfilterwidget.h"
#include "hystatmodeeventfilterwidget.h"
#include "powersweventfilterwidget.h"
#include "cellstackeventfilterwidget.h"
#include "hwswitcheventfilterwidget.h"

ModelEventFilterWidget::ModelEventFilterWidget(QWidget *parent)
    : AbstractEventFilterWidget(parent)
    , ui(new Ui::ModelEventFilterWidget)
    , m_eventWidget(NULL)
{
    ui->setupUi(this);

    ui->comboBox->addItem(tr("HYSTAT mode"), QVariant::fromValue<ModelEventFilterWidget::EventType>(HYSTAT_MODE));
    ui->comboBox->addItem(tr("Power"), QVariant::fromValue<ModelEventFilterWidget::EventType>(POWER_SWITCH));
    ui->comboBox->addItem(tr("Cell Stack"), QVariant::fromValue<ModelEventFilterWidget::EventType>(CELL_STACK));
    ui->comboBox->addItem(tr("Key position"), QVariant::fromValue<ModelEventFilterWidget::EventType>(HW_SWITCH));
}

ModelEventFilterWidget::~ModelEventFilterWidget()
{
    delete ui;
}


bool ModelEventFilterWidget::isValid()
{
    return m_eventWidget && m_eventWidget->isValid();
}

QString ModelEventFilterWidget::errorText()
{
    return
            m_eventWidget ?
                m_eventWidget->errorText() :
                QString();
}

void ModelEventFilterWidget::save(AbstractEventFilter *eventFilter)
{
    if(m_eventWidget) {
        m_eventWidget->save(eventFilter);
    }
}

void ModelEventFilterWidget::load(AbstractEventFilter *eventFilter)
{
    if(m_eventWidget) {
        m_eventWidget->load(eventFilter);
    }
}

void ModelEventFilterWidget::on_comboBox_currentIndexChanged(int index)
{
    if(m_eventWidget) {
        delete m_eventWidget;
        m_eventWidget = NULL;
    }

    switch(ui->comboBox->itemData(index).value<ModelEventFilterWidget::EventType>()) {
        case HYSTAT_MODE:
        {
            HystatModeEventFilterWidget * widget = new HystatModeEventFilterWidget(this);
            qobject_cast<QBoxLayout*>(layout())->insertWidget(layout()->count() - 1, widget);
            m_eventWidget = widget;
            break;
        }
        case POWER_SWITCH:
        {
            PowerSwEventFilterWidget * widget = new PowerSwEventFilterWidget(this);
            qobject_cast<QBoxLayout*>(layout())->insertWidget(layout()->count() - 1, widget);
            m_eventWidget = widget;
            break;
        }
        case CELL_STACK:
        {
            CellStackEventFilterWidget * widget = new CellStackEventFilterWidget(this);
            qobject_cast<QBoxLayout*>(layout())->insertWidget(layout()->count() - 1, widget);
            m_eventWidget = widget;
            break;
        }
        case HW_SWITCH:
        {
            HwSwitchEventFilterWidget * widget = new HwSwitchEventFilterWidget(this);
            qobject_cast<QBoxLayout*>(layout())->insertWidget(layout()->count() - 1, widget);
            m_eventWidget = widget;
            break;
        }
    }
}
