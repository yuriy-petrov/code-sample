#include "buttoneventfilter.h"
#include "StringsKeys.h"

ButtonEventFilter::ButtonEventFilter(QObject *parent)
    : QObject(parent)
    , m_emergencyButton(NULL)
    , m_resetButton(NULL)
{
}

void ButtonEventFilter::setEmergencyButton(QLabel *label)
{
    m_emergencyButton = label;
    m_emergencyButton->installEventFilter(this);
}

void ButtonEventFilter::setResetButton(QLabel *label)
{
    m_resetButton = label;
    m_resetButton->installEventFilter(this);
}

void ButtonEventFilter::setSnapshotStorage(SnapshotStorage::Pointer storage)
{
     m_snapshotStorage = storage;
}

bool ButtonEventFilter::eventFilter(QObject *o, QEvent *e)
{
    if(m_snapshotStorage.isNull()) {
        return false;
    }

    switch(e->type()) {
        case QEvent::MouseButtonRelease:
        {
            if(o == m_emergencyButton) {
                m_snapshotStorage->setValue(Model::EMERGENCY_BUTTON, true);
            } else if(o == m_resetButton) {
                m_snapshotStorage->setValue(Model::EMERGENCY_BUTTON, true);
            }

            break;
        }
    }

    return false;
}
