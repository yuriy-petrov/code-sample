#ifndef MODELVALUESDELEGATE_H
#define MODELVALUESDELEGATE_H

#include <QStyledItemDelegate>

class ModelValuesDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ModelValuesDelegate(QObject *parent = 0);


    // QAbstractItemDelegate interface
public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // MODELVALUESDELEGATE_H
