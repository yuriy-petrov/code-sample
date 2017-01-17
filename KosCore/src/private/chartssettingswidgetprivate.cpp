#include "chartssettingswidgetprivate.h"
#include "ui_chartssettingswidget.h"

#include <QColorDialog>
#include <comboboxitemdelegate.h>

ChartsSettingsWidgetPrivate::ChartsSettingsWidgetPrivate(QWidget *parent)
    : QObject(parent)
    , ui(new Ui::ChartsColorsSettingsWidget)
{
    ui->setupUi(parent);
    ui->tableViewColors->setItemDelegateForColumn(ChartsSettingsModel::COL_UNIT,
                                                  new ComboboxItemDelegate(ui->tableViewColors));

    parent->setWindowTitle(tr("Charts"));

    ui->tableViewColors->setModel(&m_ColorsModel);
    ui->tableViewUnits->setModel(&m_UnitsModel);

    connect(ui->buttonBox, &QDialogButtonBox::clicked,
            this, &ChartsSettingsWidgetPrivate::on_buttonBox_clicked);
    connect(ui->pushButtonAddUnit, &QPushButton::clicked,
            this, &ChartsSettingsWidgetPrivate::on_pushButtonAddUnit_clicked);
    connect(ui->pushButtonRemoveUnit, &QPushButton::clicked,
            this, &ChartsSettingsWidgetPrivate::on_pushButtonRemoveUnit_clicked);
    connect(ui->tableViewColors, &QTableView::doubleClicked,
            this, &ChartsSettingsWidgetPrivate::on_tableView_doubleClicked);
    connect(&m_ColorsModel, &ChartsSettingsModel::dataChanged,
            this, &ChartsSettingsWidgetPrivate::colorsModelDataChanged);
    connect(&m_UnitsModel, &ChartsSettingsModel::dataChanged,
            this, &ChartsSettingsWidgetPrivate::unitsModelDataChanged);
}

ChartsSettingsWidgetPrivate::~ChartsSettingsWidgetPrivate()
{
    delete ui;
}

void ChartsSettingsWidgetPrivate::on_buttonBox_clicked(QAbstractButton *button)
{
    switch(ui->buttonBox->buttonRole(button)) {
    case QDialogButtonBox::ResetRole:
    {
        m_ColorsModel.setColors(m_Colors);
        m_ColorsModel.setUnitsLinks(m_UnitsLinks, m_Units);
        ui->buttonBox->setEnabled(false);
        break;
    }
    default:
    {
        break;
    }
    }
}

void ChartsSettingsWidgetPrivate::on_tableView_doubleClicked(const QModelIndex &index)
{
    switch(index.column()) {
    case ChartsSettingsModel::COL_COLOR:
    {
        QColorDialog dialog(index.data(Qt::BackgroundColorRole).value<QColor>(), dynamic_cast<QWidget*>(parent()));

        if(dialog.exec() == QDialog::Accepted) {
            m_ColorsModel.setData(index, QVariant::fromValue(dialog.selectedColor()));
            ui->buttonBox->setEnabled(true);
        }

        break;
    }
    }
}

void ChartsSettingsWidgetPrivate::colorsModelDataChanged(const QModelIndex &topLeft,
                                                         const QModelIndex &bottomRight,
                                                         const QVector<int> roles)
{
    ui->buttonBox->setEnabled(true);
}

void ChartsSettingsWidgetPrivate::unitsModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> roles)
{
    m_ColorsModel.setUnitsLinks(m_ColorsModel.unitsLinks(), m_UnitsModel.units());
}

void ChartsSettingsWidgetPrivate::on_pushButtonAddUnit_clicked()
{
    m_UnitsModel.insertRow(m_UnitsModel.rowCount());
}

void ChartsSettingsWidgetPrivate::on_pushButtonRemoveUnit_clicked()
{
    const QModelIndexList selection = ui->tableViewUnits->selectionModel()->selectedRows();
    if(!selection.isEmpty()) {
        m_UnitsModel.removeRows(selection.first().row(), selection.size(), QModelIndex());
    }
}
