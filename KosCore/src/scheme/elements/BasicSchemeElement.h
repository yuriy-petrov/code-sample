#ifndef BASICSCHEMEELEMENT_H
#define BASICSCHEMEELEMENT_H

#include <QPointF>
#include <QColor>
#include <QJsonObject>
#include <QHash>

#include "KosTypes.h"
#include "AbstractSchemeElement.h"

class BasicSchemeElement: public AbstractSchemeElement
{

    Q_OBJECT

public:

    explicit BasicSchemeElement(QObject * parent = 0);

    virtual void fromJsonObject(const QJsonObject & jsonObject);
    virtual QJsonObject toJsonObject() const;

    static QString schemeElementName();

    KosTypes::BasicElementType type() const;
    void setType(const KosTypes::BasicElementType & type);

    int state() const;
    void setState(int state);

    QPointF position() const;
    void setPosition(const QPointF & position);

    qreal rotation() const;
    void setRotation(const qreal & rotation);

    bool mirroredHorizontal() const;
    void setMirroredHorizontal(bool mirroredHorizontal);

    bool mirroredVertical() const;
    void setMirroredVertical(bool mirroredVertical);

    QColor color() const;
    void setColor(const QColor & color);

    KosTypes::SubstanceType substanceType() const;
    void setSubstanceType(KosTypes::SubstanceType substanceType);

    bool strechable() const;
    void setStrechable(bool strechable);

    qreal factor() const;
    void setFactor(const qreal & factor);

    void setParameters(const KosTypes::BasicElementType & type,
                       int state,
                       const QPointF & position,
                       const qreal & rotation,
                       bool mirroredHorizontal,
                       bool mirroredVertical,
                       const QColor & color,
                       bool strechable,
                       const qreal & factor);

    virtual void move(const QPointF & dp);

private:

    KosTypes::BasicElementType m_type;
    int m_state;
    QPointF m_position;
    qreal m_rotation;
    bool m_mirroredHorizontal;
    bool m_mirroredVertical;
    QColor m_color;
    bool m_strechable;
    qreal m_factor;

};

#endif // BASICSCHEMEELEMENT_H
