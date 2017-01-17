#ifndef MODELPARAMETERSMODEL_H
#define MODELPARAMETERSMODEL_H

#include <QAbstractTableModel>
#include "modelparameters.h"

class ModelParametersModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum { COL_VALUE };

public:
    explicit ModelParametersModel(QObject *parent = 0);

    void setKeys(const QStringList& keys);
    void setParameters(const Model::Parameters::Type& parameters);

    inline const Model::Parameters::Type& parameters() const;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    int size() const;
    const QString& key(int row) const;

private:
    Model::Parameters::Type m_Parameters;
    QStringList m_Keys;
};

const Model::Parameters::Type &ModelParametersModel::parameters() const
{
    return m_Parameters;
}

#endif // MODELPARAMETERSMODEL_H
