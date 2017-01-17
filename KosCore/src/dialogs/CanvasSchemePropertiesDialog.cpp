#include "CanvasSchemePropertiesDialog.h"
#include "ui_CanvasSchemePropertiesDialog.h"

#include "CanvasSchemeElement.h"

#include <SchemeScene.h>
#include <SettingsStorage.h>
#include <StringsKeys.h>

#include <QMessageBox>

CanvasSchemePropertiesDialog::CanvasSchemePropertiesDialog(CanvasSchemeElement * canvasSchemeElement,
                                                           SchemeScene * schemeScene,
                                                           QWidget * parent) :
    QDialog(parent),
    ui(new Ui::CanvasSchemePropertiesDialog),
    m_canvasSchemeElement(canvasSchemeElement),
    m_schemeScene(schemeScene)
{
    ui->setupUi(this);

    load();
}

CanvasSchemePropertiesDialog::~CanvasSchemePropertiesDialog()
{
    delete ui;
}

void CanvasSchemePropertiesDialog::load()
{
    ui->leTitle->setText( m_canvasSchemeElement->title() );
    ui->gbGrid->setChecked( m_canvasSchemeElement->gridStep() != 0 );
    ui->sbGridStep->setValue( m_canvasSchemeElement->gridStep() );
    ui->sbSizeWidth->setValue( m_canvasSchemeElement->size().width() );
    ui->sbSizeHeight->setValue( m_canvasSchemeElement->size().height() );
    ui->dsbDefaultZoom->setValue( m_canvasSchemeElement->defaultZoom() );
    ui->dsbFactorBasic->setValue( m_canvasSchemeElement->basicFactor() );
    ui->dsbFactorValve->setValue( m_canvasSchemeElement->valveFactor() );
    ui->dsbFactorLevel->setValue( m_canvasSchemeElement->levelFactor() );
}

void CanvasSchemePropertiesDialog::save()
{
    m_canvasSchemeElement->setParameters(ui->leTitle->text(),
                                         QSize(ui->sbSizeWidth->value(), ui->sbSizeHeight->value()),
                                         ui->gbGrid->isChecked() ? ui->sbGridStep->value() : 0,
                                         ui->dsbDefaultZoom->value(),
                                         ui->dsbFactorBasic->value(),
                                         ui->dsbFactorValve->value(),
                                         ui->dsbFactorLevel->value());
}

void CanvasSchemePropertiesDialog::on_buttonBox_accepted()
{
    if (ui->leTitle->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning..."), tr("Title is empty."));
        return;
    }
    if (ui->sbSizeWidth->value() <= 0 || ui->sbSizeWidth->value() <= 0)
    {
        QMessageBox::warning(this, tr("Warning..."), tr("Size is invalid."));
        return;
    }
    else if (ui->gbGrid->isChecked())
    {
        if (ui->sbGridStep->value() <= 0)
        {
            QMessageBox::warning(this, tr("Warning..."), tr("Grid step is invalid."));
            return;
        }
    }
    else if (ui->dsbFactorBasic->value() <= 0)
    {
        QMessageBox::warning(this, tr("Warning..."), tr("Basic element factor is invalid."));
    }
    else if (ui->dsbFactorValve->value() <= 0)
    {
        QMessageBox::warning(this, tr("Warning..."), tr("Valve element factor is invalid."));
    }
    else if (ui->dsbFactorLevel->value() <= 0)
    {
        QMessageBox::warning(this, tr("Warning..."), tr("Level element factor is invalid."));
    }

    save();
    accept();
}

void CanvasSchemePropertiesDialog::on_tbGetZoom_clicked()
{
    ui->dsbDefaultZoom->setValue(m_schemeScene->zoom());
}
