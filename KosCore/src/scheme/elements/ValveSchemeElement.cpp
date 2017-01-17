#include "ValveSchemeElement.h"

#include <QVariant>
#include <QJsonObject>

ValveSchemeElement::ValveSchemeElement(QObject * parent) :
    AbstractSchemeElement(parent),
    m_valveType(KosTypes::NonReturnValve),
    m_substanceType(KosTypes::Nothing),
    m_closePercentage(0),
    m_closePercentageVisible(false),
    m_closePercentagePositionX(0),
    m_closePercentagePositionY(0),
    m_isValid(true),
    m_rotation(0),
    m_mirroredHorizontal(false),
    m_mirroredVertical(false)
{
}

void ValveSchemeElement::fromJsonObject(const QJsonObject & jsonObject)
{
    AbstractSchemeElement::fromJsonObject(jsonObject);

    m_valveType = (KosTypes::ValveType)jsonObject.value("valve_type").toVariant().toInt();
    m_substanceType = (KosTypes::SubstanceType)jsonObject.value("substance_type").toInt();
    m_closePercentage = jsonObject.value("close_percentage").toDouble();
    m_closePercentageVisible = jsonObject.value("close_percentage_visible").toBool();
    m_closePercentagePositionX = jsonObject.value("close_percentage_position_x").toInt();
    m_closePercentagePositionY = jsonObject.value("close_percentage_position_y").toInt();
    m_isValid = jsonObject.value("is_valid").toBool();
    m_position = QPointF(jsonObject.value("position_x").toDouble(), jsonObject.value("position_y").toDouble());
    m_rotation = jsonObject.value("rotation").toVariant().toReal();
    m_mirroredHorizontal = jsonObject.value("mirrored_horizontal").toBool();
    m_mirroredVertical = jsonObject.value("mirrored_vertical").toBool();

    emit changed();
}

QJsonObject ValveSchemeElement::toJsonObject() const
{
    QJsonObject jsonObject = AbstractSchemeElement::toJsonObject();
    jsonObject.insert("valve_type", (int)m_valveType);
    jsonObject.insert("substance_type", (int)m_substanceType);
    jsonObject.insert("close_percentage", m_closePercentage);
    jsonObject.insert("close_percentage_visible", m_closePercentageVisible);
    jsonObject.insert("close_percentage_position_x", m_closePercentagePositionX);
    jsonObject.insert("close_percentage_position_y", m_closePercentagePositionY);
    jsonObject.insert("is_valid", m_isValid);
    jsonObject.insert("position_x", m_position.x());
    jsonObject.insert("position_y", m_position.y());
    jsonObject.insert("rotation", m_rotation);
    jsonObject.insert("mirrored_horizontal", m_mirroredHorizontal);
    jsonObject.insert("mirrored_vertical", m_mirroredVertical);
    return jsonObject;
}

QString ValveSchemeElement::schemeElementName()
{
    return ValveSchemeElement::tr("Valve");
}

KosTypes::ValveType ValveSchemeElement::valveType() const
{
    return m_valveType;
}

void ValveSchemeElement::setValveType(const KosTypes::ValveType & valveType)
{
    if (m_valveType != valveType)
    {
        m_valveType = valveType;
        emit changed();
    }
}

KosTypes::SubstanceType ValveSchemeElement::substanceType() const
{
    return m_substanceType;
}

void ValveSchemeElement::setSubstanceType(const KosTypes::SubstanceType & substanceType)
{
    if (m_substanceType != substanceType)
    {
        m_substanceType = substanceType;
        emit changed();
    }
}

qreal ValveSchemeElement::closePercentage() const
{
    return m_closePercentage;
}

void ValveSchemeElement::setClosePercentage(const qreal & closePercentage)
{
    if (m_closePercentage != closePercentage)
    {
        m_closePercentage = closePercentage;
        emit changed();
    }
}

bool ValveSchemeElement::closePercentageVisible() const
{
    return m_closePercentageVisible;
}

void ValveSchemeElement::setClosePercentageVisible(bool closePercentageVisible)
{
    if (m_closePercentageVisible != closePercentageVisible)
    {
        m_closePercentageVisible = closePercentageVisible;
        emit changed();
    }
}

int ValveSchemeElement::closePercentagePositionX() const
{
    return m_closePercentagePositionX;
}

void ValveSchemeElement::setClosePercentagePositionX(int closePercentagePositionX)
{
    if (m_closePercentagePositionX != closePercentagePositionX)
    {
        m_closePercentagePositionX = closePercentagePositionX;
        emit changed();
    }
}

int ValveSchemeElement::closePercentagePositionY() const
{
    return m_closePercentagePositionY;
}

void ValveSchemeElement::setClosePercentagePositionY(int closePercentagePositionY)
{
    if (m_closePercentagePositionY != closePercentagePositionY)
    {
        m_closePercentagePositionY = closePercentagePositionY;
        emit changed();
    }
}

bool ValveSchemeElement::isValid() const
{
    return m_isValid;
}

void ValveSchemeElement::setValid(bool isValid)
{
    if (m_isValid != isValid)
    {
        m_isValid = isValid;
        emit changed();
    }
}

QPointF ValveSchemeElement::position() const
{
    return m_position;
}

void ValveSchemeElement::setPosition(const QPointF & position)
{
    if (m_position != position)
    {
        m_position = position;
        emit changed();
    }
}

qreal ValveSchemeElement::rotation() const
{
    return m_rotation;
}

void ValveSchemeElement::setRotation(const qreal & rotation)
{
    if (m_rotation != rotation)
    {
        m_rotation = rotation;
        emit changed();
    }
}

bool ValveSchemeElement::mirroredHorizontal() const
{
    return m_mirroredHorizontal;
}

void ValveSchemeElement::setMirroredHorizontal(bool mirroredHorizontal)
{
    if (m_mirroredHorizontal != mirroredHorizontal)
    {
        m_mirroredHorizontal = mirroredHorizontal;
        emit changed();
    }
}

bool ValveSchemeElement::mirroredVertical() const
{
    return m_mirroredVertical;
}

void ValveSchemeElement::setMirroredVertical(bool mirroredVertical)
{
    if (m_mirroredVertical != mirroredVertical)
    {
        m_mirroredVertical = mirroredVertical;
        emit changed();
    }
}

void ValveSchemeElement::setParameters(KosTypes::ValveType valveType,
                                       KosTypes::SubstanceType substanceType,
                                       qreal closePercentage,
                                       bool closePercentageVisible,
                                       int closePercentagePositionX,
                                       int closePercentagePositionY,
                                       bool isValid,
                                       const QPointF & position,
                                       const qreal & rotation,
                                       bool mirroredHorizontal,
                                       bool mirroredVertical)
{
    if (m_valveType != valveType || m_substanceType != substanceType || m_closePercentage != closePercentage ||
            m_closePercentageVisible != closePercentageVisible || m_closePercentagePositionX != closePercentagePositionX ||
            m_closePercentagePositionY != closePercentagePositionY || m_isValid != isValid || m_position != position ||
            m_rotation != rotation || m_mirroredHorizontal != mirroredHorizontal || m_mirroredVertical != mirroredVertical)
    {
        m_valveType = valveType;
        m_substanceType = substanceType;
        m_closePercentage = closePercentage;
        m_closePercentageVisible = closePercentageVisible;
        m_closePercentagePositionX = closePercentagePositionX;
        m_closePercentagePositionY = closePercentagePositionY;
        m_isValid = isValid;
        m_position = position;
        m_rotation = rotation;
        m_mirroredHorizontal = mirroredHorizontal;
        m_mirroredVertical = mirroredVertical;
        emit changed();
    }
}

void ValveSchemeElement::move(const QPointF &dp)
{
    setPosition(m_position + dp);
}


