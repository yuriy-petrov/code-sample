#ifndef BUTTONEVENTFILTER_H
#define BUTTONEVENTFILTER_H

#include <QObject>
#include <QLabel>
#include <QEvent>
#include <snapshotstorage.h>

class ButtonEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit ButtonEventFilter(QObject *parent = 0);

    void setEmergencyButton(QLabel * label);
    void setResetButton(QLabel * label);
    void setSnapshotStorage(SnapshotStorage::Pointer storage);
    bool eventFilter(QObject * o, QEvent * e);

private:
    QLabel * m_emergencyButton;
    QLabel * m_resetButton;
    SnapshotStorage::Pointer m_snapshotStorage;
};

#endif // BUTTONEVENTFILTER_H
