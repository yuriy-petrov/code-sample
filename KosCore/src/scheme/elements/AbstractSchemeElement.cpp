#include "AbstractSchemeElement.h"

#include "KosUtils.h"

#include <QJsonObject>

AbstractSchemeElement::AbstractSchemeElement(QObject * parent) :
    QObject(parent),
    m_isHighlighted(false),
    m_formPositionX(KosTypes::HorizontalAlignment::HCenter),
    m_formPositionY(KosTypes::VerticalAlignment::VCenter),
    m_formAlignmentX(KosTypes::HorizontalAlignment::HCenter),
    m_formAlignmentY(KosTypes::VerticalAlignment::VCenter),
    m_formFontSize(8),
    m_formRotation(0)
{
}

void AbstractSchemeElement::fromJsonObject(const QJsonObject & jsonObject)
{
    m_nodeKey = jsonObject.value("node_key").toString();
    m_tooltip = jsonObject.value("tooltip").toString();

    m_formText = jsonObject.value("form_text").toString();
    m_formPositionX = (KosTypes::HorizontalAlignment)jsonObject.value("form_position_x").toInt();
    m_formPositionY = (KosTypes::VerticalAlignment)jsonObject.value("form_position_y").toInt();
    m_formAlignmentX = (KosTypes::HorizontalAlignment)jsonObject.value("form_alignment_x").toInt();
    m_formAlignmentY = (KosTypes::VerticalAlignment)jsonObject.value("form_alignment_y").toInt();
    m_formOffset = KosUtils::instance()->pointFromString(jsonObject.value("form_offset").toString());
    m_formFontSize = jsonObject.value("form_font_size").toInt();
    m_formRotation = jsonObject.value("form_rotation").toInt();

    emit nodeKeyChanged();
}

QJsonObject AbstractSchemeElement::toJsonObject() const
{
    QJsonObject jsonObject;
    jsonObject.insert("node_key", m_nodeKey);
    jsonObject.insert("tooltip", m_tooltip);

    jsonObject.insert("form_text", m_formText);
    jsonObject.insert("form_position_x", m_formPositionX);
    jsonObject.insert("form_position_y", m_formPositionY);
    jsonObject.insert("form_alignment_x", m_formAlignmentX);
    jsonObject.insert("form_alignment_y", m_formAlignmentY);
    jsonObject.insert("form_offset", KosUtils::instance()->pointToString(m_formOffset));
    jsonObject.insert("form_font_size", m_formFontSize);
    jsonObject.insert("form_rotation", m_formRotation);

    return jsonObject;
}

QString AbstractSchemeElement::nodeKey() const
{
    return m_nodeKey;
}

void AbstractSchemeElement::setNodeKey(const QString & nodeKey)
{
    m_nodeKey = nodeKey;
    emit nodeKeyChanged();
}

bool AbstractSchemeElement::isHighlighted() const
{
    return m_isHighlighted;
}

void AbstractSchemeElement::setHighlighted(bool isHighlighted)
{
    m_isHighlighted = isHighlighted;
    emit changed();
}
QString AbstractSchemeElement::tooltip() const
{
    return m_tooltip;
}

void AbstractSchemeElement::setTooltip(const QString &tooltip)
{
    m_tooltip = tooltip;
    emit changed();
}
QString AbstractSchemeElement::formText() const
{
    return m_formText;
}

void AbstractSchemeElement::setFormText(const QString & formText)
{
    m_formText = formText;
    emit changed();
}

KosTypes::HorizontalAlignment AbstractSchemeElement::formPositionX() const
{
    return m_formPositionX;
}

void AbstractSchemeElement::setFormPositionX(const KosTypes::HorizontalAlignment & formPositionX)
{
    m_formPositionX = formPositionX;
    emit changed();
}

KosTypes::VerticalAlignment AbstractSchemeElement::formPositionY() const
{
    return m_formPositionY;
}

void AbstractSchemeElement::setFormPositionY(const KosTypes::VerticalAlignment & formPositionY)
{
    m_formPositionY = formPositionY;
    emit changed();
}

KosTypes::HorizontalAlignment AbstractSchemeElement::formAlignmentX() const
{
    return m_formAlignmentX;
}

void AbstractSchemeElement::setFormAlignmentX(const KosTypes::HorizontalAlignment & formAlignmentX)
{
    m_formAlignmentX = formAlignmentX;
    emit changed();
}

KosTypes::VerticalAlignment AbstractSchemeElement::formAlignmentY() const
{
    return m_formAlignmentY;
}

void AbstractSchemeElement::setFormAlignmentY(const KosTypes::VerticalAlignment & formAlignmentY)
{
    m_formAlignmentY = formAlignmentY;
    emit changed();
}

QPointF AbstractSchemeElement::formOffset() const
{
    return m_formOffset;
}

void AbstractSchemeElement::setFormOffset(const QPointF & formOffset)
{
    m_formOffset = formOffset;
    emit changed();
}

int AbstractSchemeElement::formFontSize() const
{
    return m_formFontSize;
}

void AbstractSchemeElement::setFormFontSize(int formFontSize)
{
    m_formFontSize = formFontSize;
    emit changed();
}

int AbstractSchemeElement::formRotation() const
{
    return m_formRotation;
}

void AbstractSchemeElement::setFormRotation(int formRotation)
{
    m_formRotation = formRotation;
    emit changed();
}

void AbstractSchemeElement::setParameters(const QString & nodeKey,
                                          const QString & tooltip,
                                          const QString & formText,
                                          KosTypes::HorizontalAlignment formPositionX,
                                          KosTypes::VerticalAlignment formPositionY,
                                          KosTypes::HorizontalAlignment formAlignmentX,
                                          KosTypes::VerticalAlignment formAlignmentY,
                                          const QPointF & formOffset,
                                          int formFontSize,
                                          int formRotation)
{
    m_nodeKey =  nodeKey;
    m_tooltip = tooltip;
    m_formText = formText;
    m_formPositionX = formPositionX;
    m_formPositionY = formPositionY;
    m_formAlignmentX = formAlignmentX;
    m_formAlignmentY = formAlignmentY;
    m_formOffset = formOffset;
    m_formFontSize = formFontSize;
    m_formRotation = formRotation;

    emit changed();
}












