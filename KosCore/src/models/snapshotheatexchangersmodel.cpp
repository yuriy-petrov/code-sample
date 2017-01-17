#include "snapshotheatexchangersmodel.h"
#include "modeltypes.h"

SnapshotHeatExchangersModel::SnapshotHeatExchangersModel(QObject *parent)
    : AbstractSnapshotSubstanceModel(parent)
{
}

int SnapshotHeatExchangersModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

int SnapshotHeatExchangersModel::substanceColumn() const
{
    return COL_SUBSTANCE;
}

QVariant SnapshotHeatExchangersModel::newTypedValue()
{
    return Model::HeatExchanger().toVariant();
}

KosTypes::SubstanceType SnapshotHeatExchangersModel::substance(const Snapshot::Key &value) const
{
    return m_Snapshot->value(value).value<Model::HeatExchanger>().substance();
}

void SnapshotHeatExchangersModel::setSubstance(const Snapshot::Key &value, KosTypes::SubstanceType substance)
{
    Model::HeatExchanger he = m_Snapshot->value(value).value<Model::HeatExchanger>();
    he.setSubstance(substance);
    m_Snapshot->setValue(value, he.toVariant());
}
