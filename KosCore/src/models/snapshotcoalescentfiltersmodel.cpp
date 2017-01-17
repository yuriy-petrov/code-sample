#include "snapshotcoalescentfiltersmodel.h"
#include "modeltypes.h"

SnapshotCoalescentFiltersModel::SnapshotCoalescentFiltersModel(QObject *parent)
    : AbstractSnapshotSubstanceModel(parent)
{
}

int SnapshotCoalescentFiltersModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

int SnapshotCoalescentFiltersModel::substanceColumn() const
{
    return COL_SUBSTANCE;
}

QVariant SnapshotCoalescentFiltersModel::newTypedValue()
{
    return Model::CoalescentFilter().toVariant();
}

KosTypes::SubstanceType SnapshotCoalescentFiltersModel::substance(const Snapshot::Key &value) const
{
    return m_Snapshot->value(value).value<Model::CoalescentFilter>().substance();
}

void SnapshotCoalescentFiltersModel::setSubstance(const Snapshot::Key &value, KosTypes::SubstanceType substance)
{
    Model::CoalescentFilter cf = m_Snapshot->value(value).value<Model::CoalescentFilter>();
    cf.setSubstance(substance);
    m_Snapshot->setValue(value, cf.toVariant());
}
