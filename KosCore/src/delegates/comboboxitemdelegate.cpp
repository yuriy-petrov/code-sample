#include <QComboBox>

#include "comboboxitemdelegate.h"

ComboboxItemDelegate::ComboboxItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *ComboboxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED( option )
    QComboBox *cb = new QComboBox(parent);
    cb->addItems(index.data(Qt::EditRole).toStringList());
    return cb;
}

void ComboboxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(QComboBox *cb = qobject_cast<QComboBox *>(editor)) {
        // get the index of the text in the combobox that matches the current value of the item
        QString currentText = index.data(Qt::DisplayRole).toString();
        int cbIndex = cb->findText(currentText, Qt::MatchFixedString);
        // if it is valid, adjust the combobox
        if(cbIndex >= 0) {
            cb->setCurrentIndex(cbIndex);
        }
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void ComboboxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(QComboBox *cb = qobject_cast<QComboBox *>(editor)) {
        model->setData(index, cb->currentText(), Qt::EditRole);
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}
