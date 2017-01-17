#ifndef TANKSCHEMEELEMENT_H
#define TANKSCHEMEELEMENT_H

#include "KosTypes.h"
#include "AbstractSchemeElement.h"

#include <QPointF>
#include <QSize>
#include <QJsonObject>

class TankSchemeElement : public AbstractSchemeElement
{

    Q_OBJECT

public:

    explicit TankSchemeElement(QObject * parent = 0);

    virtual void fromJsonObject(const QJsonObject & jsonObject);
    virtual QJsonObject toJsonObject() const;

    static QString schemeElementName();

    KosTypes::SubstanceType substanceType() const;
    void setSubstanceType(const KosTypes::SubstanceType & substanceType);

    QPointF position() const;
    void setPosition(const QPointF & position);

    QSize size() const;
    void setSize(const QSize & size);

    bool stretchable() const;
    void setStretchable(bool stretchable);

    int value() const;
    void setValue(int value);

    void setParameters(const KosTypes::SubstanceType & substanceType,
                       const QPointF & position,
                       const QSize & size,
                       bool stretchable,
                       int value);

    virtual void move(const QPointF & dp);

private:

    KosTypes::SubstanceType m_substanceType;
    QPointF m_position;
    QSize m_size;
    bool m_stretchable;
    int m_value;

};

#endif // TANKSCHEMEELEMENT_H
