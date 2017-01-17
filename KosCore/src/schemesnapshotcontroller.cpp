#include "schemesnapshotcontroller.h"
#include "schemesnapshotcontrollerprivate.h"

#include "valve.h"

#include <GroupSchemeSceneManager.h>
#include <SchemeSceneManager.h>
#include <SchemeItemContainer.h>
#include <ValveSchemeElement.h>
#include <SchemeDataProvider.h>
#include <AbstractSchemeItemContainer.h>

SchemeSnapshotController::SchemeSnapshotController(QObject * parent) :
    QObject(parent),
    m_private(new SchemeSnapshotControllerPrivate(this))
{
}

void SchemeSnapshotController::setGroupSchemeSceneManager(GroupSchemeSceneManager * groupSchemeSceneManager)
{
    m_private->m_groupSchemeSceneManager = groupSchemeSceneManager;

    foreach (QString schemeKey, groupSchemeSceneManager->schemeKeys())
    {
        QObject::connect(groupSchemeSceneManager->schemeSceneManager(schemeKey)->valveSchemeItemContainer(), SIGNAL(itemChanged(QString)),
                         this, SLOT(valveChangeEvent(QString)));
    }
}

void SchemeSnapshotController::setSnapshot(const Snapshot & snapshot)
{
    m_private->m_snapshot = snapshot;
    m_private->updateScheme();
}

void SchemeSnapshotController::valveChangeEvent(const QString & key)
{
    AbstractSchemeItemContainer * abstractContainer = (AbstractSchemeItemContainer*)sender();
    AbstractSchemeElement * abstractElement = abstractContainer->abstractElementContainer()->abstractElement(key);

    if (abstractElement)
    {
        ValveSchemeElement * valveElement = dynamic_cast<ValveSchemeElement*>(abstractElement);
        if (valveElement)
        {
            Model::Valve valve;
            valve.setClosingLevel(valveElement->closePercentage());
            valve.setSubstanceType(valveElement->substanceType());
            valve.setStatus(valveElement->isValid() ? Model::Valve::Normal : Model::Valve::Faulted);
            emit valueChanged(key, valve.toVariant());
        }
    }
}
