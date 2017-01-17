#ifndef NOISEVARIANCEMODEL_H
#define NOISEVARIANCEMODEL_H

#include <QAbstractTableModel>
#include <noisevariance.h>

class NoiseVarianceModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum { COL_VALUE, COL_VARIANCE };

public:
    explicit NoiseVarianceModel(QObject *parent = 0);

    void setNoiseVariance(const Model::NoiseVariance& nv);
    Model::NoiseVariance noiseVariance() const;

    bool isFull() const;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    QStringList woNoiseValues() const;

private:
    Model::NoiseVariance m_NoiseVariance;
    QList<Model::NoiseVariance::key_type> m_Values;
    QList<Snapshot::Key> m_EditableValues;
};

#endif // NOISEVARIANCEMODEL_H
