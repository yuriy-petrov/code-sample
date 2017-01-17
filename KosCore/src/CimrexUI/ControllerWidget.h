#ifndef CONTROLLERWIDGET_H
#define CONTROLLERWIDGET_H

#include <QWidget>

class ContextHandler;
class CimrexModelBinding;
namespace Ui {
class ControllerWidget;
}

class ControllerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControllerWidget(QWidget *parent = 0);
    ~ControllerWidget();

    void setHendler(ContextHandler* handler);
    ContextHandler* handler() const;

    QStringList currentAvailableKeys();
    virtual bool eventFilter(QObject *obj, QEvent *ev);

    void setModelBinder(CimrexModelBinding* cmb);

//    void updateValueForKey(QString& key, int value);
//    void updateValueForKey(QString& key, double value);
//    void updateValueForKey(QString& key, QString& value);
//    void updateValueForKey(QString& key, bool value);
    void updateValueForKey(QString& key, const QVariant value);
    void updateValuesForKeys(QMap<QString, QVariant> values);
protected:
    virtual void keyReleaseEvent(QKeyEvent *ev);
private slots:
    void resendClickedElementByName(QString name);

    void on_pushButton_clicked();
    void on_up_button_clicked();
    void on_down_button_clicked();
    void on_next_button_clicked();
    void on_prev_button_clicked();
    void on_enter_button_clicked();

    void change_led_state(int id, bool flag);
    void change_switcher_state(int state);
private:
    Ui::ControllerWidget *ui;
    ContextHandler* _handler;
    QHash<QString, bool> _LEDState;
    CimrexModelBinding* _binder;
    QStringList _ledKeys;
    QString _password;
};

#endif // CONTROLLERWIDGET_H
