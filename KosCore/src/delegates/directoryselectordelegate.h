#ifndef DIRECTORYSELECTORDELEGATE_H
#define DIRECTORYSELECTORDELEGATE_H

#include <QStyledItemDelegate>

class DirectorySelectorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DirectorySelectorDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // DIRECTORYSELECTORDELEGATE_H
