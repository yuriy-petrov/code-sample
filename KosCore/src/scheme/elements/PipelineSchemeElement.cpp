#include "PipelineSchemeElement.h"

#include <QJsonArray>

PipelineSchemeElement::PipelineSchemeElement(QObject * parent) :
    AbstractSchemeElement(parent),
    m_state(KosTypes::PipelineState::Normal),
    m_substanceType(KosTypes::SubstanceType::Nothing),
    m_width(1)
{
}

void PipelineSchemeElement::fromJsonObject(const QJsonObject & jsonObject)
{
    AbstractSchemeElement::fromJsonObject(jsonObject);

    foreach (QJsonValue jsonPipe, jsonObject.value("pipes").toArray())
    {
        PipelineSchemeElement::Pipe pipe;
        foreach (QJsonValue jsonPoint, jsonPipe.toObject().value("points").toArray())
        {
            pipe.append(QPointF(jsonPoint.toObject().value("position_x").toDouble(), jsonPoint.toObject().value("position_y").toDouble()));
        }
        m_pipes.append(pipe);
    }
    m_state = (KosTypes::PipelineState)jsonObject.value("state").toInt();
    m_substanceType = (KosTypes::SubstanceType)jsonObject.value("substance_type").toInt();
    m_width = jsonObject.value("width").toInt();
    emit changed();
}

QJsonObject PipelineSchemeElement::toJsonObject() const
{
    QJsonObject jsonObject = AbstractSchemeElement::toJsonObject();
    QJsonArray jsonPipes;
    foreach (PipelineSchemeElement::Pipe pipe, m_pipes)
    {
        QJsonObject jsonPipe;
        QJsonArray jsonPoints;
        foreach (QPointF position, pipe)
        {
            QJsonObject jsonPoint;
            jsonPoint.insert("position_x", position.x());
            jsonPoint.insert("position_y", position.y());
            jsonPoints.append(jsonPoint);
        }
        jsonPipe.insert("points", jsonPoints);
        jsonPipes.append(jsonPipe);
    }
    jsonObject.insert("pipes", jsonPipes);
    jsonObject.insert("state", (int)m_state);
    jsonObject.insert("substance_type", (int)m_substanceType);
    jsonObject.insert("width", m_width);
    return jsonObject;
}

QString PipelineSchemeElement::schemeElementName()
{
    return PipelineSchemeElement::tr("Pipeline");
}

QList<PipelineSchemeElement::Pipe> PipelineSchemeElement::pipes() const
{
    return m_pipes;
}

void PipelineSchemeElement::setPipes(const QList<PipelineSchemeElement::Pipe> &pipes)
{
    if (m_pipes != pipes)
    {
        m_pipes = pipes;
        emit changed();
    }
}

KosTypes::PipelineState PipelineSchemeElement::state() const
{
    return m_state;
}

void PipelineSchemeElement::setState(const KosTypes::PipelineState & state)
{
    if (m_state != state)
    {
        m_state = state;
        emit changed();
    }
}

KosTypes::SubstanceType PipelineSchemeElement::substanceType() const
{
    return m_substanceType;
}

void PipelineSchemeElement::setSubstanceType(const KosTypes::SubstanceType & substanceType)
{
    if (m_substanceType != substanceType)
    {
        m_substanceType = substanceType;
        emit changed();
    }
}

int PipelineSchemeElement::width() const
{
    return m_width;
}

void PipelineSchemeElement::setWidth(int width)
{
    if (m_width != width)
    {
        m_width = width;
        emit changed();
    }
}

void PipelineSchemeElement::setParameters(const QList<PipelineSchemeElement::Pipe> & pipes,
                                          KosTypes::PipelineState & state,
                                          KosTypes::SubstanceType & substanceType,
                                          int width)
{
    if (m_pipes != pipes || m_state != state || m_width != width || m_substanceType != substanceType)
    {
        m_pipes = pipes;
        m_state = state;
        m_width = width;
        m_substanceType = substanceType;
        emit changed();
    }
}

void PipelineSchemeElement::move(const QPointF &dp)
{
    QList<Pipe> pipes = m_pipes;

    for (int i = 0; i < pipes.size(); ++i)
    {
        Pipe pipe = pipes[i];
        for (int j = 0; j < pipe.size(); ++j)
        {
            pipe[j] = pipe[j] + dp;
        }
        pipes[i] = pipe;
    }

    setPipes(pipes);
}





