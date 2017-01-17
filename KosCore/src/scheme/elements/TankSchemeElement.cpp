#include "TankSchemeElement.h"

TankSchemeElement::TankSchemeElement(QObject * parent) :
    AbstractSchemeElement(parent),
    m_substanceType(KosTypes::Nothing),
    m_stretchable(false),
    m_value(0)
{
}

void TankSchemeElement::fromJsonObject(const QJsonObject & jsonObject)
{
    AbstractSchemeElement::fromJsonObject(jsonObject);

    m_substanceType = (KosTypes::SubstanceType)jsonObject.value("substance_type").toInt();
    m_position = QPointF(jsonObject.value("position_x").toDouble(), jsonObject.value("position_y").toDouble());
    m_size = QSize(jsonObject.value("size_width").toInt(), jsonObject.value("size_height").toInt());
    m_stretchable = jsonObject.value("stretchable").toBool();
    m_value = jsonObject.value("value").toInt();

    emit changed();
}

QJsonObject TankSchemeElement::toJsonObject() const
{
    QJsonObject jsonObject = AbstractSchemeElement::toJsonObject();
    jsonObject.insert("substance_type", (int)m_substanceType);
    jsonObject.insert("position_x", m_position.x());
    jsonObject.insert("position_y", m_position.y());
    jsonObject.insert("size_width", m_size.width());
    jsonObject.insert("size_height", m_size.height());
    jsonObject.insert("stretchable", m_stretchable);
    jsonObject.insert("value", m_value);
    return jsonObject;
}

QString TankSchemeElement::schemeElementName()
{
    return TankSchemeElement::tr("Tank");
}

KosTypes::SubstanceType TankSchemeElement::substanceType() const
{
    return m_substanceType;
}

void TankSchemeElement::setSubstanceType(const KosTypes::SubstanceType &substanceType)
{
    if (m_substanceType != substanceType)
    {
        m_substanceType = substanceType;
        emit changed();
    }
}

QPointF TankSchemeElement::position() const
{
    return m_position;
}

void TankSchemeElement::setPosition(const QPointF &position)
{
    if (m_position != position)
    {
        m_position = position;
        emit changed();
    }
}

QSize TankSchemeElement::size() const
{
    return m_size;
}

void TankSchemeElement::setSize(const QSize &size)
{
    if (m_size != size)
    {
        m_size = size;
        emit changed();
    }
}

bool TankSchemeElement::stretchable() const
{
    return m_stretchable;
}

void TankSchemeElement::setStretchable(bool stretchable)
{
    if (m_stretchable != stretchable)
    {
        m_stretchable = stretchable;
        emit changed();
    }
}

int TankSchemeElement::value() const
{
    return m_value;
}

void TankSchemeElement::setValue(int value)
{
    if (m_value != value)
    {
        m_value = value;
        emit changed();
    }
}

void TankSchemeElement::setParameters(const KosTypes::SubstanceType & substanceType,
                                      const QPointF & position,
                                      const QSize & size,
                                      bool stretchable,
                                      int value)
{
    if (m_substanceType != substanceType || m_position != position || m_size != size ||
            m_stretchable != stretchable || m_value != value)
    {
        m_substanceType = substanceType;
        m_position = position;
        m_size = size;
        m_stretchable = stretchable;
        m_value = value;
        emit changed();
    }
}

void TankSchemeElement::move(const QPointF &dp)
{
    setPosition(m_position + dp);
}







