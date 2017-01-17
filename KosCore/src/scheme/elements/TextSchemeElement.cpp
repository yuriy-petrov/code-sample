#include "TextSchemeElement.h"

#include "KosUtils.h"

TextSchemeElement::TextSchemeElement(QObject *parent) :
    AbstractSchemeElement(parent),
    m_frameVisible(true),
    m_frameType(Rect),
    m_fontSize(8),
    m_rotation(0)
{
}

void TextSchemeElement::fromJsonObject(const QJsonObject & jsonObject)
{
    AbstractSchemeElement::fromJsonObject(jsonObject);

    m_position = QPointF(jsonObject.value("position_x").toDouble(), jsonObject.value("position_y").toDouble());
    m_text = jsonObject.value("text").toString();
    m_frameVisible = jsonObject.value("frame_visible").toBool();
    m_frameType = (TextSchemeElement::FrameType)jsonObject.value("frame_type").toInt();
    m_fontSize = jsonObject.value("font_size").toInt();
    m_rotation = jsonObject.value("rotation").toDouble();
    m_screenOffset = KosUtils::instance()->pointFromString(jsonObject.value("screen_offset").toString());

    emit changed();
}

QJsonObject TextSchemeElement::toJsonObject() const
{
    QJsonObject jsonObject = AbstractSchemeElement::toJsonObject();
    jsonObject.insert("position_x", m_position.x());
    jsonObject.insert("position_y", m_position.y());
    jsonObject.insert("text", m_text);
    jsonObject.insert("frame_visible", m_frameVisible);
    jsonObject.insert("frame_type", m_frameType);
    jsonObject.insert("font_size", m_fontSize);
    jsonObject.insert("rotation", m_rotation);
    jsonObject.insert("screen_offset", KosUtils::instance()->pointToString(m_screenOffset));
    return jsonObject;
}

QString TextSchemeElement::schemeElementName()
{
    return TextSchemeElement::tr("Text");
}

QPointF TextSchemeElement::position() const
{
    return m_position;
}

void TextSchemeElement::setPosition(const QPointF &position)
{
    if (m_position != position)
    {
        m_position = position;
        emit changed();
    }
}

QString TextSchemeElement::text() const
{
    return m_text;
}

void TextSchemeElement::setText(const QString &text)
{
    if (m_text != text)
    {
        m_text = text;
        emit changed();
    }
}

bool TextSchemeElement::frameVisible() const
{
    return m_frameVisible;
}

void TextSchemeElement::setFrameVisible(bool frameVisible)
{
    if (m_frameVisible != frameVisible)
    {
        m_frameVisible = frameVisible;
        emit changed();
    }
}

TextSchemeElement::FrameType TextSchemeElement::frameType() const
{
    return m_frameType;
}

void TextSchemeElement::setFrameType(const FrameType &frameType)
{
    if (m_frameType != frameType)
    {
        m_frameType = frameType;
        emit changed();
    }
}

int TextSchemeElement::fontSize() const
{
    return m_fontSize;
}

void TextSchemeElement::setFontSize(int fontSize)
{
    if (m_fontSize != fontSize)
    {
        m_fontSize = fontSize;
        emit changed();
    }
}

qreal TextSchemeElement::rotation() const
{
    return m_rotation;
}

void TextSchemeElement::setRotation(const qreal & rotation)
{
    if (m_rotation != rotation)
    {
        m_rotation = rotation;
        emit changed();
    }
}

QPointF TextSchemeElement::screenOffset() const
{
    return m_screenOffset;
}

void TextSchemeElement::setScreenOffset(const QPointF & screenOffset)
{
    if (m_screenOffset != screenOffset)
    {
        m_screenOffset = screenOffset;
        emit changed();
    }
}

void TextSchemeElement::setParameters(const QPointF & position,
                                      const QString & text,
                                      bool frameVisible,
                                      const TextSchemeElement::FrameType & frameType,
                                      int fontSize,
                                      const qreal & rotation,
                                      const QPointF & screenOffset)
{
    if (m_position != position || m_text != text || m_frameVisible != frameVisible ||
            m_frameType != m_frameType || m_fontSize != fontSize || m_rotation != rotation ||
            m_screenOffset != screenOffset)
    {
        m_position = position;
        m_text = text;
        m_frameVisible = frameVisible;
        m_frameType = frameType;
        m_fontSize = fontSize;
        m_rotation = rotation;
        m_screenOffset = screenOffset;
        emit changed();
    }
}

void TextSchemeElement::move(const QPointF &dp)
{
    setPosition(m_position + dp);
}







