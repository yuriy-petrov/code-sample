#include <QFileDialog>
#include <log.h>

#include "directoryselectordelegate.h"

DirectorySelectorDelegate::DirectorySelectorDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *DirectorySelectorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED( option )

    QFileDialog *editor = new QFileDialog(parent,
                                          tr("Select directory"),
                                          index.data(Qt::EditRole).toString());
    editor->setFileMode(QFileDialog::Directory);
    editor->setOptions(QFileDialog::ShowDirsOnly);

    return editor;
}

void DirectorySelectorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void DirectorySelectorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(QFileDialog *fileDialog = qobject_cast<QFileDialog *>(editor)) {
        LOG << fileDialog->selectedFiles();
        model->setData(index, fileDialog->selectedFiles().first(), Qt::EditRole);
    } else {
        QStyledItemDelegate::setModelData(fileDialog, model, index);
    }
}
