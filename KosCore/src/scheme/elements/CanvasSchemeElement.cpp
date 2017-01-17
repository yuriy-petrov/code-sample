#include "CanvasSchemeElement.h"

#include <QJsonObject>

CanvasSchemeElement::CanvasSchemeElement(QObject * parent) :
    AbstractSchemeElement(parent),
    m_gridStep(0),
    m_defaultZoom(1),
    m_basicFactor(0.5),
    m_valveFactor(0.5),
    m_levelFactor(0.5)
{
}

void CanvasSchemeElement::fromJsonObject(const QJsonObject & jsonObject)
{
    AbstractSchemeElement::fromJsonObject(jsonObject);

    m_title = jsonObject.value("title").toString();
    m_size = QSize(jsonObject.value("size_width").toInt(), jsonObject.value("size_height").toInt());
    m_gridStep = jsonObject.value("grid_step").toInt();
    m_defaultZoom = jsonObject.value("default_zoom").toDouble();
    m_basicFactor = jsonObject.value("basic_factor").toDouble();
    m_valveFactor = jsonObject.value("valve_factor").toDouble();
    m_levelFactor = jsonObject.value("level_factor").toDouble();

    emit changed();
}

QJsonObject CanvasSchemeElement::toJsonObject() const
{
    QJsonObject jsonObject;
    jsonObject.insert("title", m_title);
    jsonObject.insert("size_width", m_size.width());
    jsonObject.insert("size_height", m_size.height());
    jsonObject.insert("grid_step", m_gridStep);
    jsonObject.insert("basic_factor", m_basicFactor);
    jsonObject.insert("valve_factor", m_valveFactor);
    jsonObject.insert("level_factor", m_levelFactor);
    jsonObject.insert("default_zoom", m_defaultZoom);
    return jsonObject;
}

QString CanvasSchemeElement::schemeElementName()
{
    return CanvasSchemeElement::tr("Canvas");
}

QString CanvasSchemeElement::title() const
{
    return m_title;
}

void CanvasSchemeElement::setTitle(const QString & title)
{
    if (m_title != title)
    {
        m_title = title;
        emit changed();
    }
}

QSize CanvasSchemeElement::size() const
{
    return m_size;
}

void CanvasSchemeElement::setSize(const QSize & size)
{
    if (m_size != size)
    {
        m_size = size;
        emit changed();
    }
}

int CanvasSchemeElement::gridStep() const
{
    return m_gridStep;
}

void CanvasSchemeElement::setGridStep(const int & gridStep)
{
    if (m_gridStep != gridStep)
    {
        m_gridStep = gridStep;
        emit changed();
    }
}

qreal CanvasSchemeElement::defaultZoom() const
{
    return m_defaultZoom;
}

void CanvasSchemeElement::setDefaultZoom(const qreal & defaultZoom)
{
    if (m_defaultZoom != defaultZoom)
    {
        m_defaultZoom = defaultZoom;
        emit changed();
    }
}

qreal CanvasSchemeElement::basicFactor() const
{
    return m_basicFactor;
}

void CanvasSchemeElement::setBasicFactor(const qreal &basicFactor)
{
    if (m_basicFactor != basicFactor)
    {
        m_basicFactor = basicFactor;
        emit changed();
    }
}

qreal CanvasSchemeElement::valveFactor() const
{
    return m_valveFactor;
}

void CanvasSchemeElement::setValveFactor(const qreal &valveFactor)
{
    if (m_valveFactor != valveFactor)
    {
        m_valveFactor = valveFactor;
        emit changed();
    }
}

qreal CanvasSchemeElement::levelFactor() const
{
    return m_levelFactor;
}

void CanvasSchemeElement::setLevelFactor(const qreal &levelFactor)
{
    if (m_levelFactor != levelFactor)
    {
        m_levelFactor = levelFactor;
        emit changed();
    }
}

void CanvasSchemeElement::setParameters(const QString & title,
                                        const QSize & size,
                                        const int & gridStep,
                                        qreal defaultZoom,
                                        const qreal & basicFactor,
                                        const qreal & valveFactor,
                                        const qreal & levelFactor)
{
    if (m_title != title || m_size != size || m_gridStep != gridStep || m_defaultZoom != defaultZoom ||
            m_basicFactor != basicFactor || m_valveFactor != valveFactor || m_levelFactor != levelFactor)
    {
        m_title = title;
        m_size = size;
        m_gridStep = gridStep;
        m_defaultZoom = defaultZoom;
        m_basicFactor = basicFactor;
        m_valveFactor = valveFactor;
        m_levelFactor = levelFactor;
        emit changed();
    }
}

QPointF CanvasSchemeElement::pointByGrid(const QPointF & point, bool checkSize) const
{
    if (m_gridStep > 0)
    {
        QPointF nPoint;
        if (checkSize)
        {
            nPoint = pointBySize(point);
        }
        else
        {
            nPoint = point;
        }

        int nx = nPoint.x() / m_gridStep;
        if (nPoint.x() - m_gridStep * nx > m_gridStep / 2.0)
        {
            ++nx;
        }

        if (checkSize && nx * m_gridStep > m_size.width())
        {
            --nx;
        }

        int ny = nPoint.y() / m_gridStep;
        if (nPoint.y() - m_gridStep * ny > m_gridStep / 2.0)
        {
            ++ny;
        }
        if (checkSize && ny * m_gridStep > m_size.height())
        {
            --ny;
        }

        return QPointF(nx * m_gridStep, ny * m_gridStep);
    }

    return point;
}

QPointF CanvasSchemeElement::pointBySize(const QPointF & point) const
{
    QPointF newPoint = point;

    if (point.x() < 0)
    {
        newPoint.setX(0);
    }
    else if (point.x() > m_size.width())
    {
        newPoint.setX(m_size.width());
    }

    if (point.y() < 0)
    {
        newPoint.setY(0);
    }
    else if (point.y() > m_size.height())
    {
        newPoint.setY(m_size.height());
    }

    return newPoint;
}

void CanvasSchemeElement::move(const QPointF & dp)
{
    Q_UNUSED(dp);
}








