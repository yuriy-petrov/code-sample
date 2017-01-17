#include "powersweventfilterwidget.h"
#include "ui_powersweventfilterwidget.h"
#include "modeleventfilter.h"
#include "StringsKeys.h"

PowerSwEventFilterWidget::PowerSwEventFilterWidget(QWidget *parent)
    : AbstractEventFilterWidget(parent)
    , ui(new Ui::PowerSwEventFilterWidget)
{
    ui->setupUi(this);

    ui->comboBox->addItem(tr("Power on"), true);
    ui->comboBox->addItem(tr("Power off"), false);
}

PowerSwEventFilterWidget::~PowerSwEventFilterWidget()
{
    delete ui;
}

bool PowerSwEventFilterWidget::isValid()
{
    return errorText().isEmpty();
}

QString PowerSwEventFilterWidget::errorText()
{
    return QString();
}

void PowerSwEventFilterWidget::save(AbstractEventFilter *eventFilter)
{
    ModelEventFilter * modelEventFilter = dynamic_cast<ModelEventFilter*>(eventFilter);
    Q_ASSERT(modelEventFilter != NULL);

    modelEventFilter->setKey(Model::Power::Switch);
    modelEventFilter->setValue(ui->comboBox->currentData());
}

void PowerSwEventFilterWidget::load(AbstractEventFilter *eventFilter)
{
    ModelEventFilter * modelEventFilter = dynamic_cast<ModelEventFilter*>(eventFilter);
    Q_ASSERT(modelEventFilter != NULL);

    if(modelEventFilter->key() != Model::Power::Switch) {
        return;
    }

    for(int i = 0; i < ui->comboBox->count(); ++i) {
        if(ui->comboBox->itemData(i) == modelEventFilter->value()) {
            ui->comboBox->setCurrentIndex(i);
            break;
        }
    }
}
