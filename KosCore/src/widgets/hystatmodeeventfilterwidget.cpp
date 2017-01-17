#include "hystatmodeeventfilterwidget.h"
#include "ui_hystatmodeeventfilterwidget.h"
#include "modeleventfilter.h"
#include "modeltypeshelper.h"
#include "StringsKeys.h"

HystatModeEventFilterWidget::HystatModeEventFilterWidget(QWidget *parent)
    : AbstractEventFilterWidget(parent)
    , ui(new Ui::HystatModeEventFilterWidget)
{
    ui->setupUi(this);

    foreach(Model::HystatMode::Type mode, Model::TypesHelper::hystatModeNames().keys()) {
        ui->comboBox->addItem(Model::TypesHelper::hystatModeToString(mode), QVariant::fromValue<Model::HystatMode::Type>(mode));
    }
}

HystatModeEventFilterWidget::~HystatModeEventFilterWidget()
{
    delete ui;
}


bool HystatModeEventFilterWidget::isValid()
{
    return errorText().isEmpty();
}

QString HystatModeEventFilterWidget::errorText()
{
    return QString();
}

void HystatModeEventFilterWidget::save(AbstractEventFilter *eventFilter)
{
    ModelEventFilter * modelEventFilter = dynamic_cast<ModelEventFilter*>(eventFilter);
    Q_ASSERT(modelEventFilter != NULL);

    modelEventFilter->setKey(Model::HYSTAT_Mode);
    modelEventFilter->setValue(ui->comboBox->currentData());
}

void HystatModeEventFilterWidget::load(AbstractEventFilter *eventFilter)
{
    ModelEventFilter * modelEventFilter = dynamic_cast<ModelEventFilter*>(eventFilter);
    Q_ASSERT(modelEventFilter != NULL);

    if(modelEventFilter->key() != Model::HYSTAT_Mode) {
        return;
    }

    for(int i = 0; i < ui->comboBox->count(); ++i) {
        if(ui->comboBox->itemData(i) == modelEventFilter->value()) {
            ui->comboBox->setCurrentIndex(i);
            break;
        }
    }
}
