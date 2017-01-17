#ifndef CHARTSUNITSMODEL_H
#define CHARTSUNITSMODEL_H

#include <QAbstractTableModel>
#include "ChartsUnits.h"

class ChartsUnitsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum {
        COL_NAME,
        COL_LOWER,
        COL_UPPER
    };

public:
    explicit ChartsUnitsModel(QObject *parent = 0);

    void setUnits(const ChartsUnits& units);
    inline const ChartsUnits& units() const;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

private:
    ChartsUnits m_Units;
    QStringList m_Names;
};

const ChartsUnits &ChartsUnitsModel::units() const
{
    return m_Units;
}

#endif // CHARTSUNITSMODEL_H
