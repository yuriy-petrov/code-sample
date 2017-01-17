#ifndef CHARTSSETTINGSMODEL_H
#define CHARTSSETTINGSMODEL_H

#include <QAbstractTableModel>

#include "chartscolors.h"
#include "ChartsUnits.h"
#include "ChartsUnitsLinker.h"

class ChartsSettingsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum {
        COL_COLOR = 0,
        COL_UNIT = 1
    };

public:
    explicit ChartsSettingsModel(QObject *parent = 0);

    void setColors(const ChartsColors& colors);
    inline const ChartsColors& colors() const;

    void setUnitsLinks(const ChartsUnitsLinker& links, const ChartsUnits& units);
    inline const ChartsUnitsLinker& unitsLinks() const;

    void setCustomValues(const QStringList& values);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    // QAbstractItemModel interface
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

private:
    void normalizeColors();
    void normalizeUnits(const ChartsUnits& units);

    QStringList values() const;

private:
    ChartsColors m_Colors;
    ChartsUnitsLinker m_UnitsLinks;
    ChartsUnits m_Units;
    QStringList m_CustomValues;
};

const ChartsColors &ChartsSettingsModel::colors() const
{
    return m_Colors;
}

const ChartsUnitsLinker &ChartsSettingsModel::unitsLinks() const
{
    return m_UnitsLinks;
}

#endif // CHARTSSETTINGSMODEL_H
