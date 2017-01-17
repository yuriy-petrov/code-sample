#ifndef ABSTRACTSCHEMEELEMENTCONTAINER_H
#define ABSTRACTSCHEMEELEMENTCONTAINER_H

class AbstractSchemeElement;

#include <QString>
#include <QJsonArray>
#include <QObject>

class AbstractSchemeElementContainer: public QObject
{

    Q_OBJECT

public:

    AbstractSchemeElementContainer(const QString & name,
                                   QObject * parent = 0);
    QString name() const;
    QList<AbstractSchemeElement*> abstractElements() const;
    AbstractSchemeElement * abstractElement(const QString & nodeKey) const;

public slots:

    virtual void clear() = 0;
    virtual QJsonArray toJsonArray() = 0;
    virtual void fromJsonArray(const QJsonArray & jsonArray) = 0;

signals:

    void changed();
    void elementChanged(const QString & nodeKey);

protected slots:

    virtual void elementChangedEvent() = 0;

protected:

    QString m_name;

    QList<AbstractSchemeElement*> m_abstractElements;

};

#endif // ABSTRACTSCHEMEELEMENTCONTAINER_H
