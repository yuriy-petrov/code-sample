#include "InterfaceSettingsWidget.h"
#include "ui_InterfaceSettingsWidget.h"

#include "StringsKeys.h"
#include "SettingsStorage.h"

#include <QFileDialog>

InterfaceSettingsWidget::InterfaceSettingsWidget(TranslationManager * translationManager,
                                                 QWidget * parent) :
    AbstractSettingsWidget(parent),
    ui(new Ui::InterfaceSettingsWidget),
    m_translationManager(translationManager)
{
    ui->setupUi(this);
    setWindowTitle(tr("Interface"));

    ui->cbLanguage->addItem(SettingsKeys::LANGUAGE_DEFAULT);
    ui->cbLanguage->addItems(m_translationManager->languages());
}

InterfaceSettingsWidget::~InterfaceSettingsWidget()
{
    delete ui;
}

bool InterfaceSettingsWidget::isSettingsValid()
{
    return this->settingsInvalidText().isEmpty();
}

QString InterfaceSettingsWidget::settingsInvalidText()
{
    if (ui->cbLanguage->currentIndex() == -1)
    {
        return tr("Language is invalid.");
    }
    else
    {
        return QString();
    }
}

void InterfaceSettingsWidget::settingsLoad()
{
    QString language = m_settingsStorage->value(SettingsKeys::LANGUAGE).toString();
    if (
            !language.isEmpty() &&
            m_translationManager->languages().contains(language) &&
            language != SettingsKeys::LANGUAGE_DEFAULT
       )
    {
        ui->cbLanguage->setCurrentIndex(m_translationManager->languages().indexOf(language) + 1);
    }
    else
    {
        ui->cbLanguage->setCurrentIndex(0);
    }

    ui->leTranslationsDir->setText(m_settingsStorage->value(SettingsKeys::TRANSLATION_DIR).toString());
}

void InterfaceSettingsWidget::settingsSave()
{
    m_settingsStorage->setValue(SettingsKeys::LANGUAGE, ui->cbLanguage->currentText());
    m_settingsStorage->setValue(SettingsKeys::TRANSLATION_DIR, ui->leTranslationsDir->text());
}

void InterfaceSettingsWidget::on_tbTranslationsDir_clicked()
{
    QString dirpath = QFileDialog::getExistingDirectory(this, tr("Open translations directory..."), ui->leTranslationsDir->text());
    if (!dirpath.isEmpty())
    {
        ui->leTranslationsDir->setText(dirpath);
    }
}
