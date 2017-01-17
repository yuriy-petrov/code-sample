#include "powerroomwidgetprivate.h"
#include "ui_powerroomwidget.h"

#include <ModelTypesExtractor.h>
#include <StringsKeys.h>

PowerRoomWidgetPrivate::PowerRoomWidgetPrivate(QWidget *parent)
    : QObject(parent)
    , ui(new Ui::PowerRoomWidget)
{
    ui->setupUi(parent);

    connect(ui->wPowerSwitch, SIGNAL(stateChanged(bool)),
            SLOT(powerStateChanged(bool)));

    ui->ciwAmpermeterCS1->setType(ClockIndicatorWidget::HYSTAT_ANGLED);
    ui->ciwAmpermeterCS1->setPointerHeightPercent(90);
    ui->ciwAmpermeterCS1->setTickHeightPix(7);
    ui->ciwAmpermeterCS1->setAxisLabelsFont(QFont("Arial", 7, QFont::Bold));
//    ui->ciwAmpermeterCS1->setDialColor(Qt::white);
    ui->ciwAmpermeterCS1->setText(tr("A"));
    ui->ciwAmpermeterCS1->setMaxValue(600);
    ui->ciwAmpermeterCS1->setTicksCount(6);
    ui->ciwAmpermeterCS1->setSubticksPerTickCount(10);

    ui->ciwAmpermeterCS2->setType(ClockIndicatorWidget::HYSTAT_ANGLED);
    ui->ciwAmpermeterCS2->setPointerHeightPercent(90);
    ui->ciwAmpermeterCS2->setTickHeightPix(7);
    ui->ciwAmpermeterCS2->setAxisLabelsFont(QFont("Arial", 7, QFont::Bold));
    ui->ciwAmpermeterCS2->setText(tr("A"));
    ui->ciwAmpermeterCS2->setMaxValue(600);
    ui->ciwAmpermeterCS2->setTicksCount(6);
    ui->ciwAmpermeterCS2->setSubticksPerTickCount(10);

    ui->ciwVoltmeterCS1->setType(ClockIndicatorWidget::HYSTAT_ANGLED);
    ui->ciwVoltmeterCS1->setPointerHeightPercent(90);
    ui->ciwVoltmeterCS1->setTickHeightPix(7);
    ui->ciwVoltmeterCS1->setAxisLabelsFont(QFont("Arial", 7, QFont::Bold));
    ui->ciwVoltmeterCS1->setText(tr("V"));
    ui->ciwVoltmeterCS1->setMaxValue(250);
    ui->ciwVoltmeterCS1->setTicksCount(5);
    ui->ciwVoltmeterCS1->setSubticksPerTickCount(10);

    ui->ciwVoltmeterCS2->setType(ClockIndicatorWidget::HYSTAT_ANGLED);
    ui->ciwVoltmeterCS2->setPointerHeightPercent(90);
    ui->ciwVoltmeterCS2->setTickHeightPix(7);
    ui->ciwVoltmeterCS2->setAxisLabelsFont(QFont("Arial", 7, QFont::Bold));
    ui->ciwVoltmeterCS2->setText(tr("V"));
    ui->ciwVoltmeterCS2->setMaxValue(250);
    ui->ciwVoltmeterCS2->setTicksCount(5);
    ui->ciwVoltmeterCS2->setSubticksPerTickCount(10);
}

PowerRoomWidgetPrivate::~PowerRoomWidgetPrivate()
{
    delete ui;
}

void PowerRoomWidgetPrivate::setSnapshot(const Snapshot &snapshot)
{
    Model::TypesExtractor getter(snapshot);

    ui->ciwAmpermeterCS1->setValue(getter.value(Model::ChartsValues::ITCS1));
    ui->ciwVoltmeterCS1->setValue(getter.value(Model::ChartsValues::UTCS1a) + getter.value(Model::ChartsValues::UTCS1b));

    ui->ciwAmpermeterCS2->setValue(getter.value(Model::ChartsValues::ITCS2));
    ui->ciwVoltmeterCS2->setValue(getter.value(Model::ChartsValues::UTCS2a) + getter.value(Model::ChartsValues::UTCS2b));
}

void PowerRoomWidgetPrivate::powerStateChanged(bool isPoweron)
{
    if(!m_storage.isNull()) {
        m_storage->setValue(Model::Power::Switch, isPoweron);
    }

    emit mainPowerChanged(isPoweron);
}
