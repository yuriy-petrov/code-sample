#ifndef SCHEMESNAPSHOTCONTROLLER_H
#define SCHEMESNAPSHOTCONTROLLER_H

#include <QObject>

#include <snapshot.h>
#include <SchemeSceneManager.h>

class SchemeSnapshotControllerPrivate;
class GroupSchemeSceneManager;

class SchemeSnapshotController : public QObject
{

    Q_OBJECT

public:

    explicit SchemeSnapshotController(QObject * parent = 0);

    void setGroupSchemeSceneManager(GroupSchemeSceneManager * groupSchemeSceneManager);

public slots:

    void setSnapshot(const Snapshot & snapshot);

signals:

    void valueChanged(const QString & key, const QVariant & value);

private slots:

    void valveChangeEvent(const QString & key);

private:

    SchemeSnapshotControllerPrivate * m_private;

};

#endif // SCHEMESNAPSHOTCONTROLLER_H
