#include "SchemeEventFilterWidget.h"
#include "ui_SchemeEventFilterWidget.h"

#include "SchemeEventFilter.h"
#include "SchemeEventLogElement.h"
#include "StringsKeys.h"

SchemeEventFilterWidget::SchemeEventFilterWidget(QWidget * parent) :
    AbstractEventFilterWidget(parent),
    ui(new Ui::SchemeEventFilterWidget)
{
    ui->setupUi(this);
    ui->cbActionType->setCurrentIndex(-1);
}

SchemeEventFilterWidget::~SchemeEventFilterWidget()
{
    delete ui;
}

bool SchemeEventFilterWidget::isValid()
{
    return errorText().isEmpty();
}

QString SchemeEventFilterWidget::errorText()
{
    if (ui->cbActionType->currentIndex() == -1)
    {
        return tr("Action is not selected.");
    }
    if (ui->cbActionType->currentIndex() == SchemeEventLogElement::ActionType::ValveClosePercentageChanged)
    {
        if (ui->sbValveMaxValue->value() < ui->sbValveMinValue->value())
        {
            return tr("Value is invalid");
        }
    }
    if (ui->cbNodeKey->currentText().isEmpty() )
    {
        return tr("Node key is not selected.");
    }

    return QString();
}

void SchemeEventFilterWidget::save(AbstractEventFilter * eventFilter)
{
    SchemeEventFilter * schemeEventFilter = dynamic_cast<SchemeEventFilter*>(eventFilter);
    Q_ASSERT(schemeEventFilter != NULL);

    schemeEventFilter->setActionType( (SchemeEventLogElement::ActionType) ui->cbActionType->currentIndex());
    schemeEventFilter->setNodeKey( ui->cbNodeKey->currentText() );
    schemeEventFilter->setValveMinValue( ui->sbValveMinValue->value() );
    schemeEventFilter->setValveMaxValue( ui->sbValveMaxValue->value() );
}

void SchemeEventFilterWidget::load(AbstractEventFilter * eventFilter)
{
    SchemeEventFilter * schemeEventFilter = dynamic_cast<SchemeEventFilter*>(eventFilter);
    Q_ASSERT(schemeEventFilter != NULL);

    ui->cbActionType->setCurrentIndex( schemeEventFilter->actionType() );
    ui->cbNodeKey->setCurrentText( schemeEventFilter->nodeKey() );
    ui->sbValveMinValue->setValue( schemeEventFilter->valveMinValue() );
    ui->sbValveMaxValue->setValue( schemeEventFilter->valveMaxValue() );
}

void SchemeEventFilterWidget::on_cbActionType_currentIndexChanged(int index)
{
    ui->cbNodeKey->clear();

    switch (index)
    {
        case SchemeEventLogElement::ActionType::Invalid:
            ui->stackedWidget->setCurrentWidget(ui->pageInvalid);
            break;
        case SchemeEventLogElement::ActionType::ValveClosePercentageChanged:
            ui->cbNodeKey->addItems(Model::Valves::keys());
            ui->stackedWidget->setCurrentWidget(ui->pageValve);
            break;
        case SchemeEventLogElement::ActionType::LevelCheckNormal:
        case SchemeEventLogElement::ActionType::LevelCheckOverfill:
            ui->cbNodeKey->addItems(Model::WaterLocks::keys());
            ui->stackedWidget->setCurrentWidget(ui->pageLevel);
            break;
    }
}
