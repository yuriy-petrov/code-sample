#ifndef LEVELSCHEMEELEMENT_H
#define LEVELSCHEMEELEMENT_H

#include "KosTypes.h"
#include "AbstractSchemeElement.h"

#include <QJsonObject>
#include <QPointF>

class LevelSchemeElement : public AbstractSchemeElement
{

    Q_OBJECT

public:

    explicit LevelSchemeElement(QObject * parent = 0);

    virtual void fromJsonObject(const QJsonObject & jsonObject);
    virtual QJsonObject toJsonObject() const;

    static QString schemeElementName();

    KosTypes::LevelElementType levelElementType() const;
    void setLevelElementType(const KosTypes::LevelElementType & levelElementType);

    KosTypes::SubstanceType firstSubstanceType() const;
    void setFirstSubstanceType(const KosTypes::SubstanceType & firstSubstanceType);

    KosTypes::SubstanceType secondSubstanceType() const;
    void setSecondSubstanceType(const KosTypes::SubstanceType & secondSubstanceType);

    qreal value() const;
    void setValue(const qreal & value);

    QPointF position() const;
    void setPosition(const QPointF & position);

    bool stretchable() const;
    void setStretchable(bool stretchable);

    bool mirroredHorizontal() const;
    void setMirroredHorizontal(bool mirroredHorizontal);

    bool mirroredVertical() const;
    void setMirroredVertical(bool mirroredVertical);

    qreal factor() const;
    void setFactor(qreal factor);

    void setParameters(const KosTypes::LevelElementType & levelElementType,
                       const KosTypes::SubstanceType & firstSubstanceType,
                       const KosTypes::SubstanceType & secondSubstanceType,
                       const qreal & value,
                       const QPointF & position,
                       bool stretchable,
                       bool mirroredHorizontal,
                       bool mirroredVertical,
                       qreal factor);

    virtual void move(const QPointF & dp);

private:

    KosTypes::LevelElementType m_levelElementType;

    KosTypes::SubstanceType m_firstSubstanceType;
    KosTypes::SubstanceType m_secondSubstanceType;

    qreal m_value;
    QPointF m_position;
    bool m_stretchable;
    bool m_mirroredHorizontal;
    bool m_mirroredVertical;
    qreal m_factor;

};

#endif // LEVELSCHEMEELEMENT_H
