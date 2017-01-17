#include "TroubleListController.h"

TroubleListController::TroubleListController(QObject * parent) : QObject(parent)
{
//    insertTrouble(Trouble("key01", tr("Something wrong 01")));
//    insertTrouble(Trouble("key02", tr("Something wrong 02")));
//    insertTrouble(Trouble("key03", tr("Something wrong 03")));
}

TroubleListController::~TroubleListController()
{
}

QList<Trouble> TroubleListController::troubles() const
{
    return m_troubles;
}

QSet<QString> TroubleListController::activeTroubles() const
{
    return m_activeTroubles;
}

void TroubleListController::setTroubles(const QList<Trouble> &troubles)
{
    m_troubles = troubles;
    emit troublesChanged(troubles);
}

void TroubleListController::setActiveTroubles(const QSet<QString> & activeTroubles)
{
    m_activeTroubles = activeTroubles;
    emit activeTroublesChanged(m_activeTroubles);
}
