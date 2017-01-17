#include "ValveSchemeElementDialog.h"
#include "ui_ValveSchemeElementDialog.h"

#include "ValveSchemeItem.h"
#include "ValveSchemeElement.h"
#include "KosTypesHelper.h"
#include "SettingsStorage.h"
#include "StringsKeys.h"
#include "CanvasSchemeElement.h"

#include <QMessageBox>

ValveSchemeElementDialog::ValveSchemeElementDialog(SettingsStorage * settingsStorage,
                                                   CanvasSchemeElement * canvasSchemeElement,
                                                   ValveSchemeElement * valveSchemeElement,
                                                   QWidget * parent) :
    QDialog(parent),
    ui(new Ui::ValveSchemeElementDialog),
    m_settingsStorage(settingsStorage),
    m_canvasSchemeElement(canvasSchemeElement),
    m_valveSchemeElement(valveSchemeElement),
    m_isConfigured(false)
{
    ui->setupUi(this);

    // Valve types
    m_valveTypes = KosTypesHelper::instance()->valveTypeTitles().keys();
    qSort(m_valveTypes);
    foreach (KosTypes::ValveType valveType, m_valveTypes)
    {
        ui->cbValveType->addItem( KosTypesHelper::instance()->valveTypeTitles()[valveType] );
    }

    // Substance types
    m_substanceTypes = KosTypesHelper::instance()->substanceTypeTitles().keys();
    qSort(m_substanceTypes);
    foreach (KosTypes::SubstanceType substanceType, m_substanceTypes)
    {
        ui->cbSubstanceType->addItem( KosTypesHelper::instance()->substanceTypeTitles()[substanceType] );
    }

    m_isConfigured = true;

    load(m_valveSchemeElement);
    updatePixmap();

    //

    QObject::connect(ui->cbValveType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->cbSubstanceType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->cbValid, SIGNAL(toggled(bool)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->cbClosePercentageVisible, SIGNAL(toggled(bool)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->sbClosePercentageValue, SIGNAL(valueChanged(int)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->sbClosePercentagePositionX, SIGNAL(valueChanged(int)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->sbClosePercentagePositionY, SIGNAL(valueChanged(int)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->sbPositionX, SIGNAL(valueChanged(double)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->sbPositionY, SIGNAL(valueChanged(double)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->bgRotation, SIGNAL(buttonToggled(int,bool)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->bgMirrored, SIGNAL(buttonToggled(int,bool)),
                     this, SLOT(updatePixmap()));
}

ValveSchemeElementDialog::~ValveSchemeElementDialog()
{
    delete ui;
}

void ValveSchemeElementDialog::load(ValveSchemeElement * valveSchemeElement)
{
    ui->cbValveType->setCurrentIndex( m_valveTypes.indexOf(valveSchemeElement->valveType()) );
    ui->cbSubstanceType->setCurrentIndex( m_substanceTypes.indexOf(valveSchemeElement->substanceType()) );
    ui->sbClosePercentageValue->setValue( valveSchemeElement->closePercentage() );
    ui->cbClosePercentageVisible->setChecked( valveSchemeElement->closePercentageVisible() );
    ui->sbClosePercentagePositionX->setValue( valveSchemeElement->closePercentagePositionX() );
    ui->sbClosePercentagePositionY->setValue( valveSchemeElement->closePercentagePositionY() );
    ui->cbValid->setChecked( valveSchemeElement->isValid() );

    ui->sbPositionX->setValue( valveSchemeElement->position().x() );
    ui->sbPositionY->setValue( valveSchemeElement->position().y() );

    ui->rbRotation0->setChecked(valveSchemeElement->rotation() == 0);
    ui->rbRotation90->setChecked(valveSchemeElement->rotation() == 90);
    ui->rbRotation180->setChecked(valveSchemeElement->rotation() == 180);
    ui->rbRotation270->setChecked(valveSchemeElement->rotation() == 270);

    ui->cbMirroredHorizontal->setChecked(valveSchemeElement->mirroredHorizontal());
    ui->cbMirroredVertical->setChecked(valveSchemeElement->mirroredVertical());
}

void ValveSchemeElementDialog::save(ValveSchemeElement * valveSchemeElement)
{
    qreal rotate = rotateAngleFromUi();

    valveSchemeElement->setParameters(
                m_valveTypes[ui->cbValveType->currentIndex()],
                m_substanceTypes[ui->cbSubstanceType->currentIndex()],
                ui->sbClosePercentageValue->value(),
                ui->cbClosePercentageVisible->isChecked(),
                ui->sbClosePercentagePositionX->value(),
                ui->sbClosePercentagePositionY->value(),
                ui->cbValid->isChecked(),
                QPointF(ui->sbPositionX->value(), ui->sbPositionY->value()),
                rotate,
                ui->cbMirroredHorizontal->isChecked(),
                ui->cbMirroredVertical->isChecked());
}

void ValveSchemeElementDialog::on_buttonBox_accepted()
{
    save(m_valveSchemeElement);
    accept();
}

void ValveSchemeElementDialog::updatePixmap()
{
    if (m_isConfigured)
    {
        ValveSchemeElement valveSchemeElement;
        save(&valveSchemeElement);
        ui->lPixmap->setPixmap(ValveSchemeItem::valvePixmap(&valveSchemeElement, m_canvasSchemeElement->valveFactor(), QFont(m_settingsStorage->value(SettingsKeys::SCHEME_FONT_FAMILY).toString(), m_settingsStorage->value(SettingsKeys::SCHEME_FONT_SIZE).toInt())));
        ui->lPixmap->setMinimumSize(ui->lPixmap->pixmap()->size());
    }
}

qreal ValveSchemeElementDialog::rotateAngleFromUi()
{
    qreal rotate = 0;

    if (ui->rbRotation0->isChecked())
    {
        rotate = 0;
    }
    else if (ui->rbRotation90->isChecked())
    {
        rotate = 90;
    }
    else if (ui->rbRotation180->isChecked())
    {
        rotate = 180;
    }
    else if (ui->rbRotation270->isChecked())
    {
        rotate = 270;
    }

    return rotate;
}



