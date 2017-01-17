#ifndef MODELEVENTFILTERWIDGET_H
#define MODELEVENTFILTERWIDGET_H

#include <AbstractEventFilterWidget.h>

namespace Ui {
class ModelEventFilterWidget;
}

class ModelEventFilterWidget : public AbstractEventFilterWidget
{
    Q_OBJECT

public:
    enum EventType {
        HYSTAT_MODE,
        POWER_SWITCH,
        CELL_STACK,
        HW_SWITCH
    };

public:
    explicit ModelEventFilterWidget(QWidget *parent = 0);
    ~ModelEventFilterWidget();

    // AbstractEventFilterWidget interface
public:
    virtual bool isValid();
    virtual QString errorText();

public slots:
    virtual void save(AbstractEventFilter *eventFilter);
    virtual void load(AbstractEventFilter *eventFilter);

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::ModelEventFilterWidget *ui;
    AbstractEventFilterWidget * m_eventWidget;
};

Q_DECLARE_METATYPE( ModelEventFilterWidget::EventType )

#endif // MODELEVENTFILTERWIDGET_H
