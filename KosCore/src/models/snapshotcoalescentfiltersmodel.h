#ifndef SNAPSHOTCOALESCENTFILTERSMODEL_H
#define SNAPSHOTCOALESCENTFILTERSMODEL_H

#include "abstractsnapshotsubstancemodel.h"

class SnapshotCoalescentFiltersModel : public AbstractSnapshotSubstanceModel
{
    Q_OBJECT

public:
    enum { COL_SUBSTANCE };

public:
    explicit SnapshotCoalescentFiltersModel(QObject *parent = 0);

    // QAbstractItemModel interface
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    // AbstractSnapshotSubstanceModel interface
protected:
    int substanceColumn() const;
    QVariant newTypedValue();
    KosTypes::SubstanceType substance(const Snapshot::Key &value) const;
    void setSubstance(const Snapshot::Key &value, KosTypes::SubstanceType substance);
};

#endif // SNAPSHOTCOALESCENTFILTERSMODEL_H
