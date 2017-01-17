#ifndef CHARTSSETTINGSWIDGETPRIVATE_H
#define CHARTSSETTINGSWIDGETPRIVATE_H

#include <QWidget>
#include <QAbstractButton>

#include <chartssettingsmodel.h>
#include <chartsunitsmodel.h>
#include <ChartsUnits.h>
#include <ChartsUnitsLinker.h>

namespace Ui {
class ChartsColorsSettingsWidget;
}

class ChartsSettingsWidgetPrivate : public QObject
{
    Q_OBJECT
    friend class ChartsSettingsWidget;

public:
    ChartsSettingsWidgetPrivate(QWidget *parent = 0);
    virtual ~ChartsSettingsWidgetPrivate();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void colorsModelDataChanged(const QModelIndex& topLeft,
                                const QModelIndex& bottomRight,
                                const QVector<int> roles = QVector<int>());

    void unitsModelDataChanged(const QModelIndex& topLeft,
                               const QModelIndex& bottomRight,
                               const QVector<int> roles = QVector<int>());

    void on_pushButtonAddUnit_clicked();

    void on_pushButtonRemoveUnit_clicked();

private:
    Ui::ChartsColorsSettingsWidget *ui;
    ChartsColors m_Colors;
    ChartsUnits m_Units;
    ChartsUnitsLinker m_UnitsLinks;
    ChartsSettingsModel m_ColorsModel;
    ChartsUnitsModel m_UnitsModel;
};

#endif // CHARTSSETTINGSWIDGETPRIVATE_H
