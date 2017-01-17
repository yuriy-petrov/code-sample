#include "multilinedelegate.h"
#include <QPainter>
#include <QTextLayout>
#include <log.h>

MultilineDelegate::MultilineDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


void MultilineDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    qreal height = 0;

    QStyledItemDelegate::paint(painter, option, QModelIndex());

    foreach(const QString& line, index.data().toString().split(QChar('\n'))) {
        QTextLayout layout(line);
        layout.setFont(option.font);
        layout.beginLayout();

        while(true) {
            QTextLine line = layout.createLine();
            if(!line.isValid()) {
                break;
            }
            line.setLineWidth(option.rect.width());
            height += option.fontMetrics.leading();
            line.setPosition(QPointF(0, height));
            height += option.fontMetrics.height();
        }

        layout.endLayout();

        //    if(option.state.testFlag(QStyle::State_Selected)) {
        //        painter->setBrush(Qt::blue);
        //        LOG << "selected!";
        //    }

        //    painter->drawRect(option.rect);

        layout.draw(painter, option.rect.topLeft());
    }

    painter->restore();
}

QSize MultilineDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qreal height = 0;

    QSize size = QStyledItemDelegate::sizeHint(option, index);

    if(size.width() == 0) {
        height = option.fontMetrics.leading() + option.fontMetrics.height();
    } else {
        foreach(const QString& line, index.data().toString().split(QChar('\n'))) {
            QTextLayout layout(line);
            layout.setFont(option.font);
            layout.beginLayout();


            while(true) {
                QTextLine line = layout.createLine();
                if(!line.isValid()) {
                    break;
                }
                line.setLineWidth(size.width());
                height += option.fontMetrics.leading();
                line.setPosition(QPointF(0, height));
                height += option.fontMetrics.height();
            }
            layout.endLayout();
        }
    }

    size.setHeight(height);

    return QSize(option.rect.width(), height);
}
