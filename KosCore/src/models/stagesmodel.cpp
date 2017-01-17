#include "stagesmodel.h"
#include "modeltypeshelper.h"


//QHash<Model::HystatMode::Type, QString> initModesNames()
//{
//    QHash<Model::HystatMode::Type, QString> names;
//    names.insert(Model::HystatMode::H2Production, QObject::tr("H2Production"));
//    names.insert(Model::HystatMode::H2Purge, QObject::tr("H2Purge"));
//    names.insert(Model::HystatMode::N2Purge, QObject::tr("N2Purge"));
//    names.insert(Model::HystatMode::StandbyH2Production, QObject::tr("StandbyH2Production"));
//    names.insert(Model::HystatMode::StandbyH2Purge, QObject::tr("StandbyH2Purge"));
//    names.insert(Model::HystatMode::StandbyN2Purge, QObject::tr("StandbyN2Purge"));
//    return names;
//}

//static QHash<Model::HystatMode::Type, QString> MODES_NAMES = initModesNames();

StagesModel::StagesModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void StagesModel::setStagesPath(const QString &path)
{
    m_stagesPath = path;
}

void StagesModel::setStages(const Player::Stages &stages)
{
    beginResetModel();
    m_stages = stages;
    m_modes = m_stages.keys();
    endResetModel();
}

int StagesModel::rowCount(const QModelIndex &parent) const
{
    return m_modes.size();
}

int StagesModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant StagesModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    const Player::Stage stage = m_stages.value(m_modes.at(index.row()));

    switch(index.column()) {
    case COL_MODE:
    {
        switch(role) {
        case Qt::EditRole:
        {
            QStringList modes = Model::TypesHelper::hystatModeNames().values();

            foreach(Model::HystatMode::Type mode, m_modes) {
                if(mode != stage.mode()) {
                    modes.removeOne(Model::TypesHelper::hystatModeToString(mode));
                }
            }

            return modes;
        }
        case Qt::DisplayRole:
        {
            return Model::TypesHelper::hystatModeNames().contains(stage.mode()) ?
                        Model::TypesHelper::hystatModeToString(stage.mode()) :
                        tr("???");
        }
        default: break;
        }

        break;
    }
    case COL_NAME:
    {
        switch(role) {
        case Qt::EditRole:
        case Qt::DisplayRole:
        {
            return stage.name();
        }
        default: break;
        }

        break;
    }
    case COL_DATA_PATH:
    {
        switch(role) {
        case Qt::EditRole:
        {
            return m_stagesPath;
        }
        case Qt::DisplayRole:
        {
            return stage.dataPath();
        }
        default: break;
        }

        break;
    }
    }

    return QVariant();
}

bool StagesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Player::Stage& stage = m_stages[m_modes.at(index.row())];

    switch(index.column()) {
    case COL_MODE:
    {
        if(value.toString().isEmpty()) {
            return false;
        }

        Model::HystatMode::Type oldMode = stage.mode();
        stage.setMode(Model::TypesHelper::hystatModeFromString(value.toString()));

        if(oldMode == stage.mode()) {
            return false;
        }

        m_stages[stage.mode()] = stage;
        m_stages.remove(oldMode);
        m_modes.replace(index.row(), stage.mode());

        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
        return true;
    }
    case COL_NAME:
    {
        stage.setName(value.toString());
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);

        return true;
    }
    case COL_DATA_PATH:
    {
        stage.setDataPath(value.toString());
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);

        return true;
    }
    }

    return false;
}

QVariant StagesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(orientation) {
    case Qt::Horizontal:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            switch(section) {
            case COL_MODE:
            {
                return tr("Mode");
            }
            case COL_NAME:
            {
                return tr("Name");
            }
            case COL_DATA_PATH:
            {
                return tr("Data path");
            }
            }
            break;
        }
        default:
        {
            break;
        }
        }

        break;
    }
    case Qt::Vertical:
    {
        break;
    }
    }

    return QVariant();
}

Qt::ItemFlags StagesModel::flags(const QModelIndex &index) const
{
    return
            Qt::ItemIsEnabled |
            Qt::ItemIsSelectable |
            Qt::ItemIsEditable;
}


bool StagesModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if((m_modes.size() + count) >= Model::TypesHelper::hystatModeNames().keys().size()) {
        count = qMin(count, Model::TypesHelper::hystatModeNames().keys().size() - m_modes.size());
    }

    if(count <= 0) {
        return false;
    }

    beginInsertRows(parent, row, row + count - 1);

    for(int i = 0; i < count; ++i) {
        foreach(Model::HystatMode::Type mode, Model::TypesHelper::hystatModeNames().keys()) {
            if(!m_stages.contains(mode)) {
                m_stages.insert(mode, Player::Stage(mode, QString()));
                m_modes << mode;
                break;
            }
        }
    }

    endInsertRows();

    return true;
}

bool StagesModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    QList<Model::HystatMode::Type> modes = m_modes;

    for(int i = row; i < row + count; ++i) {
        m_stages.remove(m_modes.at(row));
        m_modes.removeAt(row);
    }

    endRemoveRows();

    return true;
}
