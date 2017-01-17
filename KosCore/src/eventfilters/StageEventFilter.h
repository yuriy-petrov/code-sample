#ifndef STAGEEVENTFILTER_H
#define STAGEEVENTFILTER_H

#include "BlockEventFilter.h"
#include "AbstractEventFilter.h"

class StageEventFilter
{

public:

    StageEventFilter();
    ~StageEventFilter();

    void fromJsonObject(const QJsonObject & jsonObject);
    QJsonObject toJsonObject() const;

    QString title() const;
    void setTitle(const QString &title);

    AbstractEventFilter * eventFilter() const;
    void setEventFilter(AbstractEventFilter * eventFilter);

    QList<BlockEventFilter*> blockEventFilterList() const;
    void insertBlockEventFilter(BlockEventFilter * blockEventFilter, int index);
    void removeBlockEventFilter(BlockEventFilter * blockEventFilter);

protected:

    void clear();

private:

    QString m_title;
    AbstractEventFilter * m_eventFilter;
    QList<BlockEventFilter*> m_blockEventFilterList;

};

#endif // STAGEEVENTFILTER_H
