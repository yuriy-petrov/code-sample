#ifndef CLOCKINDICATORWIDGET_H
#define CLOCKINDICATORWIDGET_H

#include <QWidget>

class ClockIndicatorPrivate;

class ClockIndicatorWidget : public QWidget
{
    Q_OBJECT

public:
    enum Type {
        Classic,        // классический вид (стрелка внизу посередине)
        HYSTAT_ANGLED   // стрелка в правом нижнем углу
    };

public:
    explicit ClockIndicatorWidget(QWidget *parent = 0);
    ~ClockIndicatorWidget();

    void setType(ClockIndicatorWidget::Type type);
    ClockIndicatorWidget::Type type() const;

    Q_SLOT void setValue(double value);    // положение стрелки в значениях оси
    void setMaxValue(double value); // максимальное значение на оси

    // текст внизу на шкале у основания стрелки
    void setText(const QString& value); // текст на шкале
    void setTextFont(const QFont& font);  // шрифт текста на шкале
    void setTextColor(const QColor& color); // цвет текста

    // корпус
    void setCaseWidth(double value);    // толщина боковых стенок корпуса
    void setCaseColor(const QColor& color); // цвет корпуса

    // нижняя накладка на корпусе
    void setBottomHeightPercent(int value);  // размер нижней накладки корпуса, в % размера корпуса
    void setBottomColor(const QColor& color); // цвет нижней накладки

    // стрелка
    void setPointerWidthPix(int value);         // толщина стрелки, в пикселях
    void setPointerBottomPercent(int value); // положение оси вращения стрелки, в % размера нижней накладки
    void setPointerHeightPercent(int value); // размер стрелки, в % размера корпуса
    void setPointerColor(const QColor& color); // цвет стрелки

    void setDialColor(const QColor& color); // цвет шкалы (фон)

    // ось
    void setAxisHeightPercent(int value); // положение оси, в % от размера стрелки
    void setTickHeightPix(int value); // высота основных (с цифрами) рисок, в пикселях
    void setSubtickHeightPix(int value); // высота промежуточных рисок, в пикселях
    void setTickWidthPix(int value);  // толщина основных рисок
    void setSubtickWidthPix(int value);  // толщина промежуточных рисок
    void setTicksCount(int value);  // число основных (с подписями) рисок
    void setSubticksPerTickCount(int value);  // число промежуточных рисок между основными рисками
    void setAxisLabelsFont(const QFont& font); // шрифт чисел на шкале
    void setAxisTicksColor(const QColor& color); // цвет рисок
    void setAxisLabelsColor(const QColor& color); // цвет чисел на шкале

public:
    void paintEvent(QPaintEvent* e);

private:
    ClockIndicatorPrivate *m_private;
};

#endif // CLOCKINDICATORWIDGET_H
