#include "modeltypeshelper.h"
#include "StringsKeys.h"
#include <QObject>

using namespace Model;

QMap<HystatMode::Type, QString> initHystatModeNames()
{
    QMap<HystatMode::Type, QString> names;
    names.insert(HystatMode::StandbyN2Purge, QObject::tr("Standby N2 purge"));
    names.insert(HystatMode::N2Purge, QObject::tr("N2 purge"));
    names.insert(HystatMode::StandbyH2Purge, QObject::tr("Standby H2 purge"));
    names.insert(HystatMode::H2Purge, QObject::tr("H2 purge"));
    names.insert(HystatMode::StandbyH2Production, QObject::tr("Standby H2 production"));
    names.insert(HystatMode::H2ProductionToAtmosphere, QObject::tr("H2 production to atmosphere"));
    names.insert(HystatMode::H2Production, QObject::tr("H2 production"));
    names.insert(HystatMode::Depressurization, QObject::tr("Depressurization"));
    names.insert(HystatMode::Depressurized, QObject::tr("Depressurized"));
    names.insert(HystatMode::EmergencyDepressurization, QObject::tr("EmergencyDepressurization"));

    return names;
}

QMap<bool, QString> initCellStackEnableNames()
{
    QMap<bool, QString> names;

    names.insert(false, QObject::tr("Disabled"));
    names.insert(true, QObject::tr("Enabled"));

    return names;
}

QMap<HwSwitchPos, QString> initHwSwitchPosNames()
{
    QMap<HwSwitchPos, QString> names;
    names.insert(On, QObject::tr("On"));
    names.insert(Off, QObject::tr("Off"));

    return names;
}
const QMap<HystatMode::Type, QString> &TypesHelper::hystatModeNames()
{
    static QMap<HystatMode::Type, QString> names = initHystatModeNames();
    return names;
}

QString TypesHelper::hystatModeToString(HystatMode::Type mode)
{
    return
            hystatModeNames().contains(mode) ?
                hystatModeNames()[mode] :
                QString();
}

HystatMode::Type TypesHelper::hystatModeFromString(const QString &name)
{
    return hystatModeNames().key(name);
}

const QMap<HwSwitchPos, QString> &TypesHelper::hwSwitchPosNames()
{
    static QMap<HwSwitchPos, QString> names = initHwSwitchPosNames();
    return names;
}

QString TypesHelper::hwSwitchPosToString(HwSwitchPos pos)
{
    return
            hwSwitchPosNames().contains(pos) ?
                hwSwitchPosNames()[pos] :
                QString();
}

HwSwitchPos TypesHelper::hwSwitchPosFromString(const QString & name)
{
    return hwSwitchPosNames().key(name);
}

const QMap<bool, QString> &TypesHelper::cellStackEnableNames()
{
    static QMap<bool, QString> names = initCellStackEnableNames();
    return names;
}

QJsonValue TypesHelper::toJsonValue(const QString &key, const QVariant &value)
{
    if( Model::ChartsValues::keys().contains(key) ||
        (key == Model::Purge::N2_PRESSURE)
        )
    {
        return QJsonValue(value.toDouble());
    } else if(Model::CellStack::Enable::keys().contains(key)) {
        return QJsonValue(value.toBool());
    }

    return QJsonValue();
}

QVariant TypesHelper::fromJsonValue(const QString &key, const QJsonValue &value)
{
    if( Model::ChartsValues::keys().contains(key) ||
        (key == Model::Purge::N2_PRESSURE) ||
        Model::CellStack::Enable::keys().contains(key)
        )
    {
        return value.toVariant();
    }

    return QVariant();
}

QString TypesHelper::toString(const QString &key, const QVariant &value)
{
    if( Model::ChartsValues::keys().contains(key) ||
        (key == Model::Purge::N2_PRESSURE)
        )
    {
        return QString::number(value.toDouble());
    } else if(Model::CellStack::Enable::keys().contains(key)) {
        return cellStackEnableNames().value(value.toBool());
    } else if(key == HYSTAT_Mode) {
        return hystatModeNames().value(value.value<Model::HystatMode::Type>());
    }

    return QObject::tr("Unknown");
}

QVariant TypesHelper::fromString(const QString &key, const QString &value)
{
    if( Model::ChartsValues::keys().contains(key) ||
        (key == Model::Purge::N2_PRESSURE)
        )
    {
        return value.toDouble();
    } else if(Model::CellStack::Enable::keys().contains(key)) {
        return cellStackEnableNames().key(value);
    } else if(key == HYSTAT_Mode) {
        return hystatModeNames().key(value);
    }

    return QObject::tr("Unknown");
}

QVariant TypesHelper::initValue(const QString &key)
{
    if( Model::ChartsValues::keys().contains(key) ||
        (key == Model::Purge::N2_PRESSURE)
        )
    {
        return 0.0;
    } else if(Model::CellStack::Enable::keys().contains(key)) {
        return false;
    } else if(key == HYSTAT_Mode) {
        return QVariant::fromValue<Model::HystatMode::Type>(Model::HystatMode::StandbyN2Purge);
    }

    return QVariant();
}

bool TypesHelper::sameTypes(const QString &key1, const QString &key2)
{
    return
            (key1 == key2) ||
            (Model::ChartsValues::keys().contains(key1) && Model::ChartsValues::keys().contains(key2)) ||
            ((Model::CellStack::Enable::keys().contains(key1)) && (Model::CellStack::Enable::keys().contains(key2)))
            ;
}

QStringList TypesHelper::valuesNames(const QString &key)
{
    if(Model::CellStack::Enable::keys().contains(key)) {
        return cellStackEnableNames().values();
    } else if(key == HYSTAT_Mode) {
        return hystatModeNames().values();
    }

    return QStringList();
}
