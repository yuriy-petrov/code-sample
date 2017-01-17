#include "modelvaluesdelegate.h"
#include "metatypehelper.h"
#include "modeltypeshelper.h"
#include "StringsKeys.h"

#include <QComboBox>

ModelValuesDelegate::ModelValuesDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


QWidget *ModelValuesDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED( option )

    const QString key = index.data(Model::TypesHelper::ModelKeyRole).toString();

    if(Model::CellStack::Enable::keys().contains(key))
    {
        QComboBox *cb = new QComboBox(parent);
        cb->addItems(Model::TypesHelper::valuesNames(key));
        return cb;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ModelValuesDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const QString key = index.data(Model::TypesHelper::ModelKeyRole).toString();

    if(Model::CellStack::Enable::keys().contains(key))
    {
        if(QComboBox *cb = qobject_cast<QComboBox *>(editor)) {
            QString currentText = index.data(Qt::DisplayRole).toString();
            int cbIndex = cb->findText(currentText, Qt::MatchFixedString);
            if(cbIndex >= 0) {
                cb->setCurrentIndex(cbIndex);
            }
            return;
        }
    }

    QStyledItemDelegate::setEditorData(editor, index);
}

void ModelValuesDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    const QString key = index.data(Model::TypesHelper::ModelKeyRole).toString();

    if(Model::CellStack::Enable::keys().contains(key))
    {
        if(QComboBox *cb = qobject_cast<QComboBox *>(editor)) {
            model->setData(index, Model::TypesHelper::fromString(key, cb->currentText()), Qt::EditRole);
            return;
        }
    }

    QStyledItemDelegate::setModelData(editor, model, index);
}
