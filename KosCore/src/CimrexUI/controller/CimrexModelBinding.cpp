#include "CimrexModelBinding.h"
#include "ControllerWidget.h"
#include "StringsKeys.h"
#include "modeltypes.h"
#include "ModelTypesExtractor.h"

CimrexModelBinding::CimrexModelBinding(QObject *parent)
    : QObject(parent),
      _storage(0),
      _on(false)
{
}

void CimrexModelBinding::setStorageSnapshot(SnapshotStorage::Pointer ss)
{
    _storage = ss;
    QObject::connect(_storage.data(), SIGNAL(changed(Snapshot)), SLOT(incommingChanges(Snapshot)));
}

void CimrexModelBinding::setWidget(ControllerWidget *widget)
{
    _widget = widget;
    _widget->setModelBinder(this);
}

void CimrexModelBinding::toogleKey(bool flag)
{
    if (_storage) {
        _storage->setValue(Model::HW_SWITCH, QVariant::fromValue(flag ? Model::On : Model::Off));
    }
}

void CimrexModelBinding::incommingChanges(const Snapshot &s)
{
    _lastSnapShot = s;
    if (s.contains(Model::Power::Switch)) {
        _on = s.value(Model::Power::Switch).toBool();
    }
    QStringList keyList;
    if (_widget) {
        keyList = _widget->currentAvailableKeys();
    }
    foreach (QString key, keyList) {
        if (s.contains(key)) {

            QVariant variantValue = s.value(key);
            if(!variantValue.isValid()) {
                continue;
            }

            //qDebug() << "INCOME values from MODEL!!!!!!!!!!!" << key << s.value(key);
            if ( strcmp(s.value(key).typeName(), QVariant::typeToName(QMetaType::Double)) == 0) {
                QString value = QString::number(s.value(key).toDouble(), 'f' , 2);
                _widget->updateValueForKey(key, value.toDouble());
                continue;
            }
            if ( strcmp(s.value(key).typeName(), QVariant::typeToName(QMetaType::Bool)) == 0 ) {
                QString value = QString("FALSE");
                if (s.value(key).toBool()) {
                    value = QString("TRUE");
                }
                _widget->updateValueForKey(key, value);
                continue;
            }
            if (s.value(key).canConvert<Model::HystatMode::Type>()) {
                qDebug() << "SWITCH";
                QMap<QString, QVariant> values;
                QString key_TEXT_1 = "TEXT_1";
                QString key_TEXT_2 = "TEXT_2";

                QString value;
                switch (s.value(key).value<Model::HystatMode::Type>())
                {
                    case Model::HystatMode::StandbyN2Purge:
                        value = "Standby            N2-Purge";
                        values.insert("VISIBLE_1", "hidden");
                        values.insert("VISIBLE_2", "hidden");
                        break;
                    case Model::HystatMode::N2Purge:
                        value = "N2_Purging ";
                        values.insert("VISIBLE_1", "visible");
                        values.insert("VISIBLE_2", "visible");
                        values.insert(key_TEXT_1, "N2-purge counter");
                        values.insert(key_TEXT_2, "SB1 Timer");
                        values.insert("VALUE_1", s.value(Model::Purge::REMAINING_TIME));
                        values.insert("MP_1", "sec");
                        break;
                    case Model::HystatMode::StandbyH2Purge:
                        value = "Standby      H2-Purge";
                        values.insert("VISIBLE_1", "hidden");
                        values.insert("VISIBLE_2", "hidden");
                        break;
                    case Model::HystatMode::H2Purge:
                        value = "H2_Purging";
                        values.insert("VISIBLE_1", "visible");
                        values.insert("VISIBLE_2", "visible");
                        values.insert(key_TEXT_1, "H2-purge counter");
                        values.insert(key_TEXT_2, "SB1 Timer");
                        values.insert("VALUE_1", s.value(Model::Purge::REMAINING_TIME));
                        values.insert("MP_1", "sec");
                        break;
                    case Model::HystatMode::StandbyH2Production:
                        value = "Standby          H2-Production";
                        values.insert("VISIBLE_1", "hidden");
                        values.insert("VISIBLE_2", "hidden");
                        break;
                    case Model::HystatMode::H2ProductionToAtmosphere:
                        value = "H2-Production       to atmosphere";
                        values.insert("VISIBLE_1", "visible");
                        values.insert("VISIBLE_2", "hidden");
                        values.insert(key_TEXT_1, "Actual Production");
                        values.insert("MP_1", "Nm3/h");
                        break;
                    case Model::HystatMode::H2Production:
                        value = "H2-Production";
                        break;
                    case Model::HystatMode::Depressurization:
                        value = "Depressurization";
                        values.insert("VISIBLE_1", "hidden");
                        values.insert("VISIBLE_2", "hidden");
                        break;
                    case Model::HystatMode::Depressurized:
                        value = "Depressurized";
                        values.insert("VISIBLE_1", "hidden");
                        values.insert("VISIBLE_2", "hidden");
                        break;
                    case Model::HystatMode::EmergencyDepressurization:
                        value = "Emergency Depressurization";
                        break;
                }
                values.insert(key, value);
                _widget->updateValuesForKeys(values);
                continue;
            }
            if (Model::Valves::keys().contains(key)) {
                QString valve_1("VALVE_1");

                Model::TypesExtractor helper(s);
                Model::Valve valve = helper.valve(key);
                if(key == Model::Valves::MV1aO_A) {
                    _widget->updateValueForKey(valve_1, valve.closingLevel());
                }
                _widget->updateValueForKey(key, (int)valve.isOpen());
                continue;
            }
            if (Model::Separators::keys().contains(key)) {
                Model::TypesExtractor helper(s);
                Model::Separator separator = helper.separator(key);
                _widget->updateValueForKey(key, separator.fluidLevel());
                continue;
            }
            if (strcmp(s.value(key).typeName(), QVariant::typeToName(QMetaType::QString)) == 0) {
                QString value = s.value(key).toString();
                _widget->updateValueForKey(key, value);
                continue;
            }
        }
    }
}

void CimrexModelBinding::outcommingChanges(QString key, QVariant value)
{
    if (!_storage.isNull()) {
        _storage->setValue(key, value);
    }
}

void CimrexModelBinding::useLastSnapshot()
{
    incommingChanges(_lastSnapShot);
}

bool CimrexModelBinding::on()
{
    return _on;
}

SnapshotStorage::Pointer CimrexModelBinding::snapshotStorage() const
{
    return _storage;
}

