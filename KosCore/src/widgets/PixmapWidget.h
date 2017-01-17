#ifndef PIXMAPWIDGET_H
#define PIXMAPWIDGET_H

#include <QWidget>

class PixmapWidget : public QWidget
{

    Q_OBJECT

public:

    explicit PixmapWidget(QWidget * parent = 0);
    ~PixmapWidget();

    QPixmap pixmap() const;
    void setPixmap(const QPixmap & pixmap);

protected:

    virtual void paintEvent(QPaintEvent * event);

private:

    QPixmap m_pixmap;

};

#endif // PIXMAPWIDGET_H
