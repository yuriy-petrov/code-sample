#ifndef PIPELINESCHEMEELEMENT_H
#define PIPELINESCHEMEELEMENT_H

#include <QJsonObject>
#include <QPointF>
#include <QVector>

#include "AbstractSchemeElement.h"
#include "KosTypes.h"

class PipelineSchemeElement : public AbstractSchemeElement
{

    Q_OBJECT

public:

    typedef QVector<QPointF> Pipe;

    PipelineSchemeElement(QObject * parent = 0);

    virtual void fromJsonObject(const QJsonObject & jsonObject);
    virtual QJsonObject toJsonObject() const;

    static QString schemeElementName();

    QList<PipelineSchemeElement::Pipe> pipes() const;
    void setPipes(const QList<PipelineSchemeElement::Pipe> & pipes);

    KosTypes::PipelineState state() const;
    void setState(const KosTypes::PipelineState & state);

    KosTypes::SubstanceType substanceType() const;
    void setSubstanceType(const KosTypes::SubstanceType & substanceType);

    int width() const;
    void setWidth(int width);

    void setParameters(const QList<PipelineSchemeElement::Pipe> & pipes,
                       KosTypes::PipelineState & state,
                       KosTypes::SubstanceType & substanceType,
                       int width);

    virtual void move(const QPointF & dp);

private:

    QList<Pipe> m_pipes;
    KosTypes::PipelineState m_state;
    KosTypes::SubstanceType m_substanceType;
    int m_width;

};

#endif // PIPELINESCHEMEELEMENT_H
