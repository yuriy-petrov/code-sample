#ifndef TEXTSCHEMEELEMENT_H
#define TEXTSCHEMEELEMENT_H

#include "AbstractSchemeElement.h"

#include <QPointF>
#include <QJsonObject>

class TextSchemeElement : public AbstractSchemeElement
{

    Q_OBJECT

public:

    enum FrameType
    {
        Rect = 0,
        Ellipse = 1
    };

    explicit TextSchemeElement(QObject * parent = 0);

    virtual void fromJsonObject(const QJsonObject & jsonObject);
    virtual QJsonObject toJsonObject() const;

    static QString schemeElementName();

    QPointF position() const;
    void setPosition(const QPointF & position);

    QString text() const;
    void setText(const QString & text);

    bool frameVisible() const;
    void setFrameVisible(bool frameVisible);

    TextSchemeElement::FrameType frameType() const;
    void setFrameType(const TextSchemeElement::FrameType & frameType);

    int fontSize() const;
    void setFontSize(int fontSize);

    qreal rotation() const;
    void setRotation(const qreal & rotation);

    QPointF screenOffset() const;
    void setScreenOffset(const QPointF & screenOffset);

    void setParameters(const QPointF & position,
                       const QString & text,
                       bool frameVisible,
                       const TextSchemeElement::FrameType & frameType,
                       int fontSize,
                       const qreal & rotation,
                       const QPointF & screenOffset);

    virtual void move(const QPointF & dp);

private:

    QPointF m_position;
    QString m_text;
    bool m_frameVisible;
    FrameType m_frameType;
    int m_fontSize;
    qreal m_rotation;
    QPointF m_screenOffset;

};

#endif // TEXTSCHEMEELEMENT_H
