#include "TextSchemeElementDialog.h"
#include "ui_TextSchemeElementDialog.h"

#include "SettingsStorage.h"
#include "TextSchemeItem.h"
#include "StringsKeys.h"

TextSchemeElementDialog::TextSchemeElementDialog(SettingsStorage * settingsStorage,
                                                 TextSchemeElement * textSchemeElement,
                                                 QWidget * parent) :
    QDialog(parent),
    ui(new Ui::TextSchemeElementDialog),
    m_settingsStorage(settingsStorage),
    m_textSchemeElement(textSchemeElement)
{
    ui->setupUi(this);

    load(m_textSchemeElement);
    updatePixmap();

    QObject::connect(ui->leText, SIGNAL(textChanged(QString)),
                     this, SLOT(updatePixmap()));
    QObject::connect(ui->cbFrameVisible, SIGNAL(toggled(bool)),
                     this, SLOT(updatePixmap()));
}

TextSchemeElementDialog::~TextSchemeElementDialog()
{
    delete ui;
}

qreal TextSchemeElementDialog::rotateAngleFromUi()
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

void TextSchemeElementDialog::load(TextSchemeElement * textSchemeElement)
{
    ui->sbPositionX->setValue(textSchemeElement->position().x());
    ui->sbPositionY->setValue(textSchemeElement->position().y());
    ui->sbScreenOffsetX->setValue(textSchemeElement->screenOffset().x());
    ui->sbScreenOffsetY->setValue(textSchemeElement->screenOffset().y());
    ui->sbPositionY->setValue(textSchemeElement->position().y());
    ui->leText->setText(textSchemeElement->text());
    ui->cbFrameVisible->setChecked(textSchemeElement->frameVisible());
    if (textSchemeElement->frameType() == TextSchemeElement::FrameType::Rect)
    {
        ui->rbFrameTypeRect->setChecked(true);
    }
    else if (textSchemeElement->frameType() == TextSchemeElement::FrameType::Ellipse)
    {
        ui->rbFrameTypeEllipse->setChecked(true);
    }
    ui->sbFontSize->setValue(textSchemeElement->fontSize());

    ui->rbRotation0->setChecked(textSchemeElement->rotation() == 0);
    ui->rbRotation90->setChecked(textSchemeElement->rotation() == 90);
    ui->rbRotation180->setChecked(textSchemeElement->rotation() == 180);
    ui->rbRotation270->setChecked(textSchemeElement->rotation() == 270);
}

void TextSchemeElementDialog::save(TextSchemeElement * textSchemeElement)
{
    textSchemeElement->setParameters(
                QPointF(ui->sbPositionX->value(), ui->sbPositionY->value()),
                ui->leText->text(),
                ui->cbFrameVisible->isChecked(),
                ui->bgFrameType->checkedButton() == ui->rbFrameTypeRect ? TextSchemeElement::FrameType::Rect : TextSchemeElement::FrameType::Ellipse,
                ui->sbFontSize->value(),
                rotateAngleFromUi(),
                QPointF(ui->sbScreenOffsetX->value(), ui->sbScreenOffsetY->value()));
}

void TextSchemeElementDialog::updatePixmap()
{
    TextSchemeElement textSchemeElement;
    save(&textSchemeElement);
    ui->lPixmap->setPixmap(TextSchemeItem::textPixmap(&textSchemeElement, QFont(m_settingsStorage->value(SettingsKeys::SCHEME_FONT_FAMILY).toString(), m_settingsStorage->value(SettingsKeys::SCHEME_FONT_SIZE).toInt())));
    ui->lPixmap->setMinimumSize(ui->lPixmap->pixmap()->size());
}

void TextSchemeElementDialog::on_bgFrameType_buttonToggled(QAbstractButton * button, bool checked)
{
    Q_UNUSED(button);

    if (checked)
    {
        updatePixmap();
    }
}

void TextSchemeElementDialog::on_bgRotation_buttonToggled(QAbstractButton * button, bool checked)
{
    Q_UNUSED(button);

    if (checked)
    {
        updatePixmap();
    }
}

void TextSchemeElementDialog::on_buttonBox_accepted()
{
    save(m_textSchemeElement);
    accept();
}

void TextSchemeElementDialog::on_sbFontSize_valueChanged(int arg1)
{
    updatePixmap();
}
