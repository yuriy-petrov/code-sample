#ifndef TROUBLELISTMODEL_H
#define TROUBLELISTMODEL_H

#include "Trouble.h"
#include <QAbstractTableModel>

class TroubleListModel : public QAbstractTableModel
{

public:

    enum Column
    {
        Key = 0,
        Description = 1
    };

    TroubleListModel(QObject * parent = 0);
    ~TroubleListModel();

    QList<Trouble> troubles() const;

public:

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual QVariant data(const QModelIndex & index, int role) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex & index) const;

public slots:

    void setTroubles(const QList<Trouble> & troubles);

private:

    QList<Trouble> m_troubles;
    QHash<Column,QString> m_columnTitles;

};

#endif // TROUBLELISTMODEL_H
