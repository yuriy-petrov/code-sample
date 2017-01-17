#include "snapshotrinsersmodel.h"
#include "modeltypes.h"

SnapshotRinsersModel::SnapshotRinsersModel(QObject *parent)
    : AbstractSnapshotSubstanceModel(parent)
{
}

int SnapshotRinsersModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

int SnapshotRinsersModel::substanceColumn() const
{
    return COL_SUBSTANCE;
}

QVariant SnapshotRinsersModel::newTypedValue()
{
    return Model::Rinser().toVariant();
}

KosTypes::SubstanceType SnapshotRinsersModel::substance(const Snapshot::Key &value) const
{
    return m_Snapshot->value(value).value<Model::Rinser>().substance();
}

void SnapshotRinsersModel::setSubstance(const Snapshot::Key &value, KosTypes::SubstanceType substance)
{
    Model::Rinser rinser = m_Snapshot->value(value).value<Model::Rinser>();
    rinser.setSubstance(substance);
    m_Snapshot->setValue(value, rinser.toVariant());
}
