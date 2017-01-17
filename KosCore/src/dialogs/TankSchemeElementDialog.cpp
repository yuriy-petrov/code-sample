#include "TankSchemeElementDialog.h"
#include "ui_TankSchemeElementDialog.h"

#include "TankSchemeItem.h"
#include "TankSchemeElement.h"
#include "KosTypesHelper.h"

TankSchemeElementDialog::TankSchemeElementDialog(TankSchemeElement * tankSchemeElement,
                                                 QWidget * parent) :
    QDialog(parent),
    ui(new Ui::TankSchemeElementDialog),
    m_tankSchemeElement(tankSchemeElement)
{
    ui->setupUi(this);

    // Substance types
    m_substanceTypes = KosTypesHelper::instance()->substanceTypeTitles().keys();
    qSort(m_substanceTypes);
    foreach (KosTypes::SubstanceType substanceType, m_substanceTypes)
    {
        ui->cbSubstanceType->addItem( KosTypesHelper::instance()->substanceTypeTitles()[substanceType] );
    }

    m_isConfigured = true;

    load(m_tankSchemeElement);
    updatePixmap();

    QObject::connect(ui->cbSubstanceType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->sbValue, SIGNAL(valueChanged(int)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->sbSizeWidth, SIGNAL(valueChanged(int)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->sbSizeHeight, SIGNAL(valueChanged(int)),
                     this, SLOT(updatePixmap()));
}

TankSchemeElementDialog::~TankSchemeElementDialog()
{
    delete ui;
}

void TankSchemeElementDialog::on_buttonBox_accepted()
{
    save(m_tankSchemeElement);
    accept();
}

void TankSchemeElementDialog::updatePixmap()
{
    if (m_isConfigured)
    {
        TankSchemeElement tankSchemeElement;
        save(&tankSchemeElement);
        ui->lPixmap->setPixmap(TankSchemeItem::tankPixmap(&tankSchemeElement, 1));
        ui->lPixmap->setMinimumSize(ui->lPixmap->pixmap()->size());
    }
}

void TankSchemeElementDialog::load(TankSchemeElement * tankSchemeElement)
{
    ui->cbSubstanceType->setCurrentIndex( m_substanceTypes.indexOf(tankSchemeElement->substanceType()) );
    ui->sbValue->setValue(tankSchemeElement->value());
    ui->cbStretchable->setChecked(tankSchemeElement->stretchable());
    ui->sbPositionX->setValue(tankSchemeElement->position().x());
    ui->sbPositionY->setValue(tankSchemeElement->position().y());
    ui->sbSizeWidth->setValue(tankSchemeElement->size().width());
    ui->sbSizeHeight->setValue(tankSchemeElement->size().height());
}

void TankSchemeElementDialog::save(TankSchemeElement * tankSchemeElement)
{
    tankSchemeElement->setParameters(
            m_substanceTypes[ui->cbSubstanceType->currentIndex()],
            QPointF(ui->sbPositionX->value(), ui->sbPositionY->value()),
            QSize(ui->sbSizeWidth->value(), ui->sbSizeHeight->value()),
            ui->cbStretchable->isChecked(),
            ui->sbValue->value()
        );
}
