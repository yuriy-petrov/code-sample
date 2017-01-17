#ifndef MULTILINEDELEGATE_H
#define MULTILINEDELEGATE_H

#include <QStyledItemDelegate>

class MultilineDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MultilineDelegate(QObject *parent = 0);

    // QAbstractItemDelegate interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // MULTILINEDELEGATE_H
