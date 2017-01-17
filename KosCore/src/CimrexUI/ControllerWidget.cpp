#include "ControllerWidget.h"
#include "ui_ControllerWidget.h"
#include "ContextHandler.h"
#include "LEDWidget.h"
#include "ConfigReader.h"
#include <QMouseEvent>
#include "Page.h"
#include "CimrexModelBinding.h"
#include "buttoneventfilter.h"

ControllerWidget::ControllerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControllerWidget),
    _handler(0),
    _binder(0),
    _password("")
{
    ConfigReader reader(":/config/config.xml");
    ContextHandler* handler = new ContextHandler(reader.mainPage(), reader.defaultActions());

    ui->setupUi(this);
    QList<QLabel*> labelList;
    labelList = this->findChildren<QLabel*>();
    foreach(QLabel *label, labelList) {
        if (label->objectName().contains("lb_F_")){
            label->installEventFilter(this);
        }
        if (label->objectName().contains("switcher")){
            label->installEventFilter(this);
        }
    }

    _ledKeys << "led_1" << "led_2" << "led_3" << "led_4"
             << "led_5" << "led_6" << "led_7" << "led_8"
             << "led_9" << "led_10" << "led_11" << "led_12"
             << "led_13" << "led_14" << "led_15" << "led_16";
    setHendler(handler);
    QString str;
    QStringList lList;
    lList << "9" << "10" << "11"
                          << "12" << "13" << "14"
                          << "15" << "16";
    QStringList ledList;
    ledList << "1" << "2" << "3"
            << "4" << "5" << "6"
            << "7" << "8";
    foreach (str, lList) {
        QString f("F " + str);
        QLabel *label = findChild<QLabel *>("bottom_lb_F_" + str);
        QPixmap pixmap(*label->pixmap());
        QPainter painter(&pixmap);
        painter.setFont(QFont("Arial", 30));
        painter.setPen(Qt::black);
        QRect rect = pixmap.rect();
        rect.setHeight(rect.height()/2);
        painter.drawText(rect,Qt::AlignCenter, f);
        label->setProperty("pixmap", pixmap);
    }

    foreach (str, ledList) {
        QString f("LED " + str);
        QLabel *label = findChild<QLabel *>("led_" + str);
        QPixmap pixmap(*label->pixmap());
        QPainter painter(&pixmap);
        painter.setFont(QFont("Arial", 30));
        painter.setPen(Qt::black);
        QRect rect = pixmap.rect();
        rect.setHeight(rect.height() + 70);

        painter.drawText(rect,Qt::AlignCenter, f);
        label->setProperty("pixmap", pixmap);
    }

}

ControllerWidget::~ControllerWidget()
{
    delete ui;
    delete _handler;
}

void ControllerWidget::setHendler(ContextHandler *handler)
{
    _handler = handler;
    _handler->useThisBinder(_binder);
    _handler->setView(ui->webView);
    _handler->renderPage();
}

ContextHandler *ControllerWidget::handler() const
{
    return _handler;
}

QStringList ControllerWidget::currentAvailableKeys()
{
    QStringList retList;
    retList << _handler->currentPage()->keyMap().keys();
    return retList + _ledKeys;
}

bool ControllerWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (!_binder || !_binder->on()) {
        return false;
    }
//    if (ev->type() == QEvent::EnabledChange) {
//        ui->webView->hide();
//        return false;
//    } else {
//        ui->webView->show();
//    }
    if (ev->type() == QEvent::MouseButtonPress) {
        QMouseEvent* me = dynamic_cast<QMouseEvent*>(ev);
        if (me->button() == Qt::LeftButton) {
            qDebug() << "QMouse Press" << obj->objectName();
            resendClickedElementByName(obj->objectName());
        }
        if (obj->objectName() == "switcher") {
            QRect rect1(0,0,26,80);

            QRect rect2(26,0,26,80);

            QRect rect3(53,0,26,80);

            if (rect1.contains(me->pos(), true)) {
                change_switcher_state(1);
            } else if (rect2.contains(me->pos(), true)) {
                change_switcher_state(2);
            } else if (rect3.contains(me->pos(), true)) {
                change_switcher_state(3);
            };
        }
    }
    if (ev->type() == QEvent::MouseButtonRelease) {
        if (obj->objectName().contains("bottom_lb_F_")) {
            QLabel* label = qobject_cast<QLabel*>(obj);
            QString f = "F " + label->objectName().split('_').last();
            if (label) {
                if (!label->property("state").isNull()) {
                    return true;
                }
                QPixmap pixmap = label->property("pixmap").value<QPixmap>();
//                if (label->property("state").toBool()) {
//                    pixmap.load(":/images/f_led_red.png");
//                } else {
//                    pixmap.load(":/images/f_led_green.png");
//                }
                pixmap.load(":/images/f_led_default.png");

                QPainter painter(&pixmap);
                painter.setFont(QFont("Arial", 30));
                painter.setPen(Qt::black);
                QRect rect = pixmap.rect();
                rect.setHeight(rect.height()/2);
                painter.drawText(rect,Qt::AlignCenter, f);

                label->setProperty("pixmap", pixmap);
            }
        } else if (obj->objectName().contains("left_lb_F_")) {
            QLabel* label = qobject_cast<QLabel*>(obj);
            if (label) {
                QPixmap pixmap = label->property("pixmap").value<QPixmap>();
                pixmap.load(":/images/f_left_button.png");
                label->setProperty("pixmap", pixmap);
            }
        } else if (obj->objectName().contains("right_lb_F_")) {
            QLabel* label = qobject_cast<QLabel*>(obj);
            if (label) {
                QPixmap pixmap = label->property("pixmap").value<QPixmap>();
                pixmap.load(":/images/f_right_button.png");
                label->setProperty("pixmap", pixmap);
            }
        } else if (obj->objectName().contains("led_")) {
            QLabel* label = qobject_cast<QLabel*>(obj);
            QString f = "LED " + label->objectName().split('_').last();
            if (label) {
                if (!label->property("state").isNull()) {
                    return true;
                }
                QPixmap pixmap = label->property("pixmap").value<QPixmap>();

                pixmap.load(":/images/up_led_disable.png");

                QPainter painter(&pixmap);
                painter.setFont(QFont("Arial", 30));
                painter.setPen(Qt::black);
                QRect rect = pixmap.rect();
                rect.setHeight(rect.height() + 220);
                painter.drawText(rect,Qt::AlignCenter, f);

                label->setProperty("pixmap", pixmap);
            }
        }
    }
    return false;
}

void ControllerWidget::setModelBinder(CimrexModelBinding *cmb)
{
    _binder = cmb;
    _handler->useThisBinder(_binder);

    ButtonEventFilter * filter = new ButtonEventFilter(this);
    filter->setSnapshotStorage(_binder->snapshotStorage());
    filter->setEmergencyButton(ui->label_EmergencyStop);
    filter->setResetButton(ui->label_Reset);

}
void ControllerWidget::updateValueForKey(QString &key, const QVariant value)
{
    if (!_binder || !_binder->on()) {
        return;
    }
    if (_ledKeys.contains(key)) {
        change_led_state(key.split('_').last().toInt(), value.toBool());
    } else {
        _handler->changeValueByModelKey(key, value);
    }
}

void ControllerWidget::updateValuesForKeys(QMap<QString, QVariant> values)
{
    QString key;
    foreach (key, values.keys()) {
        updateValueForKey(key, values.value(key));
    }
}

void ControllerWidget::keyReleaseEvent(QKeyEvent *ev)
{
    if (_handler->currentPage()->id() == "login") {

        QString password("PWD");
        if ( (ev->key() >= Qt::Key_0) && (ev->key() <= Qt::Key_9)) {
            if (_password.length() == 4) {
                return;
            }
            _password.append("*");
        } else if ( (ev->key() == Qt::Key_Backspace )&& (_password.length() > 0) ) {
            _password.remove(_password.length() - 1, 1);
        }
        _handler->changeValueForKey(password, _password);
    }
}


void ControllerWidget::resendClickedElementByName(QString name)
{
    QStringList list = name.split('_');
    if (list.length() != 4) {
        return;
    }
    QString conc = list.at(2) + '_' + list.at(3);
    _handler->pressButtonById(conc);


}

void ControllerWidget::on_pushButton_clicked()
{
    //    ui->pushButton->setText(ui->pushButton->isChecked() ? tr("Off") : tr("On"));
    //    if (_binder)
    //        _binder->toogleKey(ui->pushButton->isChecked());
}

void ControllerWidget::on_up_button_clicked()
{
    _handler->currentPage()->nextKey();
    _handler->renderPage();
}

void ControllerWidget::on_down_button_clicked()
{
    _handler->currentPage()->previosKey();
    _handler->renderPage();
}

void ControllerWidget::on_next_button_clicked()
{

}

void ControllerWidget::on_prev_button_clicked()
{
}

void ControllerWidget::on_enter_button_clicked()
{
    QString key =_handler->currentPage()->currentSelectedKey();

    if (_handler->currentPage()->tmpKeyMap().contains(key)) {
        _handler->changeValueForKeyInModel(key, _handler->currentPage()->tmpKeyMap().value(key));
        //    ctx()->changeValueForKeyInModel(key, ctx()->currentPage()->tmpKeyMap().value(key));
        //    QVariantHash hash = ctx()->currentPage()->tmpKeyMap();
        //    foreach (QString key, _keyList) {
        //        ctx()->changeValueForKeyInModel(key, hash.value(key));
        _handler->currentPage()->flushTmpKey();
    }
}

void ControllerWidget::change_led_state(int id, bool flag)
{
    bool bottomLed = false;
    QLabel* label = findChild<QLabel*>(QString("led_%1").arg(id));
    QString f("F ");
    QString led("LED ");
    bool F_flag = false;
    bool LED_flag = false;
    if (!label) {
        bottomLed = true;
        label = findChild<QLabel*>(QString("bottom_lb_F_%1").arg(id));
        if (label) {
            label->setProperty("state", flag);
        }
        F_flag = true;
        f.append(QString::number(id));
    } else {
        LED_flag = true;
        led.append(QString::number(id));
    }
    QPixmap pixmap = label->property("pixmap").value<QPixmap>();
    if (flag) {
        if (bottomLed) {
            pixmap.load(":/images/f_led_red.png");
        } else {
            pixmap.load(":/images/up_led_red.png");
        }
    } else {
        if (bottomLed) {
            pixmap.load(":/images/f_led_green.png");
        } else {
            pixmap.load(":/images/up_led_green.png");
        }
    }
    QPainter painter(&pixmap);
    painter.setFont(QFont("Arial", 30));
    painter.setPen(Qt::black);
    QRect rect = pixmap.rect();
    rect.setHeight(rect.height()/2);
    if (F_flag)
        painter.drawText(rect,Qt::AlignCenter, f);
    if (LED_flag) {
        rect.setHeight(rect.height() + 220);
        painter.drawText(rect,Qt::AlignCenter, led);
    }
    label->setProperty("pixmap", pixmap);

}

void ControllerWidget::change_switcher_state(int state)
{
    QLabel* label = findChild<QLabel*>(QString("switcher"));
    QPixmap pixmap = label->property("pixmap").value<QPixmap>();
    switch (state) {
    case 1:{
            pixmap.load(":/images/switcher_stop.png");
            if (_binder)
                _binder->toogleKey(false);
        }
        break;
    case 3:{
            pixmap.load(":/images/switcher_start.png");
            if (_binder)
                _binder->toogleKey(true);
        }
        break;
    default:
        pixmap.load(":/images/switcher_off.png");
        break;
    }
    if (label)
        label->setProperty("pixmap", pixmap);

}
