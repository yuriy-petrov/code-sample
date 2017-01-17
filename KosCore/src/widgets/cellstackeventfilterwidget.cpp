#include "cellstackeventfilterwidget.h"
#include "ui_cellstackeventfilterwidget.h"
#include "modeleventfilter.h"
#include "StringsKeys.h"

CellStackEventFilterWidget::CellStackEventFilterWidget(QWidget *parent)
    : AbstractEventFilterWidget(parent)
    , ui(new Ui::CellStackEventFilterWidget)
{
    ui->setupUi(this);

    ui->comboBoxCS->addItem(tr("Cell Stack 1"), Model::CellStack::Enable::CS1);
    ui->comboBoxCS->addItem(tr("Cell Stack 2"), Model::CellStack::Enable::CS2);
    ui->comboBoxCS->addItem(tr("Cell Stack 3"), Model::CellStack::Enable::CS3);
    ui->comboBoxCS->addItem(tr("Cell Stack 4"), Model::CellStack::Enable::CS4);

    ui->comboBoxEnable->addItem(tr("Enabled"), true);
    ui->comboBoxEnable->addItem(tr("Disabled"), false);
}

CellStackEventFilterWidget::~CellStackEventFilterWidget()
{
    delete ui;
}

bool CellStackEventFilterWidget::isValid()
{
    return errorText().isEmpty();
}

QString CellStackEventFilterWidget::errorText()
{
    return QString();
}

void CellStackEventFilterWidget::save(AbstractEventFilter *eventFilter)
{
    ModelEventFilter * modelEventFilter = dynamic_cast<ModelEventFilter*>(eventFilter);
    Q_ASSERT(modelEventFilter != NULL);

    modelEventFilter->setKey(ui->comboBoxCS->currentData().toString());
    modelEventFilter->setValue(ui->comboBoxEnable->currentData());
}

void CellStackEventFilterWidget::load(AbstractEventFilter *eventFilter)
{
    ModelEventFilter * modelEventFilter = dynamic_cast<ModelEventFilter*>(eventFilter);
    Q_ASSERT(modelEventFilter != NULL);

    for(int i = 0; i < ui->comboBoxCS->count(); ++i) {
        if(modelEventFilter->key().compare(ui->comboBoxCS->itemData(i).toString()) == 0) {
            ui->comboBoxCS->setCurrentIndex(i);

            for(int i = 0; i < ui->comboBoxEnable->count(); ++i) {
                if(ui->comboBoxEnable->itemData(i) == modelEventFilter->value()) {
                    ui->comboBoxEnable->setCurrentIndex(i);
                    break;
                }
            }
        }
    }
}
