#include "PipelineSchemeElementDialog.h"
#include "ui_PipelineSchemeElementDialog.h"

#include "KosTypesHelper.h"

#include "PipelineSchemeElement.h"

PipelineSchemeElementDialog::PipelineSchemeElementDialog(PipelineSchemeElement * pipelineSchemeElement,
                                                         QWidget * parent) :
    QDialog(parent),
    ui(new Ui::PipelineSchemeElementDialog),
    m_pipelineSchemeElement(pipelineSchemeElement)
{
    ui->setupUi(this);

    // State
    m_pipelineStates = KosTypesHelper::instance()->pipelineStateTitles().keys();
    qSort(m_pipelineStates);
    foreach (KosTypes::PipelineState state, m_pipelineStates)
    {
        ui->cbState->addItem( KosTypesHelper::instance()->pipelineStateTitles()[state] );
    }

    // Substance types
    m_substanceTypes = KosTypesHelper::instance()->substanceTypeTitles().keys();
    qSort(m_substanceTypes);
    foreach (KosTypes::SubstanceType substanceType, m_substanceTypes)
    {
        ui->cbSubstanceType->addItem( KosTypesHelper::instance()->substanceTypeTitles()[substanceType] );
    }

    load();
}

PipelineSchemeElementDialog::~PipelineSchemeElementDialog()
{
    delete ui;
}

void PipelineSchemeElementDialog::load()
{
    ui->cbState->setCurrentIndex( m_pipelineStates.indexOf(m_pipelineSchemeElement->state()) );
    ui->cbSubstanceType->setCurrentIndex( m_substanceTypes.indexOf(m_pipelineSchemeElement->substanceType()) );
    ui->sbWidth->setValue(m_pipelineSchemeElement->width());
}

void PipelineSchemeElementDialog::save()
{
    m_pipelineSchemeElement->setParameters(m_pipelineSchemeElement->pipes(),
                                           m_pipelineStates[ui->cbState->currentIndex()],
                                           m_substanceTypes[ui->cbSubstanceType->currentIndex()],
                                           ui->sbWidth->value());
}

void PipelineSchemeElementDialog::on_buttonBox_accepted()
{
    save();
    accept();
}
