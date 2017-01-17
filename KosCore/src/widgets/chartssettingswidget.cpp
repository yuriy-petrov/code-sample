#include <StringsKeys.h>
#include <log.h>

#include "chartssettingswidget.h"
#include "chartssettingswidgetprivate.h"
#include "ui_chartssettingswidget.h"

ChartsSettingsWidget::ChartsSettingsWidget(bool isInterfaceEditable,
                                           QWidget *parent)
    : AbstractSettingsWidget(parent)
    , m_Private(new ChartsSettingsWidgetPrivate(this))
{
}

ChartsSettingsWidget::~ChartsSettingsWidget()
{
}

void ChartsSettingsWidget::setCustomValues(const QStringList &values)
{
    m_Private->m_ColorsModel.setCustomValues(values);
}

bool ChartsSettingsWidget::isSettingsValid()
{
    return true;
}

QString ChartsSettingsWidget::settingsInvalidText()
{
    return QString();
}

void ChartsSettingsWidget::settingsLoad()
{
    m_Private->m_Colors.loadFromString(m_settingsStorage->value(SettingsKeys::CHARTS_COLORS).toString());
    m_Private->m_ColorsModel.setColors(m_Private->m_Colors);

    m_Private->m_Units = ChartsUnits::fromString(m_settingsStorage->value(SettingsKeys::CHARTS_UNITS).toString());
    m_Private->m_UnitsLinks = ChartsUnitsLinker::fromString(m_settingsStorage->value(SettingsKeys::CHARTS_UNITS_LINKS).toString());

    m_Private->m_ColorsModel.setUnitsLinks(m_Private->m_UnitsLinks, m_Private->m_Units);
    m_Private->m_UnitsModel.setUnits(m_Private->m_Units);
}

void ChartsSettingsWidget::settingsSave()
{
    m_settingsStorage->setValue(SettingsKeys::CHARTS_COLORS, m_Private->m_ColorsModel.colors().toString());
    m_settingsStorage->setValue(SettingsKeys::CHARTS_UNITS, m_Private->m_UnitsModel.units().toString());
    m_settingsStorage->setValue(SettingsKeys::CHARTS_UNITS_LINKS, m_Private->m_ColorsModel.unitsLinks().toString());
}
