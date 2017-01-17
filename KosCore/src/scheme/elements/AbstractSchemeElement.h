#ifndef ABSTRACTSCHEMEELEMENT_H
#define ABSTRACTSCHEMEELEMENT_H

#include "KosTypes.h"

#include <QObject>
#include <QPointF>

class AbstractSchemeElement : public QObject
{

    Q_OBJECT

public:


    explicit AbstractSchemeElement(QObject * parent = 0);

    virtual void fromJsonObject(const QJsonObject & jsonObject);
    virtual QJsonObject toJsonObject() const;

    QString nodeKey() const;
    void setNodeKey(const QString & nodeKey);

    bool isHighlighted() const;
    void setHighlighted(bool isHighlighted);

    QString tooltip() const;
    void setTooltip(const QString & tooltip);

    QString formText() const;
    void setFormText(const QString & formText);

    KosTypes::HorizontalAlignment formPositionX() const;
    void setFormPositionX(const KosTypes::HorizontalAlignment & formPositionX);

    KosTypes::VerticalAlignment formPositionY() const;
    void setFormPositionY(const KosTypes::VerticalAlignment & formPositionY);

    KosTypes::HorizontalAlignment formAlignmentX() const;
    void setFormAlignmentX(const KosTypes::HorizontalAlignment & formAlignmentX);

    KosTypes::VerticalAlignment formAlignmentY() const;
    void setFormAlignmentY(const KosTypes::VerticalAlignment & formAlignmentY);

    QPointF formOffset() const;
    void setFormOffset(const QPointF & formOffset);

    int formFontSize() const;
    void setFormFontSize(int formFontSize);

    int formRotation() const;
    void setFormRotation(int formRotation);

    void setParameters(const QString & nodeKey,
                       const QString & tooltip,
                       const QString & formText,
                       KosTypes::HorizontalAlignment formPositionX,
                       KosTypes::VerticalAlignment formPositionY,
                       KosTypes::HorizontalAlignment formAlignmentX,
                       KosTypes::VerticalAlignment formAlignmentY,
                       const QPointF & formOffset,
                       int formFontSize,
                       int formRotation);

public slots:

    virtual void move(const QPointF & dp) = 0;

signals:

    void changed();
    void nodeKeyChanged();

private:

    QString m_nodeKey;
    QString m_tooltip;

    bool m_isHighlighted;

    QString m_formText;
    KosTypes::HorizontalAlignment m_formPositionX;
    KosTypes::VerticalAlignment m_formPositionY;
    KosTypes::HorizontalAlignment m_formAlignmentX;
    KosTypes::VerticalAlignment m_formAlignmentY;
    QPointF m_formOffset;
    int m_formFontSize;
    int m_formRotation;

};

#endif // ABSTRACTSCHEMEELEMENT_H
