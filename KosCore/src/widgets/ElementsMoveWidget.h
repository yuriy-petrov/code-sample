#ifndef ELEMENTSMOVEWIDGET_H
#define ELEMENTSMOVEWIDGET_H

class SchemeDataProvider;

#include <QWidget>

class ElementsMoveWidget : public QWidget
{

    Q_OBJECT

public:

    explicit ElementsMoveWidget(QWidget * parent = 0);
    ~ElementsMoveWidget();

public slots:

    void setSchemeDataProvider(SchemeDataProvider * schemeDataProvider);

protected:

    virtual void paintEvent(QPaintEvent * event);
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);

private:

    QPixmap m_pixmap;

    SchemeDataProvider * m_schemeDataProvider;
    QPoint m_mouseLastPos;

};

#endif // ELEMENTSMOVEWIDGET_H
