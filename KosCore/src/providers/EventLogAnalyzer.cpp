#include "EventLogAnalyzer.h"

#include "EventFilterProvider.h"
#include "EventLogProvider.h"
#include "filedatastorage.h"
#include "SnapshotCondition.h"

#include <QDebug>

EventLogAnalyzer::EventLogAnalyzer(EventLogProvider * eventLogProvider,
                                   EventFilterProvider * stagesEventFilterProvider,
                                   EventFilterProvider * modesEventFilterProvider,
                                   FileDataStorage * fileDataStorage,
                                   QObject * parent) :
    QObject(parent),
    m_eventLogProvider(eventLogProvider),
    m_stagesEventFilterProvider(stagesEventFilterProvider),
    m_modesEventFilterProvider(modesEventFilterProvider),
    m_fileDataStorage(fileDataStorage)
{
    m_currentStagesEventFilterProvider = new EventFilterProvider;
    m_currentModesEventFilterProvider = new EventFilterProvider;
}

EventLogAnalyzer::~EventLogAnalyzer()
{
    delete m_currentModesEventFilterProvider;
    delete m_currentStagesEventFilterProvider;
}

void EventLogAnalyzer::reset()
{
    m_currentStagesEventFilterProvider->fromJsonObject(m_stagesEventFilterProvider->toJsonObject());
    m_currentEventLogElements.clear();
}

void EventLogAnalyzer::appendEventLogElement(AbstractEventLogElement * eventLogElement)
{
    m_eventLogProvider->appendEventLogElement(eventLogElement);

    if (m_currentStagesEventFilterProvider->stageEventFilterList().isEmpty())
    {
        // Упражнение закончилось, либо фильтры не настроены
        appendCommentEventLogElement(AbstractEventLogElement::CheckedState::CheckedFail, tr("list of stages is empty"));
    }
    else
    {
        StageEventFilter * stageEventFilter = m_currentStagesEventFilterProvider->stageEventFilterList().first();
        if (!processStage(stageEventFilter, eventLogElement, false))
        {
            m_currentModesEventFilterProvider->fromJsonObject(m_modesEventFilterProvider->toJsonObject());
            foreach (StageEventFilter * stageEventFilter, m_currentModesEventFilterProvider->stageEventFilterList())
            {
                if (processStage(stageEventFilter, eventLogElement, true))
                {
                    return;
                }
            }
        }
    }
}

void EventLogAnalyzer::appendCommentEventLogElement(AbstractEventLogElement::CheckedState checkedState, const QString & text)
{
    CommentEventLogElement * commentEventLogElement = new CommentEventLogElement();
    commentEventLogElement->setCheckedState(checkedState);
    commentEventLogElement->setText(text);
    m_eventLogProvider->appendEventLogElement(commentEventLogElement);
}

bool EventLogAnalyzer::processStage(StageEventFilter * stageEventFilter, AbstractEventLogElement * eventLogElement, bool mode)
{
    AbstractEventFilter * eventFilter = stageEventFilter->eventFilter();
    if (eventFilter == NULL)
    {
        // Некорректная ситуация - фильтр этапа не задан
        appendCommentEventLogElement(AbstractEventLogElement::CheckedState::CheckedFail, tr("checkpoint of stage \"%1\" is empty").arg(stageEventFilter->title()));
    }
    else
    {
        QString snapshotConditionError;
        if (eventFilter->eventLogType() == eventLogElement->eventLogType() && eventFilter->check(eventLogElement) && eventFilter->snapshotCondition()->check(m_fileDataStorage, eventLogElement->modelDatetime(), snapshotConditionError))
        {
            QString errorText;
            if (checkStage(stageEventFilter, m_currentEventLogElements, errorText))
            {
                if (!mode)
                {
                    m_currentStagesEventFilterProvider->removeStageEventFilter(stageEventFilter);
                }

                QString stageTitle = stageEventFilter->title();
                m_currentEventLogElements.clear();

                appendCommentEventLogElement(AbstractEventLogElement::CheckedState::CheckedPass, mode ? tr("mode \"%1\" was passed").arg(stageTitle) : tr("stage \"%1\" was passed").arg(stageTitle));
                if (!mode && m_currentStagesEventFilterProvider->stageEventFilterList().isEmpty())
                {
                    emit successfullyFinished();
                }
            }
            else
            {
                appendCommentEventLogElement(AbstractEventLogElement::CheckedState::CheckedFail, mode ? tr("mode \"%1\" was failed: %2").arg(stageEventFilter->title()).arg(errorText) : tr("stage \"%1\" was failed: %2").arg(stageEventFilter->title()).arg(errorText));
                emit unsuccessfullyFinished(errorText);
            }
        }
        else
        {
            m_currentEventLogElements.append(eventLogElement);
            return false;
        }
    }

    return true;
}

bool EventLogAnalyzer::checkStage(StageEventFilter * stageEventFilter, QList<AbstractEventLogElement*> & eventLogElements, QString & errorText)
{
    QDateTime finishTime;

    while (!stageEventFilter->blockEventFilterList().isEmpty())
    {
        BlockEventFilter * blockEventFilter = stageEventFilter->blockEventFilterList().last();

        if (blockEventFilter->timeIntervalType() != BlockEventFilter::TimeIntervalType::Ignore && finishTime != QDateTime())
        {
            if (!eventLogElements.isEmpty())
            {
                QDateTime dateTime = eventLogElements.last()->realDatetime();
                if (blockEventFilter->timeIntervalType() == BlockEventFilter::TimeIntervalType::Less)
                {
                    if (dateTime.secsTo(finishTime) >= blockEventFilter->timeInterval())
                    {
                        errorText = tr("time interval of block \"%1\" is not sustained").arg(blockEventFilter->title());
                        return false;
                    }
                }
                else if (blockEventFilter->timeIntervalType() == BlockEventFilter::TimeIntervalType::More)
                {
                    if (dateTime.secsTo(finishTime) <= blockEventFilter->timeInterval())
                    {
                        errorText = tr("time interval of block \"%1\" is not sustained").arg(blockEventFilter->title());
                        return false;
                    }
                }
            }
        }

        if (checkBlock(blockEventFilter, eventLogElements, errorText, finishTime))
        {
            stageEventFilter->removeBlockEventFilter(blockEventFilter);
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool EventLogAnalyzer::checkBlock(BlockEventFilter * blockEventFilter, QList<AbstractEventLogElement *> & eventLogElements, QString & errorText, QDateTime & finishTime)
{
    if (blockEventFilter->eventFilterList().isEmpty())
    {
        errorText = tr("event filter list of block is empty");
        return false;
    }

    QHash<AbstractEventFilter*,QString> snapshotConditionErrors;

    int index = -1;
    for (int i = eventLogElements.size() - 1; i >= 0 ; --i)
    {
        AbstractEventLogElement * eventLogElement = eventLogElements[i];
        for (int j = 0; j < blockEventFilter->eventFilterList().size(); ++j)
        {
            AbstractEventFilter * eventFilter = blockEventFilter->eventFilterList()[j];
            if (eventFilter->eventLogType() == eventLogElement->eventLogType())
            {
                QString snapshotConditionError;
                bool snapshotConditionResult = eventFilter->snapshotCondition()->check(m_fileDataStorage, eventLogElement->modelDatetime(), snapshotConditionError);
                if (!snapshotConditionResult)
                {
                    snapshotConditionErrors.insert(eventFilter, snapshotConditionError);
                }

                if (eventFilter->check(eventLogElement) && snapshotConditionResult)
                {
                    index = i;
                    blockEventFilter->removeEventFilter(eventFilter);
                    --j;

                    if (blockEventFilter->logicType() == BlockEventFilter::LogicType::And || blockEventFilter->logicType() == BlockEventFilter::LogicType::Or)
                    {
                        eventLogElement->setCheckedState(AbstractEventLogElement::CheckedState::CheckedPass);
                    }
                    else if (blockEventFilter->logicType() == BlockEventFilter::LogicType::Not)
                    {
                        eventLogElement->setCheckedState(AbstractEventLogElement::CheckedState::CheckedFail);
                    }
                }
            }
        }
    }

    switch (blockEventFilter->logicType())
    {
        case BlockEventFilter::LogicType::And:
        {
            if (blockEventFilter->eventFilterList().isEmpty() && index != -1)
            {
                finishTime = eventLogElements.last()->realDatetime();
                while (eventLogElements.size() != index)
                {
                    eventLogElements.removeLast();
                }
                return true;
            }
            else
            {
                errorText = tr("block \"%1\" with logic AND failed").arg(blockEventFilter->title());
                foreach (AbstractEventFilter * eventFilter, blockEventFilter->eventFilterList())
                {
                    errorText += "\n - " + eventFilter->fullDescription();
                    if (snapshotConditionErrors.contains(eventFilter))
                    {
                        errorText += " (" + snapshotConditionErrors.value(eventFilter) + ")";
                    }
                }
                return false;
            }
        }
        case BlockEventFilter::LogicType::Or:
        {
            if (index != -1)
            {
                finishTime = eventLogElements.last()->realDatetime();
                while (eventLogElements.size() != index)
                {
                    eventLogElements.removeLast();
                }
                return true;
            }
            else
            {
                errorText = tr("block \"%1\" with logic OR failed").arg(blockEventFilter->title());
                foreach (AbstractEventFilter * eventFilter, blockEventFilter->eventFilterList())
                {
                    errorText += "\n - " + eventFilter->fullDescription();
                    if (snapshotConditionErrors.contains(eventFilter))
                    {
                        errorText += " (" + snapshotConditionErrors.value(eventFilter) + ")";
                    }
                }
                return false;
            }
        }
        case BlockEventFilter::LogicType::Not:
        {
            if (index == -1)
            {
                finishTime = QDateTime();
                return true;
            }
            else
            {
                errorText = tr("block \"%1\" with logic NOT failed - %2").arg(blockEventFilter->title()).arg(eventLogElements[index]->description());
                return false;
            }
        }
    }

    return false;
}

