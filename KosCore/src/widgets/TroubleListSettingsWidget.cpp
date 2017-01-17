#include "TroubleListSettingsWidget.h"
#include "ui_TroubleListSettingsWidget.h"

#include "TroubleListModel.h"
#include "StringsKeys.h"

#include <QJsonDocument>
#include <QJsonArray>

TroubleListSettingsWidget::TroubleListSettingsWidget(QWidget * parent) :
    AbstractSettingsWidget(parent),
    ui(new Ui::TroubleListSettingsWidget)
{
    ui->setupUi(this);

    m_troubleListModel = new TroubleListModel(this);
    ui->tvTroubleList->setModel(m_troubleListModel);

    ui->tvTroubleList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

TroubleListSettingsWidget::~TroubleListSettingsWidget()
{
    delete ui;
}

bool TroubleListSettingsWidget::isSettingsValid()
{
    return true;
}

QString TroubleListSettingsWidget::settingsInvalidText()
{
    return QString();
}

void TroubleListSettingsWidget::settingsLoad()
{
    QJsonDocument document = QJsonDocument::fromJson(m_settingsStorage->value(SettingsKeys::TROUBLE_LIST).toByteArray());
    m_troubleListModel->setTroubles(Trouble::troubleListFromJsonArray(document.array()));
}

void TroubleListSettingsWidget::settingsSave()
{
    m_settingsStorage->setValue(SettingsKeys::TROUBLE_LIST, QJsonDocument(Trouble::troubleListToJsonArray(m_troubleListModel->troubles())).toJson());
}
