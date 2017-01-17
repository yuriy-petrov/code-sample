#ifndef EVENTLOGANALYZER_H
#define EVENTLOGANALYZER_H

class EventLogProvider;
class AbstractEventLogElement;
class EventFilterProvider;
class FileDataStorage;
class StageEventFilter;
class BlockEventFilter;

#include "CommentEventLogElement.h"

#include <QObject>

class EventLogAnalyzer : public QObject
{

    Q_OBJECT

public:

    explicit EventLogAnalyzer(EventLogProvider * eventLogProvider,
                              EventFilterProvider * stagesEventFilterProvider,
                              EventFilterProvider * modesEventFilterProvider,
                              FileDataStorage * fileDataStorage,
                              QObject * parent = 0);
    ~EventLogAnalyzer();

public slots:

    void reset();
    void appendEventLogElement(AbstractEventLogElement * eventLogElement);

signals:

    void unsuccessfullyFinished(const QString & errorText);
    void successfullyFinished();

protected:

    void appendCommentEventLogElement(AbstractEventLogElement::CheckedState checkedState, const QString & text);
    bool processStage(StageEventFilter * stageEventFilter, AbstractEventLogElement * eventLogElement, bool mode);
    bool checkStage(StageEventFilter * stageEventFilter, QList<AbstractEventLogElement*> & eventLogElements, QString & errorText);
    bool checkBlock(BlockEventFilter * blockEventFilter, QList<AbstractEventLogElement*> & eventLogElements, QString & errorText, QDateTime & finishTime);

private:

    EventLogProvider * m_eventLogProvider;
    EventFilterProvider * m_stagesEventFilterProvider;
    EventFilterProvider * m_modesEventFilterProvider;

    EventFilterProvider * m_currentStagesEventFilterProvider;
    EventFilterProvider * m_currentModesEventFilterProvider;
    FileDataStorage * m_fileDataStorage;

    QList<AbstractEventLogElement*> m_currentEventLogElements;

};

#endif // EVENTLOGANALYZER_H
