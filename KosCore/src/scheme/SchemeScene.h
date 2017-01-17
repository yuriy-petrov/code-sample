#ifndef SCHEMESCENE_H
#define SCHEMESCENE_H

class SchemeView;
class CanvasSchemeItem;
class AbstractSchemeItemContainer;
class SettingsStorage;
class QGraphicsScene;

#include <QObject>
#include <QSet>

class SchemeScene : public QObject
{

    Q_OBJECT

public:

    SchemeScene(SettingsStorage * settingsStorage,
                QObject * parent = 0);

    QGraphicsScene * scene() const;
    CanvasSchemeItem * canvasSchemeItem() const;
    SchemeView * schemeView() const;

    QSet<AbstractSchemeItemContainer*> schemeItemContainers() const;

    qreal zoomDelta() const;
    qreal zoom() const;

public slots:

    void setSchemeView(SchemeView * schemeView);
    void setCanvasSchemeItem(CanvasSchemeItem * canvasSchemeItem);

    void setZoom(const qreal & zoom);
    void insertItemContainer(AbstractSchemeItemContainer * schemeItemContainer);

protected slots:

    void canvasElementChanged();

private:

    SettingsStorage * m_settingsStorage;

    QGraphicsScene * m_scene;
    CanvasSchemeItem * m_canvasSchemeItem;
    QSet<AbstractSchemeItemContainer*> m_schemeItemContainers;

    SchemeView * m_schemeView;

    qreal m_zoomMinimum;
    qreal m_zoomMaximum;
    qreal m_zoomDelta;
    qreal m_zoom;

};

#endif // SCHEMESCENE_H
