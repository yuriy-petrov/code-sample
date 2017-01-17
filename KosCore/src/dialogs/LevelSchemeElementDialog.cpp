#include "LevelSchemeElementDialog.h"
#include "ui_LevelSchemeElementDialog.h"

#include "KosTypesHelper.h"
#include "LevelSchemeElement.h"
#include "LevelSchemeItem.h"
#include "CanvasSchemeElement.h"

LevelSchemeElementDialog::LevelSchemeElementDialog(CanvasSchemeElement * canvasSchemeElement,
                                                   LevelSchemeElement * levelSchemeElement,
                                                   QWidget * parent) :
    QDialog(parent),
    ui(new Ui::LevelSchemeElementDialog),
    m_canvasSchemeElement(canvasSchemeElement),
    m_levelSchemeElement(levelSchemeElement),
    m_isConfigured(false)
{
    ui->setupUi(this);

    // Level element types
    m_levelElementTypes = KosTypesHelper::instance()->levelElementTypeTitles().keys();
    qSort(m_levelElementTypes);
    foreach (KosTypes::LevelElementType levelElementType, m_levelElementTypes)
    {
        ui->cbLevelType->addItem( KosTypesHelper::instance()->levelElementTypeTitles()[levelElementType] );
    }

    // Substance types
    m_substanceTypes = KosTypesHelper::instance()->substanceTypeTitles().keys();
    qSort(m_substanceTypes);
    foreach (KosTypes::SubstanceType substanceType, m_substanceTypes)
    {
        ui->cbFirstSubstanceType->addItem( KosTypesHelper::instance()->substanceTypeTitles()[substanceType] );
        ui->cbSecondSubstanceType->addItem( KosTypesHelper::instance()->substanceTypeTitles()[substanceType] );
    }

    m_isConfigured = true;

    load(m_levelSchemeElement);
    updatePixmap();

    QObject::connect(ui->cbLevelType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->cbFirstSubstanceType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->cbSecondSubstanceType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->cbStretchable, SIGNAL(toggled(bool)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->sbValue, SIGNAL(valueChanged(int)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->cbMirroredHorizontal, SIGNAL(toggled(bool)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->cbMirroredVertical, SIGNAL(toggled(bool)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->dsbFactor, SIGNAL(valueChanged(double)),
                     this, SLOT(updatePixmap()));
}

LevelSchemeElementDialog::~LevelSchemeElementDialog()
{
    delete ui;
}

void LevelSchemeElementDialog::updatePixmap()
{
    if (m_isConfigured)
    {
        LevelSchemeElement levelSchemeElement;
        save(&levelSchemeElement);
        ui->lPixmap->setPixmap(LevelSchemeItem::levelPixmap(&levelSchemeElement, m_canvasSchemeElement->levelFactor() * levelSchemeElement.factor()));
        ui->lPixmap->setMinimumSize(ui->lPixmap->pixmap()->size());
    }
}

void LevelSchemeElementDialog::on_buttonBox_accepted()
{
    save(m_levelSchemeElement);
    accept();
}

void LevelSchemeElementDialog::load(LevelSchemeElement * levelSchemeElement)
{
    ui->cbLevelType->setCurrentIndex( m_levelElementTypes.indexOf(levelSchemeElement->levelElementType()) );
    ui->cbFirstSubstanceType->setCurrentIndex( m_substanceTypes.indexOf(levelSchemeElement->firstSubstanceType()) );
    ui->cbSecondSubstanceType->setCurrentIndex( m_substanceTypes.indexOf(levelSchemeElement->secondSubstanceType()) );
    ui->sbValue->setValue(levelSchemeElement->value());
    ui->dsbFactor->setValue(levelSchemeElement->factor());
    ui->cbStretchable->setChecked(levelSchemeElement->stretchable());
    ui->cbMirroredHorizontal->setChecked(levelSchemeElement->mirroredHorizontal());
    ui->cbMirroredVertical->setChecked(levelSchemeElement->mirroredVertical());
    ui->sbPositionX->setValue(levelSchemeElement->position().x());
    ui->sbPositionY->setValue(levelSchemeElement->position().y());
}

void LevelSchemeElementDialog::save(LevelSchemeElement * levelSchemeElement)
{
    levelSchemeElement->setParameters(
                m_levelElementTypes[ui->cbLevelType->currentIndex()],
                m_substanceTypes[ui->cbFirstSubstanceType->currentIndex()],
                m_substanceTypes[ui->cbSecondSubstanceType->currentIndex()],
                ui->sbValue->value(),
                QPointF(ui->sbPositionX->value(), ui->sbPositionY->value()),
                ui->cbStretchable->isChecked(),
                ui->cbMirroredHorizontal->isChecked(),
                ui->cbMirroredVertical->isChecked(),
                ui->dsbFactor->value());
}
