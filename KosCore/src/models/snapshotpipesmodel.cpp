#include "snapshotpipesmodel.h"
#include "modeltypes.h"

SnapshotPipesModel::SnapshotPipesModel(QObject *parent)
    : AbstractSnapshotSubstanceModel(parent)
{
}


int SnapshotPipesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent )

    return 1;
}

int SnapshotPipesModel::substanceColumn() const
{
    return COL_SUBSTANCE;
}

QVariant SnapshotPipesModel::newTypedValue()
{
    return Model::Pipe().toVariant();
}

KosTypes::SubstanceType SnapshotPipesModel::substance(const Snapshot::Key &value) const
{
    return m_Snapshot->value(value).value<Model::Pipe>().substance();

}

void SnapshotPipesModel::setSubstance(const Snapshot::Key &value, KosTypes::SubstanceType substance)
{
    Model::Pipe pipe = m_Snapshot->value(value).value<Model::Pipe>();
    pipe.setSubstance(substance);
    m_Snapshot->setValue(value, pipe.toVariant());
}
