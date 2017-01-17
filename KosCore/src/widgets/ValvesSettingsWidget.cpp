#include "ValvesSettingsWidget.h"
#include "ui_ValvesSettingsWidget.h"

#include "StringsKeys.h"

ValvesSettingsWidget::ValvesSettingsWidget(bool isInterfaceEditable,
                                           QWidget * parent) :
    AbstractSettingsWidget(parent),
    ui(new Ui::ValvesSettingsWidget)
{
    ui->setupUi(this);

    m_currentValvesModel = new QStringListModel(this);
    m_availabelValvesModel = new QStringListModel(this);

    ui->lvCurrent->setModel(m_currentValvesModel);
    ui->lvAvailable->setModel(m_availabelValvesModel);
}

ValvesSettingsWidget::~ValvesSettingsWidget()
{
    delete ui;
}

bool ValvesSettingsWidget::isSettingsValid()
{
    return true;
}

QString ValvesSettingsWidget::settingsInvalidText()
{
    return QString();
}

void ValvesSettingsWidget::settingsLoad()
{
    QStringList prevValves = m_settingsStorage->value(SettingsKeys::CLIENT_INTERACTIVE_VALVE_LIST).toStringList();
    QStringList currentValves;
    QStringList availableValves;
    foreach (QString line, Model::Valves::keys())
    {
        if (prevValves.contains(line))
        {
            currentValves.append(line);
        }
        else
        {
            availableValves.append(line);
        }
    }
    m_currentValvesModel->setStringList(currentValves);
    m_currentValvesModel->sort(0);
    m_availabelValvesModel->setStringList(availableValves);
    m_availabelValvesModel->sort(0);
}

void ValvesSettingsWidget::settingsSave()
{
    m_settingsStorage->setValue(SettingsKeys::CLIENT_INTERACTIVE_VALVE_LIST, m_currentValvesModel->stringList());
}

void ValvesSettingsWidget::on_tbRemove_clicked()
{
    QModelIndex index = ui->lvCurrent->currentIndex();
    if (index.isValid())
    {
        QVariant valve = m_currentValvesModel->data(index, Qt::DisplayRole);
        m_currentValvesModel->removeRow(index.row());

        QStringList lines = m_availabelValvesModel->stringList();
        lines.append(valve.toString());
        m_availabelValvesModel->setStringList(lines);
        m_availabelValvesModel->sort(0);
    }
}

void ValvesSettingsWidget::on_tbAdd_clicked()
{
    QModelIndex index = ui->lvAvailable->currentIndex();
    if (index.isValid())
    {
        QVariant valve = m_availabelValvesModel->data(index, Qt::DisplayRole);
        m_availabelValvesModel->removeRow(index.row());

        QStringList lines = m_currentValvesModel->stringList();
        lines.append(valve.toString());
        m_currentValvesModel->setStringList(lines);
        m_currentValvesModel->sort(0);
    }
}
