#include "equipmentroomwidgetprivate.h"
#include "ui_equipmentroomwidget.h"

#include <QtMath>
#include <QPaintEvent>

#include <ModelTypesExtractor.h>
#include <SchemeEventLogElement.h>
#include <physconst.h>

const int pipeWidth = 15;
const QColor pipeOutletColor("#737077");
const QColor pipeColor("#737077");

EquipmentRoomWidgetPrivate::EquipmentRoomWidgetPrivate(QWidget *parent)
    : QObject(parent)
    , ui(new Ui::EquipmentRoomWidget)
    , m_IsBV_N1adjustement(false)
    , m_IsBV_N3adjustement(false)
    , m_IsHV_Nadjustement(false)
{
    ui->setupUi(parent);

    ui->wBV_N1->setName("BV N1");
    ui->wBV_N1->setEndAngle(180.0);
    ui->wBV_N1->setRotatesCount(0.25);
    ui->wBV_N1->setOpenDirection(AbstractValveWidget::counterClockWise);

    ui->wBV_N3->setName("BV N3");
    ui->wBV_N3->setEndAngle(0.0);
    ui->wBV_N3->setRotatesCount(0.25);
    ui->wBV_N3->setOpenDirection(AbstractValveWidget::counterClockWise);

//    ui->wHV_N->setTracking(true);
    ui->wHV_N->setName("HV N");
    ui->wHV_N->setEndAngle(90.0);
    ui->wHV_N->setRotatesCount(3.0);
    ui->wHV_N->setOpenDirection(AbstractValveWidget::counterClockWise);

    ui->wPI_N->setText(tr("bar"));
    ui->wPI_N->setMaxValue(16);


    ui->labelPipesInlets->installEventFilter(this);
    ui->labelPipes1->installEventFilter(this);
    ui->labelPipes2->installEventFilter(this);
    ui->labelPipes3->installEventFilter(this);
    ui->labelPipesBottom->installEventFilter(this);
    ui->labelMV_N2->installEventFilter(this);
    ui->wPI_N->installEventFilter(this);

    ui->wBV_N1->installEventFilter(this);
    ui->wBV_N3->installEventFilter(this);
    ui->wHV_N->installEventFilter(this);

    connect(ui->wBV_N1, &AbstractValveWidget::changed,
            this, &EquipmentRoomWidgetPrivate::bv_n1_changed);
    connect(ui->wBV_N3, &AbstractValveWidget::changed,
            this, &EquipmentRoomWidgetPrivate::bv_n3_changed);
    connect(ui->wHV_N, &AbstractValveWidget::changed,
            this, &EquipmentRoomWidgetPrivate::hv_n_changed);
}

EquipmentRoomWidgetPrivate::~EquipmentRoomWidgetPrivate()
{
    delete ui;
}

bool EquipmentRoomWidgetPrivate::eventFilter(QObject *o, QEvent *e)
{
    switch(e->type()) {
        case QEvent::Paint:
        {
            QWidget* w = qobject_cast<QWidget*>(o);
            QPainter painter(w);
//            painter.setRenderHint(QPainter::Antialiasing, true);

            if(o == ui->labelPipesInlets) {
                drawNVerticalPipes(painter, w->rect(), 3);
                drawNVerticalPipesMount(painter, w->rect(), 3);
                return true;
            } else if(o == ui->labelPipes1) {
                drawNVerticalPipes(painter, w->rect(), 2);
                return true;
            } else if(o == ui->labelPipes2) {
                drawNVerticalPipes(painter, w->rect(), 2);
                return true;
            } else if(o == ui->labelPipes3) {
                drawNVerticalPipes(painter, w->rect(), 3);
                return true;
            } else if(o == ui->labelPipesBottom) {
                drawPipesBottom(painter, w->rect());
                return true;
            } else if(o == ui->labelMV_N2) {
                drawMagneticValve(painter, w->rect());
                return true;
            } else if(o == ui->wPI_N) {
                drawNVerticalPipes(painter, w->rect(), 1);
                return false;
            }

            break;
        }

        case QEvent::MouseButtonPress:
        {
            if(o == ui->wBV_N1) {
                m_IsBV_N1adjustement = true;
                return false;
            } else if(o == ui->wBV_N3) {
                m_IsBV_N3adjustement = true;
                return false;
            } else if(o == ui->wHV_N) {
                m_IsHV_Nadjustement = true;
                return false;
            }

            break;
        }

        case QEvent::MouseButtonRelease:
        {
            if(o == ui->wBV_N1) {
                m_IsBV_N1adjustement = false;
                return false;
            } else if(o == ui->wBV_N3) {
                m_IsBV_N3adjustement = false;
                return false;
            } else if(o == ui->wHV_N) {
                m_IsHV_Nadjustement = false;
                return false;
            }

            break;
        }
    }

    return false;
}

void EquipmentRoomWidgetPrivate::drawNVerticalPipesMount(QPainter &painter, const QRect &rect, int count)
{
    const int mountWidth = 50;
    const int mountHeight = 20;
    const QColor mountOutletColor("#000000");
    const QColor mountColor("#466d7e");

    const int screwSize = 5;
    const QColor screwOutletColor("#000000");
    const QColor screwColor("#6B7075");

    for(double x = (double)rect.width() / (double)count * 0.5; x < rect.width(); x += (double)rect.width() / (double)count) {
        QRect mountRect(x - mountWidth / 2, (rect.height() - mountHeight) / 2, mountWidth, mountHeight);
        painter.setPen(QPen(mountOutletColor, 2));
        painter.setBrush(mountColor);
        painter.drawRect(mountRect);

        QRect screwRect(x + mountWidth / 3,
                        mountRect.y() + mountRect.height() / 2 - screwSize / 2,
                        screwSize, screwSize);
        painter.setPen(QPen(screwOutletColor, 1));
        painter.setBrush(screwColor);
        painter.drawEllipse(screwRect);
    }

}

void EquipmentRoomWidgetPrivate::drawNVerticalPipes(QPainter &painter, const QRect &rect, int count)
{
    for(double x = (double)rect.width() / (double)count * 0.5; x < rect.width(); x += (double)rect.width() / (double)count) {
        QRect pipeRect(x - (double)pipeWidth * 0.5, 0, pipeWidth, rect.height());
        painter.setPen(QPen(pipeOutletColor, 1));
        painter.setBrush(pipeColor);
        painter.drawRect(pipeRect);
    }
}

void EquipmentRoomWidgetPrivate::drawPipesBottom(QPainter &painter, const QRect &rect)
{
    // 3 верхних трубы
    drawNVerticalPipes(painter, rect.adjusted(0, 0, 0, -rect.height() * 0.5 - pipeWidth * 0.5), 3);

    // левая труба
    QRect pipeRect(((double)rect.width() / 3.0 - (double)pipeWidth) / 2.0,
                   rect.height() / 3,
                   pipeWidth,
                   2 * rect.height() / 3);
    painter.setPen(QPen(pipeOutletColor, 1));
    painter.setBrush(pipeColor);
    painter.drawRect(pipeRect);

    // правая труба
    pipeRect = QRect(rect.width() - ((double)rect.width() / 3.0 + (double)pipeWidth) / 2.0,
                     rect.height() / 3,
                     pipeWidth,
                     2 * rect.height() / 3);
    painter.drawRect(pipeRect);

    // нижняя горизонтальная труба
    pipeRect = QRect(((double)rect.width() / 3.0 - (double)pipeWidth) / 2.0,
                     rect.height() - pipeWidth - 1,
                     rect.width() / 3 * 2 + pipeWidth,
                     pipeWidth);
    painter.drawRect(pipeRect);

    // средняя горизонтальная труба
    pipeRect = QRect(((double)rect.width() / 3.0 * 3.0 - (double)pipeWidth) / 2.0,
                     rect.height() / 3 + pipeWidth,
                     rect.width() - rect.width() / 3 * 2,
                     pipeWidth);
    painter.drawRect(pipeRect);

    // соединение труб
    const QColor junctionOutloneColor("#000000");
    const QColor junctionColor("#848484");
    const double partLength = 20;
    const double juncWidth = pipeWidth + 5;
    QPolygon junction(8);
    junction.setPoint(0,
                      rect.width() - ((double)rect.width() / 3.0 + juncWidth) / 2.0,
                      rect.height() / 3.0 + pipeWidth / 2.0 - partLength);
    junction.setPoint(1,
                      rect.width() - ((double)rect.width() / 3.0 + juncWidth) / 2.0 + juncWidth,
                      rect.height() / 3.0 + pipeWidth / 2.0 - partLength);
    junction.setPoint(2,
                      rect.width() - ((double)rect.width() / 3.0 + juncWidth) / 2.0 + juncWidth,
                      rect.height() / 3.0 + pipeWidth / 2.0 + partLength * 2 + pipeWidth);
    junction.setPoint(3,
                      rect.width() - ((double)rect.width() / 3.0 + juncWidth) / 2.0,
                      rect.height() / 3.0 + pipeWidth / 2.0 + partLength * 2 + pipeWidth);
    junction.setPoint(4,
                      rect.width() - ((double)rect.width() / 3.0 + juncWidth) / 2.0,
                      rect.height() / 3.0 + pipeWidth * 1.5 + juncWidth / 2.0);
    junction.setPoint(5,
                      rect.width() - ((double)rect.width() / 3.0 + juncWidth) / 2.0 - partLength,
                      rect.height() / 3.0 + pipeWidth * 1.5 + juncWidth / 2.0);
    junction.setPoint(6,
                      rect.width() - ((double)rect.width() / 3.0 + juncWidth) / 2.0 - partLength,
                      rect.height() / 3.0 + pipeWidth * 1.5 + juncWidth / 2.0 - juncWidth);
    junction.setPoint(7,
                      rect.width() - ((double)rect.width() / 3.0 + juncWidth) / 2.0,
                      rect.height() / 3.0 + pipeWidth * 1.5 + juncWidth / 2.0 - juncWidth);

    painter.setPen(QPen(junctionOutloneColor, 2));
    painter.setBrush(junctionColor);

    painter.drawPolygon(junction);

}

void EquipmentRoomWidgetPrivate::drawMagneticValve(QPainter &painter, const QRect &rect)
{
    const QColor valveOutlineColor("#414141");
    const QColor valveColor("#212121");

    drawNVerticalPipes(painter, rect, 1);

    double sideWidth = qSin(qDegreesToRadians(45.0)) * qMin(rect.width(), rect.height());
    QRect valveRect(-sideWidth * 0.5, -sideWidth * 0.5, sideWidth, sideWidth);

    QTransform transform;
    transform.translate(rect.center().x(), rect.center().y());
    transform.rotate(45.0);

    painter.setTransform(transform);

    painter.setPen(QPen(valveOutlineColor, 5));
    painter.setBrush(valveColor);

    painter.drawRect(valveRect);
}

void EquipmentRoomWidgetPrivate::update(const Snapshot &snapshot)
{
    Model::TypesExtractor getter(snapshot);

    if(!m_IsBV_N1adjustement) {
        ui->wBV_N1->setClosurePercent(getter.valve(Model::Valves::BV_N1).closingLevel());
    }
    if(!m_IsBV_N3adjustement) {
        ui->wBV_N3->setClosurePercent(getter.valve(Model::Valves::BV_N3).closingLevel());
    }
    if(!m_IsHV_Nadjustement) {
        ui->wHV_N->setClosurePercent(getter.valve(Model::Valves::HV_N).closingLevel());
    }
    ui->wPI_N->setValue(PhysConst::Pa_to_bar(getter.value(Model::Purge::N2_PRESSURE) * 1000.0));
}

void EquipmentRoomWidgetPrivate::bv_n1_changed(int closurePercent, bool isFinal)
{
    if(m_storage.isNull()) {
        return;
    }

    bool stateChanged;
    Model::TypesExtractor getter(m_storage->snapshot());
    Model::Valve valve = getter.valve(Model::Valves::BV_N1);

    stateChanged = valve.isOpen();
    valve.setClosingLevel(closurePercent);
    stateChanged = stateChanged != valve.isOpen();

    m_storage->setValue(Model::Valves::BV_N1, valve.toVariant());

    if(stateChanged || isFinal) {
        sendValveToLog(Model::Valves::BV_N1, valve, stateChanged);
    }
}

void EquipmentRoomWidgetPrivate::bv_n3_changed(int closurePercent, bool isFinal)
{
    if(m_storage.isNull()) {
        return;
    }

    bool stateChanged;
    Model::TypesExtractor getter(m_storage->snapshot());
    Model::Valve valve = getter.valve(Model::Valves::BV_N3);

    stateChanged = valve.isOpen();
    valve.setClosingLevel(closurePercent);
    stateChanged = stateChanged != valve.isOpen();

    m_storage->setValue(Model::Valves::BV_N3, valve.toVariant());

    if(stateChanged || isFinal) {
        sendValveToLog(Model::Valves::BV_N3, valve, stateChanged);
    }
}

void EquipmentRoomWidgetPrivate::hv_n_changed(int closurePercent, bool isFinal)
{
    if(m_storage.isNull()) {
        return;
    }

    bool stateChanged;
    Model::TypesExtractor getter(m_storage->snapshot());
    Model::Valve valve = getter.valve(Model::Valves::HV_N);

    stateChanged = valve.isOpen();
    valve.setClosingLevel(closurePercent);
    stateChanged = stateChanged != valve.isOpen();

    m_storage->setValue(Model::Valves::HV_N, valve.toVariant());

    if(stateChanged || isFinal) {
        sendValveToLog(Model::Valves::HV_N, valve, stateChanged);
    }
}

void EquipmentRoomWidgetPrivate::sendValveToLog(const QString &key, const Model::Valve &valve, bool stateChanged)
{
    ValveSchemeElement valveElement;
    valveElement.setNodeKey(key);
    valveElement.setClosePercentage(valve.closingLevel());

    // отправка сообщения в лог
    SchemeEventLogElement logElement;
    logElement.setJsonDetails(valveElement.toJsonObject());

    logElement.setActionType(SchemeEventLogElement::ActionType::ValveClosePercentageChanged);

    emit eventLogGenerated(&logElement);
}
