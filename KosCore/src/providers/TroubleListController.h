#ifndef TROUBLELISTCONTROLLER_H
#define TROUBLELISTCONTROLLER_H

#include <Trouble.h>
#include <QMap>
#include <QSet>
#include <QList>
#include <QStringList>
#include <QObject>

class TroubleListController : public QObject
{

    Q_OBJECT

public:

    explicit TroubleListController(QObject * parent = 0);
    ~TroubleListController();

    QList<Trouble> troubles() const;
    QSet<QString> activeTroubles() const;

public slots:

    void setTroubles(const QList<Trouble> &troubles);
    void setActiveTroubles(const QSet<QString> & activeTroubles);

signals:

    void troublesChanged(QList<Trouble> troubles);
    void activeTroublesChanged(QSet<QString> activeTroubles);

private:

    QList<Trouble> m_troubles;
    QSet<QString> m_activeTroubles;
};

#endif // TROUBLELISTCONTROLLER_H
