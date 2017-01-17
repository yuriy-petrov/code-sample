#include "BasicSchemeElement.h"

#include "KosUtils.h"
#include "KosTypesHelper.h"

#include <QVariant>

BasicSchemeElement::BasicSchemeElement(QObject * parent) :
    AbstractSchemeElement(parent),
    m_type(KosTypes::Pump),
    m_state(0),
    m_rotation(0),
    m_mirroredHorizontal(false),
    m_mirroredVertical(false),
    m_color(QColor(Qt::white)),
    m_strechable(false),
    m_factor(1)
{
}

void BasicSchemeElement::fromJsonObject(const QJsonObject & jsonObject)
{
    AbstractSchemeElement::fromJsonObject(jsonObject);

    m_type = (KosTypes::BasicElementType)jsonObject.value("type").toVariant().toInt();
    m_state = jsonObject.value("state").toVariant().toInt();
    m_position = QPointF(jsonObject.value("position_x").toDouble(), jsonObject.value("position_y").toDouble());
    m_rotation = jsonObject.value("rotation").toVariant().toReal();
    m_mirroredHorizontal = jsonObject.value("mirrored_horizontal").toBool();
    m_mirroredVertical = jsonObject.value("mirrored_vertical").toBool();
    m_color = KosUtils::instance()->colorFromString(jsonObject.value("color").toString());
    m_strechable = jsonObject.value("strechable").toBool();
    m_factor = jsonObject.value("factor").toDouble(1);

    emit changed();
}

QJsonObject BasicSchemeElement::toJsonObject() const
{
    QJsonObject jsonObject = AbstractSchemeElement::toJsonObject();
    jsonObject.insert("type", (int)m_type);
    jsonObject.insert("state", m_state);
    jsonObject.insert("position_x", m_position.x());
    jsonObject.insert("position_y", m_position.y());
    jsonObject.insert("rotation", m_rotation);
    jsonObject.insert("mirrored_horizontal", m_mirroredHorizontal);
    jsonObject.insert("mirrored_vertical", m_mirroredVertical);
    jsonObject.insert("color", KosUtils::instance()->colorToString(m_color));
    jsonObject.insert("strechable", m_strechable);
    jsonObject.insert("factor", m_factor);
    return jsonObject;
}

QString BasicSchemeElement::schemeElementName()
{
    return BasicSchemeElement::tr("Basic");
}

KosTypes::BasicElementType BasicSchemeElement::type() const
{
    return m_type;
}

void BasicSchemeElement::setType(const KosTypes::BasicElementType & type)
{
    if (m_type != type)
    {
        m_type = type;
        emit changed();
    }
}

int BasicSchemeElement::state() const
{
    return m_state;
}

void BasicSchemeElement::setState(int state)
{
    if (m_state != state)
    {
        m_state = state;
        emit changed();
    }
}

QPointF BasicSchemeElement::position() const
{
    return m_position;
}

void BasicSchemeElement::setPosition(const QPointF & position)
{
    if (m_position != position)
    {
        m_position = position;
        emit changed();
    }
}

qreal BasicSchemeElement::rotation() const
{
    return m_rotation;
}

void BasicSchemeElement::setRotation(const qreal & rotation)
{
    if (m_rotation != rotation)
    {
        m_rotation = rotation;
        emit changed();
    }
}

bool BasicSchemeElement::mirroredVertical() const
{
    return m_mirroredVertical;
}

void BasicSchemeElement::setMirroredVertical(bool mirroredVertical)
{
    if (m_mirroredVertical != mirroredVertical)
    {
        m_mirroredVertical = mirroredVertical;
        emit changed();
    }
}

bool BasicSchemeElement::mirroredHorizontal() const
{
    return m_mirroredHorizontal;
}

void BasicSchemeElement::setMirroredHorizontal(bool mirroredHorizontal)
{
    if (m_mirroredHorizontal != mirroredHorizontal)
    {
        m_mirroredHorizontal = mirroredHorizontal;
        emit changed();
    }
}

QColor BasicSchemeElement::color() const
{
    return m_color;
}

void BasicSchemeElement::setColor(const QColor & color)
{
    if (m_color != color)
    {
        m_color = color;
        emit changed();
    }
}

KosTypes::SubstanceType BasicSchemeElement::substanceType() const
{
    return KosTypesHelper::instance()->substanceTypeColors().key(this->color(), KosTypes::SubstanceType::Invalid);
}

void BasicSchemeElement::setSubstanceType(KosTypes::SubstanceType substanceType)
{
    setColor(KosTypesHelper::instance()->substanceTypeColors().value(substanceType));
}

bool BasicSchemeElement::strechable() const
{
    return m_strechable;
}

void BasicSchemeElement::setStrechable(bool strechable)
{
    if (m_strechable != strechable)
    {
        m_strechable = strechable;
        emit changed();
    }
}

qreal BasicSchemeElement::factor() const
{
    return m_factor;
}

void BasicSchemeElement::setFactor(const qreal & factor)
{
    if (m_factor != factor)
    {
        m_factor = factor;
        emit changed();
    }
}

void BasicSchemeElement::setParameters(const KosTypes::BasicElementType & type,
                                       int state,
                                       const QPointF & position,
                                       const qreal & rotation,
                                       bool mirroredHorizontal,
                                       bool mirroredVertical,
                                       const QColor & color,
                                       bool strechable,
                                       const qreal & factor)
{
    if (m_type != type || m_state != state || m_position != position ||
            m_rotation != rotation || m_mirroredHorizontal != mirroredHorizontal ||
            m_mirroredVertical != mirroredVertical || m_color != color || m_strechable != strechable ||
            m_factor != factor)
    {
        m_type = type;
        m_state = state;
        m_position = position;
        m_rotation = rotation;
        m_mirroredHorizontal = mirroredHorizontal;
        m_mirroredVertical = mirroredVertical;
        m_color = color;
        m_strechable = strechable;
        m_factor = factor;
        emit changed();
    }
}

void BasicSchemeElement::move(const QPointF & dp)
{
    setPosition(m_position + dp);
}



