#ifndef BLOCKEVENTFILTER_H
#define BLOCKEVENTFILTER_H

#include "AbstractEventFilter.h"

#include <QList>

class BlockEventFilter
{

public:

    enum LogicType
    {
        And = 0,
        Or = 1,
        Not = 2
    };

    enum TimeIntervalType
    {
        Ignore = 0,
        Less = 1,
        More = 2,
    };

    BlockEventFilter();
    ~BlockEventFilter();

    void fromJsonObject(const QJsonObject & jsonObject);
    QJsonObject toJsonObject() const;

    QString title() const;
    void setTitle(const QString & title);

    BlockEventFilter::LogicType logicType() const;
    void setLogicType(const BlockEventFilter::LogicType & logicType);
    const QString& logicTypeName() const;

    BlockEventFilter::TimeIntervalType timeIntervalType() const;
    void setTimeIntervalType(const BlockEventFilter::TimeIntervalType &timeIntervalType);

    int timeInterval() const;
    void setTimeInterval(int timeInterval);

    QList<AbstractEventFilter*> eventFilterList() const;
    void insertEventFilter(AbstractEventFilter * eventFilter, int index);
    void removeEventFilter(AbstractEventFilter * eventFilter);
    void replaceEventFilter(AbstractEventFilter * eventFilter, int index);

    static const QMap<LogicType, QString>& logicTypeNames();
    static const QMap<TimeIntervalType, QString>& timeIntervalTypeNames();

protected:

    void clear();

private:

    QString m_title;
    BlockEventFilter::LogicType m_logicType;
    BlockEventFilter::TimeIntervalType m_timeIntervalType;
    int m_timeInterval;
    QList<AbstractEventFilter*> m_eventFilterList;

};

#endif // BLOCKEVENTFILTER_H
