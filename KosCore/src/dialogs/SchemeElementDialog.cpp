#include "SchemeElementDialog.h"
#include "ui_SchemeElementDialog.h"

#include "AbstractSchemeElement.h"

SchemeElementDialog::SchemeElementDialog(AbstractSchemeElement * schemeElement,
                                         QWidget * parent) :
    QDialog(parent),
    ui(new Ui::SchemeElementDialog),
    m_schemeElement(schemeElement)
{
    ui->setupUi(this);
    load();
}

SchemeElementDialog::~SchemeElementDialog()
{
    delete ui;
}

void SchemeElementDialog::load()
{
    ui->leNodeKey->setText(m_schemeElement->nodeKey());
    ui->leTooltip->setText(m_schemeElement->tooltip());

    ui->leFormText->setText(m_schemeElement->formText());
    ui->sbFormFontSize->setValue(m_schemeElement->formFontSize());
    ui->sbFormOffsetX->setValue(m_schemeElement->formOffset().x());
    ui->sbFormOffsetY->setValue(m_schemeElement->formOffset().y());

    ui->cbFormRotation->setCurrentIndex(m_schemeElement->formRotation());

    ui->wPosition->setHorizontalAlignment(m_schemeElement->formPositionX());
    ui->wPosition->setVerticalAlignment(m_schemeElement->formPositionY());

    ui->wAlignment->setHorizontalAlignment(m_schemeElement->formAlignmentX());
    ui->wAlignment->setVerticalAlignment(m_schemeElement->formAlignmentY());
}

void SchemeElementDialog::save()
{
    m_schemeElement->setParameters(ui->leNodeKey->text(),
                                   ui->leTooltip->text(),
                                   ui->leFormText->text(),
                                   ui->wPosition->horizontalAlignment(),
                                   ui->wPosition->verticalAlignment(),
                                   ui->wAlignment->horizontalAlignment(),
                                   ui->wAlignment->verticalAlignment(),
                                   QPointF(ui->sbFormOffsetX->value(), ui->sbFormOffsetY->value()),
                                   ui->sbFormFontSize->value(),
                                   ui->cbFormRotation->currentIndex());
}

void SchemeElementDialog::on_buttonBox_accepted()
{
    save();
    accept();
}
