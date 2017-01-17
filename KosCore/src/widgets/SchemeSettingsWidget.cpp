#include "SchemeSettingsWidget.h"
#include "ui_SchemeSettingsWidget.h"

#include "StringsKeys.h"

SchemeSettingsWidget::SchemeSettingsWidget(QWidget *parent) :
    AbstractSettingsWidget(parent),
    ui(new Ui::SchemeSettingsWidget)
{
    ui->setupUi(this);
}

SchemeSettingsWidget::~SchemeSettingsWidget()
{
    delete ui;
}

bool SchemeSettingsWidget::isSettingsValid()
{
    return settingsInvalidText().isEmpty();
}

QString SchemeSettingsWidget::settingsInvalidText()
{
    if (ui->fcbFontFamily->currentIndex() == -1)
    {
        return tr("Font family is invalid.");
    }
    else if (ui->sbFontSize->value() == 0)
    {
        return tr("Font size is invalid.");
    }

    return QString();
}

void SchemeSettingsWidget::settingsLoad()
{
    QFont schemeFont(m_settingsStorage->value(SettingsKeys::SCHEME_FONT_FAMILY).toString(), m_settingsStorage->value(SettingsKeys::SCHEME_FONT_SIZE).toInt());

    ui->fcbFontFamily->setCurrentFont(schemeFont);
    ui->sbFontSize->setValue(schemeFont.pointSize());
}

void SchemeSettingsWidget::settingsSave()
{
    m_settingsStorage->setValue(SettingsKeys::SCHEME_FONT_FAMILY, ui->fcbFontFamily->currentFont().family());
    m_settingsStorage->setValue(SettingsKeys::SCHEME_FONT_SIZE, ui->sbFontSize->value());
}
