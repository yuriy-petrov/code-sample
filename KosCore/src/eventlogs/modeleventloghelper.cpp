#include "modeleventloghelper.h"
#include "StringsKeys.h"
#include "modeltypeshelper.h"

#include <QObject>
#include <log.h>

QJsonValue ModelEventLogHelper::toJsonValue(const QString &key, const QVariant &value)
{
    if(key == Model::HYSTAT_Mode) {
        return QJsonValue(mode(value));
    } else if((key == Model::Power::Switch) ||
              (key == Model::CellStack::Enable::CS1) ||
              (key == Model::CellStack::Enable::CS2) ||
              (key == Model::CellStack::Enable::CS3) ||
              (key == Model::CellStack::Enable::CS4)) {
        return QJsonValue(powerOn(value));
    } else if(key == Model::HW_SWITCH) {
        return QJsonValue(value.value<Model::HwSwitchPos>());
    }

    return QJsonValue();
}

QVariant ModelEventLogHelper::fromJsonValue(const QString& key, const QJsonValue &jsonValue)
{
    if(key == Model::HYSTAT_Mode) {
        return QVariant::fromValue(static_cast<Model::HystatMode::Type>(jsonValue.toInt()));
    } else if((key == Model::Power::Switch) ||
              (key == Model::CellStack::Enable::CS1) ||
              (key == Model::CellStack::Enable::CS2) ||
              (key == Model::CellStack::Enable::CS3) ||
              (key == Model::CellStack::Enable::CS4)) {
        return jsonValue.toBool();
    } else if(key == Model::HW_SWITCH) {
        return QVariant::fromValue(static_cast<Model::HwSwitchPos>(jsonValue.toInt()));
    }

    return QVariant();
}

Model::HystatMode::Type ModelEventLogHelper::mode(const QVariant &value)
{
    if(value.canConvert<Model::HystatMode::Type>()) {
        return value.value<Model::HystatMode::Type>();
    } else {
        return Model::HystatMode::Invalid;
    }
}

bool ModelEventLogHelper::powerOn(const QVariant &value)
{
    if(value.canConvert<bool>()) {
        return value.toBool();
    } else {
        return false;
    }
}

QString ModelEventLogHelper::eventDescription(const QString &key, const QVariant &value)
{
    if(key == Model::HYSTAT_Mode) {
        return QObject::tr("Mode changed to %1").arg(Model::TypesHelper::hystatModeToString(value.value<Model::HystatMode::Type>()));
    } else if((key == Model::Power::Switch) ||
              (key == Model::CellStack::Enable::CS1) ||
              (key == Model::CellStack::Enable::CS2) ||
              (key == Model::CellStack::Enable::CS3) ||
              (key == Model::CellStack::Enable::CS4) ||
              (key == Model::HW_SWITCH))
    {
        return filterDescription(key, value);
    }

    return QObject::tr("Invalid event");
}

QString ModelEventLogHelper::filterDescription(const QString &key, const QVariant &value)
{
    if(key == Model::HYSTAT_Mode) {
        return QString("%1 = %2")
                .arg(key)
                .arg(Model::TypesHelper::hystatModeToString(value.value<Model::HystatMode::Type>()));
    } else if(key == Model::Power::Switch) {
        return value.toBool() ?
                    QObject::tr("Power is on") :
                    QObject::tr("Power is off");
    } else if(key == Model::CellStack::Enable::CS1) {
        return QObject::tr("Cell Stack 1 is %1")
                .arg(value.toBool() ? QObject::tr("enabled") : QObject::tr("disabled"));
    } else if(key == Model::CellStack::Enable::CS2) {
        return QObject::tr("Cell Stack 2 is %1")
                .arg(value.toBool() ? QObject::tr("enabled") : QObject::tr("disabled"));
    } else if(key == Model::CellStack::Enable::CS3) {
        return QObject::tr("Cell Stack 3 is %1")
                .arg(value.toBool() ? QObject::tr("enabled") : QObject::tr("disabled"));
    } else if(key == Model::CellStack::Enable::CS4) {
        return QObject::tr("Cell Stack 4 is %1")
                .arg(value.toBool() ? QObject::tr("enabled") : QObject::tr("disabled"));
    } else if(key == Model::HW_SWITCH) {
        return QObject::tr("Key moved to %1")
                .arg(Model::TypesHelper::hwSwitchPosToString(value.value<Model::HwSwitchPos>()));
    }
}

ModelEventLogElement *ModelEventLogHelper::generateEventLogElement(const QString &key, const QVariant &value)
{
    ModelEventLogElement * eventLogElement = NULL;

    if( (key == Model::HYSTAT_Mode) ||
        (key == Model::Power::Switch) ||
        (key == Model::CellStack::Enable::CS1) ||
        (key == Model::CellStack::Enable::CS2) ||
        (key == Model::CellStack::Enable::CS3) ||
        (key == Model::CellStack::Enable::CS4) ||
        (key == Model::HW_SWITCH)
        )
    {
        eventLogElement = new ModelEventLogElement(key, value);
    }

//    LOG << "GENERATE EVENT:" << key;

    return eventLogElement;
}
