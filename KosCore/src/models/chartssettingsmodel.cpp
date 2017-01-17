#include "StringsKeys.h"

#include "chartssettingsmodel.h"

ChartsSettingsModel::ChartsSettingsModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    normalizeColors();
    normalizeUnits(m_Units);
}

void ChartsSettingsModel::setColors(const ChartsColors &colors)
{
    beginResetModel();

    m_Colors = colors;
    normalizeColors();

    endResetModel();
}

void ChartsSettingsModel::setUnitsLinks(const ChartsUnitsLinker& links, const ChartsUnits& units)
{
    beginResetModel();

    m_UnitsLinks = links;
    normalizeUnits(units);

    endResetModel();
}

void ChartsSettingsModel::setCustomValues(const QStringList &values)
{
    beginResetModel();
    m_CustomValues = values;
    endResetModel();
}

int ChartsSettingsModel::rowCount(const QModelIndex &parent) const
{
    return m_CustomValues.isEmpty() ?
                Model::ChartsValues::keys().size() :
                m_CustomValues.size();
}

int ChartsSettingsModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ChartsSettingsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    const QString value = values().at(index.row());

    switch(index.column()) {
    case COL_COLOR:
    {
        switch(role) {
        case Qt::EditRole:
        case Qt::BackgroundColorRole:
        {
            return m_Colors.color(value);
        }
        default:
        {
            break;
        }
        }

        break;
    }
    case COL_UNIT:
    {
        switch(role) {
        case Qt::EditRole:
        {
            QStringList units = m_Units.keys();
            qSort(units);
            return units;
        }
        case Qt::DisplayRole:
        {
            return m_UnitsLinks[value];
        }
        case Qt::TextAlignmentRole:
        {
            return Qt::AlignRight;
        }
        default:
        {
            break;
        }
        }
    }
    }

    return QVariant();
}

QVariant ChartsSettingsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(orientation) {
    case Qt::Horizontal:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            switch(section) {
            case COL_COLOR: return tr("Color");
            case COL_UNIT: return tr("Unit");
            }
            break;
        }
        }

        break;
    }
    case Qt::Vertical:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            return values().at(section);
        }
        }

        break;
    }
    }

    return QVariant();
}

Qt::ItemFlags ChartsSettingsModel::flags(const QModelIndex &index) const
{
    switch(index.column()) {
    case COL_COLOR:
        return Qt::ItemIsEnabled;
    default:
        return
                Qt::ItemIsEnabled |
                Qt::ItemIsSelectable |
                Qt::ItemIsEditable;
    }

    return Qt::NoItemFlags;
}


bool ChartsSettingsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) {
        return false;
    }

    switch(index.column()) {
    case COL_COLOR:
    {
        switch(role) {
        case Qt::EditRole:
        {
            if(!value.canConvert<QColor>()) {
                return false;
            }

            m_Colors.setColor(values().at(index.row()), value.value<QColor>());
            emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);

            return true;
        }
        }

        break;
    }
    case COL_UNIT:
    {
        switch(role) {
        case Qt::EditRole:
        {
            m_UnitsLinks[values().at(index.row())] = value.toString();
            emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);

            return true;
        }
        }

        break;
    }
    }

    return false;
}

void ChartsSettingsModel::normalizeColors()
{
    if(m_Colors.isEmpty()) {
        foreach(const QString& key, values()) {
            m_Colors.setColor(key, "blue");
        }
    } else {
        QStringList chartsKeys = values();
        // Model::chartsKeys() --> m_Colors
        foreach(const QString& key, chartsKeys) {
            if(!m_Colors.contains(key)) {
                m_Colors.setColor(key, "blue");
            }
        }

        foreach(const QString& key, m_Colors.keys()) {
            if(!chartsKeys.contains(key)) {
                m_Colors.remove(key);
            }
        }
    }
}

void ChartsSettingsModel::normalizeUnits(const ChartsUnits& units)
{
    QString newName;
    QString oldName;

    foreach(const QString& name, units.keys()) {
        if(!m_Units.contains(name)) {
            newName = name;
            break;
        }
    }

    foreach(const QString& name, m_Units.keys()) {
        if(!units.contains(name)) {
            oldName = name;
            break;
        }
    }

    foreach(const Snapshot::Key& key, m_UnitsLinks.keys()) {
        if(m_UnitsLinks[key] == oldName) {
            m_UnitsLinks[key] = newName;
        }
    }

    m_Units = units;

//    if(m_Limits.isEmpty()) {
//        foreach(const QString& key, values()) {
//            m_Limits.setLimit(key, ChartsLimit(0, 100));
//        }
//    } else {
//        QStringList chartsKeys = values();
//        // Model::chartsKeys() --> m_Limits
//        foreach(const QString& key, chartsKeys) {
//            if(!m_Limits.contains(key)) {
//                m_Limits.setLimit(key, ChartsLimit(0, 100));
//            }
//        }

//        foreach(const QString& key, m_Limits.keys()) {
//            if(!chartsKeys.contains(key)) {
//                m_Limits.remove(key);
//            }
//        }
//    }
}

QStringList ChartsSettingsModel::values() const
{
    return m_CustomValues.isEmpty() ?
                Model::ChartsValues::keys() :
                m_CustomValues;
}
