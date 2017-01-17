#include <log.h>

#include "schemesnapshotcontrollerprivate.h"
#include "StringsKeys.h"
#include "modeltypes.h"
#include "ModelTypesExtractor.h"

#include <SchemeSceneManager.h>
#include <SchemeDataProvider.h>

SchemeSnapshotControllerPrivate::SchemeSnapshotControllerPrivate(QObject * parent) :
    QObject(parent),
    m_groupSchemeSceneManager(NULL)
{
}

void SchemeSnapshotControllerPrivate::updateScheme()
{
    Q_ASSERT(m_groupSchemeSceneManager != NULL);

    updateValves();
    updatePipes();
    updateSeparators(Model::Separators::keys());
    updateSeparators(Model::WaterLocks::keys());
    updateCoalescentFilters();
    updateRinsers();
    updateHeatExchangers();
    updateManometers();
}

void SchemeSnapshotControllerPrivate::updateValves()
{
    foreach (QString schemeKey, m_groupSchemeSceneManager->schemeKeys())
    {
        foreach (const QString & key, Model::Valves::keys())
        {
            const QVariant v = m_snapshot.value(key);
            ValveSchemeElement * schElement = m_groupSchemeSceneManager->schemeSceneManager(schemeKey)->schemeDataProvider()->valveElementContainer()->element(key);

            if (!v.isValid() || v.isNull() || (schElement == NULL))
            {
                continue;
            }

            const Model::Valve valve = v.value<Model::Valve>();
            schElement->setClosePercentage(valve.closingLevel());
            schElement->setSubstanceType(valve.substanceType());
            schElement->setValid(valve.status() == Model::Valve::Normal);
        }
    }
}

void SchemeSnapshotControllerPrivate::updatePipes()
{
    foreach (QString schemeKey, m_groupSchemeSceneManager->schemeKeys())
    {
        foreach (const QString & key, Model::Pipes::keys())
        {
            const QVariant v = m_snapshot.value(key);
            PipelineSchemeElement* schElement = m_groupSchemeSceneManager->schemeSceneManager(schemeKey)->schemeDataProvider()->pipelineElementContainer()->element(key);

            if (!v.isValid() || v.isNull() || (schElement == NULL))
            {
                continue;
            }

            const Model::Pipe pipe = v.value<Model::Pipe>();
            schElement->setSubstanceType(pipe.substance());
        }
    }
}

void SchemeSnapshotControllerPrivate::updateSeparators(const QStringList &keys)
{
    foreach (QString schemeKey, m_groupSchemeSceneManager->schemeKeys())
    {
        foreach(const QString& key, keys)
        {
            const QVariant v = m_snapshot.value(key);
            LevelSchemeElement* schElement = m_groupSchemeSceneManager->schemeSceneManager(schemeKey)->schemeDataProvider()->levelSchemeElementContainer()->element(key);

            if (!v.isValid() || v.isNull() || (schElement == NULL))
            {
                continue;
            }

            const Model::Separator separator = v.value<Model::Separator>();
            schElement->setFirstSubstanceType(separator.gas());
            schElement->setSecondSubstanceType(separator.fluid());
            schElement->setValue(separator.fluidLevel());
        }
    }
}

void SchemeSnapshotControllerPrivate::updateCoalescentFilters()
{
    foreach (QString schemeKey, m_groupSchemeSceneManager->schemeKeys())
    {
        foreach(const QString& key, Model::CoalescentFilters::keys())
        {
            const QVariant v = m_snapshot.value(key);
            BasicSchemeElement* schElement = m_groupSchemeSceneManager->schemeSceneManager(schemeKey)->schemeDataProvider()->basicElementContainer()->element(key);

            if (!v.isValid() || v.isNull() || (schElement == NULL))
            {
                continue;
            }

            const Model::CoalescentFilter cf = v.value<Model::CoalescentFilter>();
            schElement->setSubstanceType(cf.substance());
        }
    }
}

void SchemeSnapshotControllerPrivate::updateRinsers()
{
    foreach (QString schemeKey, m_groupSchemeSceneManager->schemeKeys())
    {
        foreach(const QString& key, Model::Rinsers::keys()) {
            const QVariant v = m_snapshot.value(key);
            BasicSchemeElement* schElement = m_groupSchemeSceneManager->schemeSceneManager(schemeKey)->schemeDataProvider()->basicElementContainer()->element(key);

            if(!v.isValid() || v.isNull() || (schElement == NULL)) {
                continue;
            }

            const Model::Rinser rinser = v.value<Model::Rinser>();
            schElement->setSubstanceType(rinser.substance());
        }
    }
}

void SchemeSnapshotControllerPrivate::updateHeatExchangers()
{
    foreach (QString schemeKey, m_groupSchemeSceneManager->schemeKeys())
    {
        foreach (const QString& key, Model::HeatExchangers::keys())
        {
            const QVariant v = m_snapshot.value(key);
            BasicSchemeElement* schElement = m_groupSchemeSceneManager->schemeSceneManager(schemeKey)->schemeDataProvider()->basicElementContainer()->element(key);

            if (!v.isValid() || v.isNull() || (schElement == NULL))
            {
                continue;
            }

            const Model::HeatExchanger he = v.value<Model::HeatExchanger>();
            schElement->setSubstanceType(he.substance());
        }
    }
}

void SchemeSnapshotControllerPrivate::updateManometers()
{
    foreach (QString schemeKey, m_groupSchemeSceneManager->schemeKeys())
    {
        Model::TypesExtractor extractor(m_snapshot);
        TextSchemeElement * schElement;
        double pressure;

        schElement = m_groupSchemeSceneManager->schemeSceneManager(schemeKey)->schemeDataProvider()->textSchemeElementContainer()->element(Model::Manometers::M_PTGS);
        if(schElement) {
            pressure = extractor.value(Model::ChartsValues::PTGS);
            schElement->setText(QString("%1 кПа").arg(pressure, 0, 'f', 1));
        }

        schElement = m_groupSchemeSceneManager->schemeSceneManager(schemeKey)->schemeDataProvider()->textSchemeElementContainer()->element(Model::Manometers::M_RCV_N);
        if(schElement) {
            pressure = extractor.value(Model::Purge::N2_PRESSURE);
            schElement->setText(QString("%1 кПа").arg(pressure, 0, 'f', 1));
        }
    }
}
