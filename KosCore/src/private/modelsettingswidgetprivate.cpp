#include <QMessageBox>

#include "modelsettingswidgetprivate.h"
#include "ui_modelsettingswidget.h"
#include "comboboxitemdelegate.h"
#include "StringsKeys.h"

ModelSettingsWidgetPrivate::ModelSettingsWidgetPrivate(QWidget *parent)
    : QObject(parent)
    , ui(new Ui::ModelSettingsWidget)
{
    ui->setupUi(parent);
    ui->tableViewNoise->setItemDelegateForColumn(NoiseVarianceModel::COL_VALUE,
                                                 new ComboboxItemDelegate(ui->tableViewNoise));
    ui->tableViewNoise->setModel(&m_NoiseVarianceModel);

    m_ModelParametersModel.setKeys(Model::Parameters::keys());
    ui->tableViewParameters->setModel(&m_ModelParametersModel);

    connect(ui->pushButtonAdd, &QPushButton::clicked,
            this, &ModelSettingsWidgetPrivate::on_pushButtonAdd_clicked);
    connect(ui->pushButtonRemove, &QPushButton::clicked,
            this, &ModelSettingsWidgetPrivate::on_pushButtonRemove_clicked);
    connect(ui->tableViewNoise->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &ModelSettingsWidgetPrivate::on_tableViewNoiseSelectionChanged);
}

ModelSettingsWidgetPrivate::~ModelSettingsWidgetPrivate()
{
    delete ui;
}

void ModelSettingsWidgetPrivate::on_pushButtonAdd_clicked()
{
    m_NoiseVarianceModel.insertRow(m_NoiseVarianceModel.rowCount());
    ui->pushButtonAdd->setEnabled(!m_NoiseVarianceModel.isFull());
}

void ModelSettingsWidgetPrivate::on_pushButtonRemove_clicked()
{
    if(ui->tableViewNoise->selectionModel()->selectedRows().isEmpty()) {
        return;
    }

    QMessageBox msgBox(QMessageBox::Warning,
                       tr("Warning"),
                       tr("Delete selected noise variances?"),
                       QMessageBox::Yes | QMessageBox::No,
                       qobject_cast<QWidget*>(parent()));

    if(msgBox.exec() == QMessageBox::No) {
        QList<int> rows;

        foreach(const QModelIndex& index, ui->tableViewNoise->selectionModel()->selectedRows()) {
            rows << index.row();
        }

        int removed = 0;
        foreach(int row, rows) {
            m_NoiseVarianceModel.removeRow(row - removed++);
        }
    }
}

void ModelSettingsWidgetPrivate::on_tableViewNoiseSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    ui->pushButtonRemove->setEnabled(!ui->tableViewNoise->selectionModel()->selectedRows().isEmpty());
}
