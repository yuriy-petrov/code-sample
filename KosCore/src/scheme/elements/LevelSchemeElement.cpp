#include "LevelSchemeElement.h"

#include <QVariant>
#include <KosUtils.h>

LevelSchemeElement::LevelSchemeElement(QObject * parent) :
    AbstractSchemeElement(parent),
    m_firstSubstanceType(KosTypes::SubstanceType::Nothing),
    m_secondSubstanceType(KosTypes::SubstanceType::Nothing),
    m_levelElementType(KosTypes::LevelElementType::WaterLock),
    m_value(0),
    m_stretchable(true),
    m_mirroredHorizontal(false),
    m_mirroredVertical(false),
    m_factor(1)
{
}

void LevelSchemeElement::fromJsonObject(const QJsonObject & jsonObject)
{
    AbstractSchemeElement::fromJsonObject(jsonObject);
    m_firstSubstanceType = (KosTypes::SubstanceType)jsonObject.value("first_substance_type").toInt();
    m_secondSubstanceType = (KosTypes::SubstanceType)jsonObject.value("second_substance_type").toInt();
    m_levelElementType = (KosTypes::LevelElementType)jsonObject.value("level_type").toVariant().toInt();
    m_value = (KosTypes::ValveType)jsonObject.value("value").toVariant().toInt();
    m_position = QPointF(KosUtils::instance()->pointFromString(jsonObject.value("position").toString()));
    m_stretchable = jsonObject.value("stretchable").toBool();
    m_mirroredHorizontal = jsonObject.value("mirrored_horizontal").toBool();
    m_mirroredVertical = jsonObject.value("mirrored_vertical").toBool();
    m_factor = jsonObject.value("factor").toDouble();
    emit changed();
}

QJsonObject LevelSchemeElement::toJsonObject() const
{
    QJsonObject jsonObject = AbstractSchemeElement::toJsonObject();
    jsonObject.insert("first_substance_type", (int)m_firstSubstanceType);
    jsonObject.insert("second_substance_type", (int)m_secondSubstanceType);
    jsonObject.insert("level_type", (int)m_levelElementType);
    jsonObject.insert("value", m_value);
    jsonObject.insert("position", KosUtils::instance()->pointToString(m_position));
    jsonObject.insert("stretchable", m_stretchable);
    jsonObject.insert("mirrored_horizontal", m_mirroredHorizontal);
    jsonObject.insert("mirrored_vertical", m_mirroredVertical);
    jsonObject.insert("factor", m_factor);
    return jsonObject;
}

QString LevelSchemeElement::schemeElementName()
{
    return LevelSchemeElement::tr("Level");
}

KosTypes::LevelElementType LevelSchemeElement::levelElementType() const
{
    return m_levelElementType;
}

void LevelSchemeElement::setLevelElementType(const KosTypes::LevelElementType & levelElementType)
{
    if (m_levelElementType != levelElementType)
    {
        m_levelElementType = levelElementType;
        emit changed();
    }
}

KosTypes::SubstanceType LevelSchemeElement::firstSubstanceType() const
{
    return m_firstSubstanceType;
}

void LevelSchemeElement::setFirstSubstanceType(const KosTypes::SubstanceType & firstSubstanceType)
{
    if (m_firstSubstanceType != firstSubstanceType)
    {
        m_firstSubstanceType = firstSubstanceType;
        emit changed();
    }
}

KosTypes::SubstanceType LevelSchemeElement::secondSubstanceType() const
{
    return m_secondSubstanceType;
}

void LevelSchemeElement::setSecondSubstanceType(const KosTypes::SubstanceType & secondSubstanceType)
{
    if (m_secondSubstanceType != secondSubstanceType)
    {
        m_secondSubstanceType = secondSubstanceType;
        emit changed();
    }
}

qreal LevelSchemeElement::value() const
{
    return m_value;
}

void LevelSchemeElement::setValue(const qreal & value)
{
    if (m_value != value)
    {
        m_value = value;
        emit changed();
    }
}

QPointF LevelSchemeElement::position() const
{
    return m_position;
}

void LevelSchemeElement::setPosition(const QPointF &position)
{
    if (m_position != position)
    {
        m_position = position;
        emit changed();
    }
}

bool LevelSchemeElement::stretchable() const
{
    return m_stretchable;
}

void LevelSchemeElement::setStretchable(bool stretchable)
{
    if (m_stretchable != stretchable)
    {
        m_stretchable = stretchable;
        emit changed();
    }
}

bool LevelSchemeElement::mirroredHorizontal() const
{
    return m_mirroredHorizontal;
}

void LevelSchemeElement::setMirroredHorizontal(bool mirroredHorizontal)
{
    if (m_mirroredHorizontal != mirroredHorizontal)
    {
        m_mirroredHorizontal = mirroredHorizontal;
        emit changed();
    }
}

bool LevelSchemeElement::mirroredVertical() const
{
    return m_mirroredVertical;
}

void LevelSchemeElement::setMirroredVertical(bool mirroredVertical)
{
    if (m_mirroredVertical != mirroredVertical)
    {
        m_mirroredVertical = mirroredVertical;
        emit changed();
    }
}

qreal LevelSchemeElement::factor() const
{
    return m_factor;
}

void LevelSchemeElement::setFactor(qreal factor)
{
    if (m_factor != factor)
    {
        m_factor = factor;
        emit changed();
    }
}

void LevelSchemeElement::setParameters(const KosTypes::LevelElementType & levelElementType,
                                       const KosTypes::SubstanceType & firstSubstanceType,
                                       const KosTypes::SubstanceType & secondSubstanceType,
                                       const qreal & value,
                                       const QPointF & position,
                                       bool stretchable,
                                       bool mirroredHorizontal,
                                       bool mirroredVertical,
                                       qreal factor)
{
    if (m_levelElementType != levelElementType || m_firstSubstanceType != firstSubstanceType ||
            m_secondSubstanceType != secondSubstanceType || m_value != value || m_position != position ||
            m_stretchable != stretchable || m_mirroredHorizontal != mirroredHorizontal ||
            m_mirroredVertical != mirroredVertical || m_factor != factor)
    {
        m_levelElementType = levelElementType;
        m_firstSubstanceType = firstSubstanceType;
        m_secondSubstanceType = secondSubstanceType;
        m_value = value;
        m_position = position;
        m_stretchable = stretchable;
        m_mirroredHorizontal = mirroredHorizontal;
        m_mirroredVertical = mirroredVertical;
        m_factor = factor;
        emit changed();
    }
}

void LevelSchemeElement::move(const QPointF & dp)
{
    setPosition(m_position + dp);
}
