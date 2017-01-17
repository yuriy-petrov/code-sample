#ifndef CIMREXMODELBINDING_H
#define CIMREXMODELBINDING_H

#include <snapshotstorage.h>

class ControllerWidget;

class CimrexModelBinding : public QObject
{
    Q_OBJECT
public:
    CimrexModelBinding(QObject * parent = 0);

    void setStorageSnapshot(SnapshotStorage::Pointer ss);
    void setWidget(ControllerWidget* widget);
    void toogleKey(bool flag);
    void outcommingChanges(QString key, QVariant value);
    void useLastSnapshot();
    bool on();

    SnapshotStorage::Pointer snapshotStorage() const;

private slots:
    void incommingChanges(const Snapshot& s);
private:
    ControllerWidget* _widget;
    SnapshotStorage::Pointer _storage;

    Snapshot _lastSnapShot;
    bool _on;
};

#endif // CIMREXMODELBINDING_H
