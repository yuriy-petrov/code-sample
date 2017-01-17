#ifndef EVENTFILTERPROVIDER_H
#define EVENTFILTERPROVIDER_H

#include "StageEventFilter.h"

class EventFilterProvider
{

public:

    EventFilterProvider();
    ~EventFilterProvider();

    QString lastError() const;

    void fromJsonObject(const QJsonObject & jsonObject);
    QJsonObject toJsonObject() const;

    QList<StageEventFilter*> stageEventFilterList() const;
    void insertStageEventFilter(StageEventFilter * stageEventFilter, int index);
    void removeStageEventFilter(StageEventFilter * stageEventFilter);

    bool load(const QString & filepath);
    bool save(const QString & filepath);

private:

    void clear();

private:

    QList<StageEventFilter*> m_stageEventFilterList;
    QString m_lastError;

};

#endif // EVENTFILTERPROVIDER_H
