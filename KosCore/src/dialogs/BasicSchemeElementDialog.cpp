#include "BasicSchemeElementDialog.h"
#include "ui_BasicSchemeElementDialog.h"

#include "BasicSchemeElement.h"
#include "BasicSchemeItem.h"
#include "KosTypesHelper.h"
#include "KosUtils.h"
#include "SettingsStorage.h"
#include "StringsKeys.h"
#include "CanvasSchemeElement.h"

#include <QMessageBox>
#include <QColorDialog>

BasicSchemeElementDialog::BasicSchemeElementDialog(SettingsStorage * settingsStorage,
                                                   CanvasSchemeElement * canvasSchemeElement,
                                                   BasicSchemeElement * basicSchemeElement,
                                                   QWidget * parent) :
    QDialog(parent),
    ui(new Ui::BasicSchemeElementDialog),
    m_settingsStorage(settingsStorage),
    m_canvasSchemeElement(canvasSchemeElement),
    m_basicSchemeElement(basicSchemeElement),
    m_isConfigured(false)
{
    ui->setupUi(this);

    //

    m_basicSchemeElementTypes = KosTypesHelper::instance()->basicElementTypeTitles().keys();
    qSort(m_basicSchemeElementTypes);
    foreach (KosTypes::BasicElementType type, m_basicSchemeElementTypes)
    {
        ui->cbType->addItem( KosTypesHelper::instance()->basicElementTypeTitles()[type] );
    }

    //

    m_substanceTypes = KosTypesHelper::instance()->substanceTypeTitles().keys();
    qSort(m_substanceTypes);
    foreach (KosTypes::SubstanceType substanceType, m_substanceTypes)
    {
        ui->cbSubstanceType->addItem( KosTypesHelper::instance()->substanceTypeTitles()[substanceType] );
    }

    //

    m_isConfigured = true;

    load(m_basicSchemeElement);
    updatePixmap();

    QObject::connect(ui->dsbFactor, SIGNAL(valueChanged(double)),
                     this, SLOT(updatePixmap()));
}

BasicSchemeElementDialog::~BasicSchemeElementDialog()
{
    delete ui;
}

void BasicSchemeElementDialog::load(BasicSchemeElement * basicSchemeElement)
{
    ui->cbType->setCurrentIndex( m_basicSchemeElementTypes.indexOf(basicSchemeElement->type()) );
    ui->sbState->setValue( basicSchemeElement->state() );
    ui->sbPositionX->setValue( basicSchemeElement->position().x() );
    ui->sbPositionY->setValue( basicSchemeElement->position().y() );

    ui->rbRotation0->setChecked(basicSchemeElement->rotation() == 0);
    ui->rbRotation90->setChecked(basicSchemeElement->rotation() == 90);
    ui->rbRotation180->setChecked(basicSchemeElement->rotation() == 180);
    ui->rbRotation270->setChecked(basicSchemeElement->rotation() == 270);

    ui->cbMirroredHorizontal->setChecked(basicSchemeElement->mirroredHorizontal());
    ui->cbMirroredVertical->setChecked(basicSchemeElement->mirroredVertical());

    ui->leOtherColor->setText(KosUtils::instance()->colorToString(basicSchemeElement->color()));
    ui->cbSubstanceType->setCurrentIndex(m_substanceTypes.indexOf(KosTypesHelper::instance()->substanceTypeColors().key(basicSchemeElement->color(), KosTypes::SubstanceType::Invalid)));
    ui->cbOtherStretchable->setChecked(basicSchemeElement->strechable());
    ui->dsbFactor->setValue(basicSchemeElement->factor());
}

void BasicSchemeElementDialog::save(BasicSchemeElement * basicSchemeElement)
{
    qreal rotate = rotateAngleFromUi();

    basicSchemeElement->setParameters(
                m_basicSchemeElementTypes[ui->cbType->currentIndex()],
                ui->sbState->value(),
                QPointF(ui->sbPositionX->value(), ui->sbPositionY->value()),
                rotate,
                ui->cbMirroredHorizontal->isChecked(),
                ui->cbMirroredVertical->isChecked(),
                KosUtils::instance()->colorFromString(ui->leOtherColor->text()),
                ui->cbOtherStretchable->isChecked(),
                ui->dsbFactor->value()
    );
}

void BasicSchemeElementDialog::on_buttonBox_accepted()
{
    if (ui->cbType->currentIndex() == -1)
    {
        QMessageBox::warning(this, tr("Warning..."), tr("Type is not selected."));
    }
    if (ui->dsbFactor->value() == 0)
    {
        QMessageBox::warning(this, tr("Warning..."), tr("Factor is invalid."));
    }
    else
    {
        save(m_basicSchemeElement);
        accept();
    }
}

void BasicSchemeElementDialog::on_cbType_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    updatePixmap();
}

void BasicSchemeElementDialog::on_bgRotation_buttonToggled(QAbstractButton * button, bool checked)
{
    Q_UNUSED(button);
    if (checked)
    {
        updatePixmap();
    }
}

void BasicSchemeElementDialog::on_bgMirrored_buttonToggled(QAbstractButton * button, bool checked)
{
    Q_UNUSED(button);
    Q_UNUSED(checked);
    updatePixmap();
}

void BasicSchemeElementDialog::on_sbState_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    updatePixmap();
}

void BasicSchemeElementDialog::on_tbOtherColor_clicked()
{
    QColor color = QColorDialog::getColor(KosUtils::instance()->colorFromString(ui->leOtherColor->text()), this);
    if (color.isValid())
    {
        ui->leOtherColor->setText(KosUtils::instance()->colorToString(color));
        ui->cbSubstanceType->setCurrentIndex(m_substanceTypes.indexOf(KosTypesHelper::instance()->substanceTypeColors().key(color, KosTypes::SubstanceType::Invalid)));
        updatePixmap();
    }
}

qreal BasicSchemeElementDialog::rotateAngleFromUi()
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

void BasicSchemeElementDialog::updatePixmap()
{
    if (m_isConfigured)
    {
        BasicSchemeElement basicSchemeElement;
        save(&basicSchemeElement);
        ui->lPixmap->setPixmap(BasicSchemeItem::basicPixmap(&basicSchemeElement, m_canvasSchemeElement->basicFactor()));
        ui->lPixmap->setMinimumSize(ui->lPixmap->pixmap()->size());
    }
}

void BasicSchemeElementDialog::on_cbSubstanceType_currentIndexChanged(int index)
{
    if (index != -1)
    {
        QColor color = KosTypesHelper::instance()->substanceTypeColors().value(m_substanceTypes[index]);
        if (color.isValid())
        {
            ui->leOtherColor->setText(KosUtils::instance()->colorToString(color));
        }
        updatePixmap();
    }
}
