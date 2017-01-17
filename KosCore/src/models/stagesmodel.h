#ifndef STAGESMODEL_H
#define STAGESMODEL_H

#include <QAbstractTableModel>
#include "stages.h"

class StagesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum {
        COL_MODE,
        COL_NAME,
        COL_DATA_PATH
    };

public:
    explicit StagesModel(QObject *parent = 0);

    void setStagesPath(const QString& path);

    void setStages(const Player::Stages& stages);
    inline const Player::Stages& stages() const;

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

private:
    QList<Model::HystatMode::Type> m_modes;
    Player::Stages m_stages;
    QString m_stagesPath;
};

const Player::Stages &StagesModel::stages() const
{
    return m_stages;
}

#endif // STAGESMODEL_H
