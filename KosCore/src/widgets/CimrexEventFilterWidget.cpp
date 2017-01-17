#include "CimrexEventFilterWidget.h"
#include "ui_CimrexEventFilterWidget.h"
#include "CimrexEventFilter.h"

#include "ConfigReader.h"

CimrexEventFilterWidget::CimrexEventFilterWidget(QWidget *parent)
    : AbstractEventFilterWidget(parent)
    , ui(new Ui::CimrexEventFilterWidget)
{
    ui->setupUi(this);
    ui->comboBox->addItems(ConfigReader::pagesById());
    // we need to add items to combo box
}

CimrexEventFilterWidget::~CimrexEventFilterWidget()
{
    delete ui;
}

bool CimrexEventFilterWidget::isValid()
{
    return errorText().isEmpty();
}

QString CimrexEventFilterWidget::errorText()
{
    return QString();
}

void CimrexEventFilterWidget::save(AbstractEventFilter *eventFilter)
{
    CimrexEventFilter * cimrexEventFilter = dynamic_cast<CimrexEventFilter*>(eventFilter);
    Q_ASSERT(cimrexEventFilter != NULL);

    cimrexEventFilter->setSelectedDisplayId(ui->comboBox->currentText()) ;
}

void CimrexEventFilterWidget::load(AbstractEventFilter *eventFilter)
{
    CimrexEventFilter * cimrexEventFilter = dynamic_cast<CimrexEventFilter*>(eventFilter);
    Q_ASSERT(cimrexEventFilter != NULL);

    for(int i = 0; i < ui->comboBox->count(); ++i)
    {
        if(ui->comboBox->currentText() == cimrexEventFilter->selectedDisplayId() )
        {
            ui->comboBox->setCurrentIndex(i);
            break;
        }
    }
}
