#include "hwswitcheventfilterwidget.h"
#include "ui_hwswitcheventfilterwidget.h"
#include "modeleventfilter.h"
#include "modeltypeshelper.h"
#include "StringsKeys.h"

HwSwitchEventFilterWidget::HwSwitchEventFilterWidget(QWidget *parent)
    : AbstractEventFilterWidget(parent)
    , ui(new Ui::HwSwitchEventFilterWidget)
{
    ui->setupUi(this);

    foreach(Model::HwSwitchPos pos, Model::TypesHelper::hwSwitchPosNames().keys()) {
        ui->comboBox->addItem(Model::TypesHelper::hwSwitchPosToString(pos), QVariant::fromValue<Model::HwSwitchPos>(pos));
    }
}

HwSwitchEventFilterWidget::~HwSwitchEventFilterWidget()
{
    delete ui;
}

bool HwSwitchEventFilterWidget::isValid()
{
    return errorText().isEmpty();
}

QString HwSwitchEventFilterWidget::errorText()
{
    return QString();
}

void HwSwitchEventFilterWidget::save(AbstractEventFilter * eventFilter)
{
    ModelEventFilter * modelEventFilter = dynamic_cast<ModelEventFilter*>(eventFilter);
    Q_ASSERT(modelEventFilter != NULL);

    modelEventFilter->setKey(Model::HW_SWITCH);
    modelEventFilter->setValue(ui->comboBox->currentData());
}

void HwSwitchEventFilterWidget::load(AbstractEventFilter * eventFilter)
{
    ModelEventFilter * modelEventFilter = dynamic_cast<ModelEventFilter*>(eventFilter);
    Q_ASSERT(modelEventFilter != NULL);

    if(modelEventFilter->key() != Model::HW_SWITCH) {
        return;
    }

    for(int i = 0; i < ui->comboBox->count(); ++i) {
        if(ui->comboBox->itemData(i) == modelEventFilter->value()) {
            ui->comboBox->setCurrentIndex(i);
            break;
        }
    }
}
