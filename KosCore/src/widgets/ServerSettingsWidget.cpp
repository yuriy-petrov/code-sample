#include "ServerSettingsWidget.h"
#include "ui_ServerSettingsWidget.h"

#include "StringsKeys.h"

#include <QInputDialog>
#include <QNetworkInterface>

ServerSettingsWidget::ServerSettingsWidget(bool isInterfaceEditable,
                                           QWidget * parent) :
    AbstractSettingsWidget(parent),
    ui(new Ui::ServerSettingsWidget)
{
    ui->setupUi(this);
    setWindowTitle(tr("Server"));

    ui->leHostAddress->setReadOnly(!isInterfaceEditable);
    ui->tbHostAddress->setVisible(!isInterfaceEditable);
}

ServerSettingsWidget::~ServerSettingsWidget()
{
    delete ui;
}

bool ServerSettingsWidget::isSettingsValid()
{
    return settingsInvalidText().isEmpty();
}

QString ServerSettingsWidget::settingsInvalidText()
{
    if (ui->leHostAddress->text().isEmpty() || QHostAddress(ui->leHostAddress->text()).isNull())
    {
        return tr("Host address is invalid.");
    }
    else
    {
        return QString();
    }
}

void ServerSettingsWidget::settingsLoad()
{
    ui->leHostAddress->setText(m_settingsStorage->value(SettingsKeys::SERVER_ADDRESS).toString());
    ui->sbHostPort->setValue(m_settingsStorage->value(SettingsKeys::SERVER_PORT).toInt());
}

void ServerSettingsWidget::settingsSave()
{
    m_settingsStorage->setValue(SettingsKeys::SERVER_ADDRESS, ui->leHostAddress->text());
    m_settingsStorage->setValue(SettingsKeys::SERVER_PORT, ui->sbHostPort->value());
}

void ServerSettingsWidget::on_tbHostAddress_clicked()
{
    QList<QHostAddress> allAddresses = QNetworkInterface::allAddresses();

    QStringList items;
    foreach (QHostAddress address, allAddresses)
    {
        items.append(address.toString());
    }

    bool isOk = false;
    QString address = QInputDialog::getItem(this, tr("Select..."), tr("Network address:"), items, 0, false, &isOk);
    if (isOk)
    {
        ui->leHostAddress->setText(address);
    }
}
