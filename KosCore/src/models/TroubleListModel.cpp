#include "TroubleListModel.h"

#include "StringsKeys.h"

TroubleListModel::TroubleListModel(QObject * parent) :
    QAbstractTableModel(parent)
{
    foreach (QString key, Model::initialKeys())
    {
        m_troubles.append(Trouble(key, QString()));
    }

    m_columnTitles.insert(Key, tr("Key"));
    m_columnTitles.insert(Description, tr("Description"));
}

TroubleListModel::~TroubleListModel()
{
}

QList<Trouble> TroubleListModel::troubles() const
{
    return m_troubles;
}

int TroubleListModel::rowCount(const QModelIndex & parent) const
{
    if (!parent.isValid())
    {
        return m_troubles.size();
    }

    return 0;
}

int TroubleListModel::columnCount(const QModelIndex & parent) const
{
    if (!parent.isValid())
    {
        return 2;
    }

    return 0;
}

QVariant TroubleListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            return m_columnTitles[(Column)section];
        }
    }
    return QVariant();
}

QVariant TroubleListModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole && index.row() < m_troubles.size())
    {
        Trouble trouble = m_troubles[index.row()];
        switch (index.column())
        {
            case Key: return trouble.key();
            case Description: return trouble.description();
        }
    }

    return QVariant();
}

bool TroubleListModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    Q_UNUSED(role);

    if (index.isValid() && index.column() == Description)
    {
        Trouble trouble = m_troubles[index.row()];
        trouble.setDescription(value.toString());
        m_troubles[index.row()] = trouble;
        return true;
    }

    return false;
}

Qt::ItemFlags TroubleListModel::flags(const QModelIndex & index) const
{
    Qt::ItemFlags flags = Qt::ItemIsEnabled |
            Qt::ItemIsSelectable;
    if (index.column() == Description)
    {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

void TroubleListModel::setTroubles(const QList<Trouble> & troubles)
{
    beginResetModel();
    foreach (Trouble trouble, troubles)
    {
        for (int i = 0; i < m_troubles.size(); ++i)
        {
            if (trouble.key() == m_troubles[i].key())
            {
                m_troubles[i] = trouble;
                break;
            }
        }
    }
    endResetModel();
}

