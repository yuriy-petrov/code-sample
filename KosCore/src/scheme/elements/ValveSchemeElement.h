#ifndef VALVESCHEMEELEMENT_H
#define VALVESCHEMEELEMENT_H

#include "AbstractSchemeElement.h"
#include "KosTypes.h"

#include <QPointF>
#include <QHash>

class ValveSchemeElement : public AbstractSchemeElement
{

    Q_OBJECT

public:

    explicit ValveSchemeElement(QObject * parent = 0);

    virtual void fromJsonObject(const QJsonObject & jsonObject);
    virtual QJsonObject toJsonObject() const;

    static QString schemeElementName();

    KosTypes::ValveType valveType() const;
    void setValveType(const KosTypes::ValveType & valveType);

    KosTypes::SubstanceType substanceType() const;
    void setSubstanceType(const KosTypes::SubstanceType & substanceType);

    qreal closePercentage() const;
    void setClosePercentage(const qreal &closePercentage);

    bool closePercentageVisible() const;
    void setClosePercentageVisible(bool closePercentageVisible);

    int closePercentagePositionX() const;
    void setClosePercentagePositionX(int closePercentagePositionX);

    int closePercentagePositionY() const;
    void setClosePercentagePositionY(int closePercentagePositionY);

    bool isValid() const;
    void setValid(bool isValid);

    QPointF position() const;
    void setPosition(const QPointF & position);

    qreal rotation() const;
    void setRotation(const qreal & rotation);

    bool mirroredHorizontal() const;
    void setMirroredHorizontal(bool mirroredHorizontal);

    bool mirroredVertical() const;
    void setMirroredVertical(bool mirroredVertical);

    void setParameters(KosTypes::ValveType valveType,
                       KosTypes::SubstanceType substanceType,
                       qreal closePercentage,
                       bool closePercentageVisible,
                       int closePercentagePositionX,
                       int closePercentagePositionY,
                       bool isValid,
                       const QPointF & position,
                       const qreal & rotation,
                       bool mirroredHorizontal,
                       bool mirroredVertical);

    virtual void move(const QPointF & dp);

private:

    KosTypes::ValveType m_valveType;
    KosTypes::SubstanceType m_substanceType;
    qreal m_closePercentage;
    bool m_closePercentageVisible;
    int m_closePercentagePositionX;
    int m_closePercentagePositionY;
    bool m_isValid;
    QPointF m_position;
    qreal m_rotation;
    bool m_mirroredHorizontal;
    bool m_mirroredVertical;

};

#endif // VALVESCHEMEELEMENT_H
