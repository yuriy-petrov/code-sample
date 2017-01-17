#include <QMessageBox>

#include <log.h>
#include "playersettingswidgetprivate.h"
#include "ui_playersettingswidget.h"
#include "comboboxitemdelegate.h"
#include "directoryselectordelegate.h"

PlayerSettingsWidgetPrivate::PlayerSettingsWidgetPrivate(QWidget *parent)
    : QObject(parent)
    , ui(new Ui::PlayerSettingsWidget)
{
    ui->setupUi(parent);
    connect(ui->toolButtonAdd, SIGNAL(clicked()), SLOT(on_toolButtonAdd_clicked()));
    connect(ui->toolButtonRemove, SIGNAL(clicked()), SLOT(on_toolButtonRemove_clicked()));

    ui->tableView->setItemDelegateForColumn(StagesModel::COL_MODE,
                                            new ComboboxItemDelegate(ui->tableView));
    ui->tableView->setItemDelegateForColumn(StagesModel::COL_DATA_PATH,
                                            new DirectorySelectorDelegate(ui->tableView));

    ui->tableView->setModel(&m_stagesModel);
}

PlayerSettingsWidgetPrivate::~PlayerSettingsWidgetPrivate()
{
    LOG << "DESTROY:" << this;
    delete ui;
}

void PlayerSettingsWidgetPrivate::on_toolButtonAdd_clicked()
{
    ui->toolButtonAdd->setEnabled(m_stagesModel.insertRow(m_stagesModel.rowCount()));
}

void PlayerSettingsWidgetPrivate::on_toolButtonRemove_clicked()
{
    if(ui->tableView->selectionModel()->selectedRows().isEmpty()) {
        return;
    }

    QMessageBox msgBox(QMessageBox::Warning,
                       tr("Warning"),
                       tr("Delete selected stages?"),
                       QMessageBox::Yes | QMessageBox::No,
                       qobject_cast<QWidget*>(parent()));

    if(msgBox.exec() == QMessageBox::No) {
        QList<int> rows;

        foreach(const QModelIndex& index, ui->tableView->selectionModel()->selectedRows()) {
            rows << index.row();
        }

        int removed = 0;
        foreach(int row, rows) {
            m_stagesModel.removeRow(row - removed++);
        }
    }

    ui->toolButtonRemove->setEnabled(m_stagesModel.rowCount() > 0);
}
