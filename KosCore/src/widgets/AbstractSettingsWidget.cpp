#include "AbstractSettingsWidget.h"

AbstractSettingsWidget::AbstractSettingsWidget(QWidget * parent) :
    QWidget(parent)
{
}

void AbstractSettingsWidget::setSettingsStorage(SettingsStorage * settingsStorage)
{
    m_settingsStorage = settingsStorage;
}
