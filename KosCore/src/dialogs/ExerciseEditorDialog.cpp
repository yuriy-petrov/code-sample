#include "ExerciseEditorDialog.h"
#include "ui_ExerciseEditorDialog.h"
#include "snapshottablemodel.h"
#include "conditionsmodel.h"
#include "snapshotvalvesmodel.h"
#include "snapshotpipesmodel.h"
#include "snapshotrinsersmodel.h"
#include "snapshotcoalescentfiltersmodel.h"
#include "snapshotheatexchangersmodel.h"
#include "snapshotseparatorsmodel.h"
#include "cellstackenablemodel.h"
#include "comboboxitemdelegate.h"
#include "StringsKeys.h"
#include "modeltypes.h"
#include "EventFilterProviderWidget.h"
#include "modeltypeshelper.h"

#include <log.h>

ExerciseEditorDialog::ExerciseEditorDialog(SettingsStorage * settingsStorage,
                                           const QStringList & schemeKeys,
                                           QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExerciseEditorDialog)
    , m_settingsStorage(settingsStorage)
    , m_SnapshotModel(new SnapshotTableModel(this))
    , m_SnapshotValvesModel(new SnapshotValvesModel(this))
    , m_SnapshotPipesModel(new SnapshotPipesModel(this))
    , m_SnapshotRinsersModel(new SnapshotRinsersModel(this))
    , m_SnapshotCoalescentModel(new SnapshotCoalescentFiltersModel(this))
    , m_SnapshotHeatExchangersModel(new SnapshotHeatExchangersModel(this))
    , m_SeparatorsModel(new SnapshotSeparatorsModel(this))
    , m_WaterLocksModel(new SnapshotSeparatorsModel(this))
    , m_BasicCondsModel(new ConditionsModel(this))
    , m_CSEnableModel(new CellStackEnableModel(this))
    , m_N2PurgeCondsModel(new ConditionsModel(this))
    , m_H2ProdCondsModel(new ConditionsModel(this))
    , m_Cs1CondsModel(new ConditionsModel(this))
    , m_Cs2CondsModel(new ConditionsModel(this))
{
    ui->setupUi(this);
    ui->comboBoxSchemeKey->addItems(schemeKeys);

    ui->tableViewInitValues->setModel(m_SnapshotModel);

    ui->tableViewValves->setModel(m_SnapshotValvesModel);
    ComboboxItemDelegate * delegate = new ComboboxItemDelegate(ui->tableViewValves);
    ui->tableViewValves->setItemDelegateForColumn(SnapshotValvesModel::COL_POSITION,
                                                  delegate);
    ui->tableViewValves->setItemDelegateForColumn(SnapshotValvesModel::COL_STATUS,
                                                  delegate);

    ui->tableViewPipes->setModel(m_SnapshotPipesModel);
    delegate = new ComboboxItemDelegate(ui->tableViewPipes);
    ui->tableViewPipes->setItemDelegateForColumn(SnapshotPipesModel::COL_SUBSTANCE,
                                                 delegate);

    ui->tableViewRinsers->setModel(m_SnapshotRinsersModel);
    delegate = new ComboboxItemDelegate(ui->tableViewRinsers);
    ui->tableViewRinsers->setItemDelegateForColumn(SnapshotRinsersModel::COL_SUBSTANCE,
                                                   delegate);

    ui->tableViewCoalescentFilters->setModel(m_SnapshotCoalescentModel);
    delegate = new ComboboxItemDelegate(ui->tableViewCoalescentFilters);
    ui->tableViewCoalescentFilters->setItemDelegateForColumn(SnapshotCoalescentFiltersModel::COL_SUBSTANCE,
                                                             delegate);

    ui->tableViewHeatExchangers->setModel(m_SnapshotHeatExchangersModel);
    delegate = new ComboboxItemDelegate(ui->tableViewHeatExchangers);
    ui->tableViewHeatExchangers->setItemDelegateForColumn(SnapshotHeatExchangersModel::COL_SUBSTANCE,
                                                          delegate);

    ui->tableViewSeparators->setModel(m_SeparatorsModel);
    delegate = new ComboboxItemDelegate(ui->tableViewSeparators);
    ui->tableViewSeparators->setItemDelegateForColumn(SnapshotSeparatorsModel::COL_FLUID_SUBSTANCE,
                                                      delegate);
    ui->tableViewSeparators->setItemDelegateForColumn(SnapshotSeparatorsModel::COL_GAS_SUBSTANCE,
                                                      delegate);

    ui->tableViewWaterLocks->setModel(m_WaterLocksModel);
    delegate = new ComboboxItemDelegate(ui->tableViewWaterLocks);
    ui->tableViewWaterLocks->setItemDelegateForColumn(SnapshotSeparatorsModel::COL_FLUID_SUBSTANCE,
                                                      delegate);
    ui->tableViewWaterLocks->setItemDelegateForColumn(SnapshotSeparatorsModel::COL_GAS_SUBSTANCE,
                                                      delegate);

    ui->tableViewCSEnable->setModel(m_CSEnableModel);

    ui->tableViewBasicConds->setModel(m_BasicCondsModel);
    ui->tableViewN2PurgeConds->setModel(m_N2PurgeCondsModel);
    ui->tableViewH2ProdConds->setModel(m_H2ProdCondsModel);
    ui->tableViewCs1Conds->setModel(m_Cs1CondsModel);
    ui->tableViewCs2Conds->setModel(m_Cs2CondsModel);

    connect(m_BasicCondsModel, &ConditionsModel::conditionsFullfilled,
            this, &ExerciseEditorDialog::conditionsFullfilled);
    connect(m_N2PurgeCondsModel, &ConditionsModel::conditionsFullfilled,
            this, &ExerciseEditorDialog::conditionsFullfilled);
    connect(m_H2ProdCondsModel, &ConditionsModel::conditionsFullfilled,
            this, &ExerciseEditorDialog::conditionsFullfilled);
    connect(m_Cs1CondsModel, &ConditionsModel::conditionsFullfilled,
            this, &ExerciseEditorDialog::conditionsFullfilled);
    connect(m_Cs2CondsModel, &ConditionsModel::conditionsFullfilled,
            this, &ExerciseEditorDialog::conditionsFullfilled);

    restoreState();
}

ExerciseEditorDialog::~ExerciseEditorDialog()
{
    saveState();
    delete ui;
}

void ExerciseEditorDialog::setExercise(Exercise::Pointer exercise)
{
    m_Exercise = exercise;
    ui->wStagesEventFilterProvider->setEventFilterProvider(m_Exercise->stagesEventFilterProvider());
    ui->wModesEventFilterProvider->setEventFilterProvider(m_Exercise->modesEventFilterProvider());
    exerciseToUi();
}

void ExerciseEditorDialog::applyChanges()
{
    uiToExercise();
}

void ExerciseEditorDialog::exerciseToUi()
{
    ui->lineEditTitle->setText(m_Exercise->title());
    ui->comboBoxSchemeKey->setCurrentText(m_Exercise->defaultSchemeKey());

    exerciseToHystatMode();

    exerciseToEditableSnapshot();

    ui->comboBoxMainPower->setCurrentIndex(m_EditableSnapshot.value(Model::Power::Switch).toBool() ? 0 : 1);

    ui->comboBoxEmergencyButton->setCurrentIndex(m_EditableSnapshot.value(Model::EMERGENCY_BUTTON).toBool() ? 1 : 0);

    m_SnapshotModel->setValues(Model::initialKeys());
    m_SnapshotModel->setSnapshot(&m_EditableSnapshot);

    m_SnapshotValvesModel->setValues(Model::Valves::keys());
    m_SnapshotValvesModel->setSnapshot(&m_EditableSnapshot);

    m_SnapshotPipesModel->setValues(Model::Pipes::keys());
    m_SnapshotPipesModel->setSnapshot(&m_EditableSnapshot);

    m_SnapshotRinsersModel->setValues(Model::Rinsers::keys());
    m_SnapshotRinsersModel->setSnapshot(&m_EditableSnapshot);

    m_SnapshotCoalescentModel->setValues(Model::CoalescentFilters::keys());
    m_SnapshotCoalescentModel->setSnapshot(&m_EditableSnapshot);

    m_SnapshotHeatExchangersModel->setValues(Model::HeatExchangers::keys());
    m_SnapshotHeatExchangersModel->setSnapshot(&m_EditableSnapshot);

    m_SeparatorsModel->setValues(Model::Separators::keys());
    m_SeparatorsModel->setSnapshot(&m_EditableSnapshot);

    m_WaterLocksModel->setValues(Model::WaterLocks::keys());
    m_WaterLocksModel->setSnapshot(&m_EditableSnapshot);

    m_CSEnableModel->setValues(Model::CellStack::Enable::keys());
    m_CSEnableModel->setSnapshot(&m_EditableSnapshot);

    m_BasicCondsModel->setValues(Model::Conditions::Basic::editableKeys());
    m_BasicCondsModel->setSnapshot(&m_EditableSnapshot);

    m_N2PurgeCondsModel->setValues(Model::Conditions::N2Purge::editableKeys());
    m_N2PurgeCondsModel->setSnapshot(&m_EditableSnapshot);

    m_H2ProdCondsModel->setValues(Model::Conditions::H2Production::editableKeys());
    m_H2ProdCondsModel->setSnapshot(&m_EditableSnapshot);

    m_Cs1CondsModel->setValues(Model::Conditions::CS1::editableKeys());
    m_Cs1CondsModel->setSnapshot(&m_EditableSnapshot);

    m_Cs2CondsModel->setValues(Model::Conditions::CS2::editableKeys());
    m_Cs2CondsModel->setSnapshot(&m_EditableSnapshot);
}

void ExerciseEditorDialog::uiToExercise()
{
    m_Exercise->setTitle(ui->lineEditTitle->text());
    m_Exercise->setDefaultSchemeKey(ui->comboBoxSchemeKey->currentText());

    m_EditableSnapshot.setValue(Model::HYSTAT_Mode, ui->comboBoxMode->currentData(), 0);
    m_EditableSnapshot.setValue(Model::Power::Switch, ui->comboBoxMainPower->currentIndex() == 0);
    m_EditableSnapshot.setValue(Model::EMERGENCY_BUTTON, ui->comboBoxEmergencyButton->currentIndex() == 1);

    m_EditableSnapshot.setValue(Model::Conditions::Result::Basic, m_BasicCondsModel->checkConditions());
    m_EditableSnapshot.setValue(Model::Conditions::Result::N2Purge, m_N2PurgeCondsModel->checkConditions());
    m_EditableSnapshot.setValue(Model::Conditions::Result::H2Production, m_H2ProdCondsModel->checkConditions());
    m_EditableSnapshot.setValue(Model::Conditions::Result::CS1, m_Cs1CondsModel->checkConditions());
    m_EditableSnapshot.setValue(Model::Conditions::Result::CS2, m_Cs2CondsModel->checkConditions());
    m_EditableSnapshot.setValue(Model::Conditions::Result::CS3, true);
    m_EditableSnapshot.setValue(Model::Conditions::Result::CS4, true);

    m_Exercise->setInitialValues(m_EditableSnapshot);
}

void ExerciseEditorDialog::exerciseToEditableSnapshot()
{
    m_EditableSnapshot = m_Exercise->initialValues();

    if(m_EditableSnapshot.values().isEmpty()) {
        foreach(const Snapshot::Key& key, Model::initialKeys()) {
            m_EditableSnapshot.setValue(key, 0, 0);
        }
    }
}

void ExerciseEditorDialog::exerciseToHystatMode()
{
    ui->comboBoxMode->clear();

    foreach(Model::HystatMode::Type mode, Model::TypesHelper::hystatModeNames().keys()) {
        ui->comboBoxMode->addItem(Model::TypesHelper::hystatModeToString(mode), QVariant::fromValue(mode));
    }

//    ui->comboBoxMode->addItem(tr("Standby N2 purge"), QVariant::fromValue(Model::HystatMode::StandbyN2Purge));
//    ui->comboBoxMode->addItem(tr("N2 purge"), QVariant::fromValue(Model::HystatMode::N2Purge));
//    ui->comboBoxMode->addItem(tr("Standby H2 purge"), QVariant::fromValue(Model::HystatMode::StandbyH2Purge));
//    ui->comboBoxMode->addItem(tr("H2 purge"), QVariant::fromValue(Model::HystatMode::H2Purge));
//    ui->comboBoxMode->addItem(tr("Standby H2 production"), QVariant::fromValue(Model::HystatMode::StandbyH2Production));
//    ui->comboBoxMode->addItem(tr("H2 production"), QVariant::fromValue(Model::HystatMode::H2Production));

    switch(m_Exercise->initialValues().value(Model::HYSTAT_Mode).value<Model::HystatMode::Type>()) {
    default:
    case Model::HystatMode::StandbyN2Purge:
    {
        ui->comboBoxMode->setCurrentIndex(0);
        break;
    }
    case Model::HystatMode::N2Purge:
    {
        ui->comboBoxMode->setCurrentIndex(1);
        break;
    }
    case Model::HystatMode::StandbyH2Purge:
    {
        ui->comboBoxMode->setCurrentIndex(2);
        break;
    }
    case Model::HystatMode::H2Purge:
    {
        ui->comboBoxMode->setCurrentIndex(3);
        break;
    }
    case Model::HystatMode::StandbyH2Production:
    {
        ui->comboBoxMode->setCurrentIndex(4);
        break;
    }
    case Model::HystatMode::H2Production:
    {
        ui->comboBoxMode->setCurrentIndex(5);
        break;
    }
    }
}

void ExerciseEditorDialog::conditionsFullfilled(bool value)
{
    if(sender() == m_BasicCondsModel) {
        ui->tabWidgetConditions->tabBar()->setTabTextColor(ui->tabWidgetConditions->indexOf(ui->tabBasicConds),
                                                           value ? "green" : "red");
    } else if(sender() == m_N2PurgeCondsModel) {
        ui->tabWidgetConditions->tabBar()->setTabTextColor(ui->tabWidgetConditions->indexOf(ui->tabN2PurgeConds),
                                                           value ? "green" : "red");
    } else if(sender() == m_H2ProdCondsModel) {
        ui->tabWidgetConditions->tabBar()->setTabTextColor(ui->tabWidgetConditions->indexOf(ui->tabH2ProductionConds),
                                                           value ? "green" : "red");
    } else if(sender() == m_Cs1CondsModel) {
        ui->tabWidgetConditions->tabBar()->setTabTextColor(ui->tabWidgetConditions->indexOf(ui->tabCS1Conds),
                                                           value ? "green" : "red");
    } else if(sender() == m_Cs2CondsModel) {
        ui->tabWidgetConditions->tabBar()->setTabTextColor(ui->tabWidgetConditions->indexOf(ui->tabCS2Conds),
                                                           value ? "green" : "red");
    }

    ui->tabWidget->tabBar()->setTabTextColor(ui->tabWidget->indexOf(ui->tabConditions),
                                             m_BasicCondsModel->checkConditions() &&
                                             m_N2PurgeCondsModel->checkConditions() &&
                                             m_H2ProdCondsModel->checkConditions() &&
                                             m_Cs1CondsModel->checkConditions() &&
                                             m_Cs2CondsModel->checkConditions() ?
                                                 "green" : "red");
}

void ExerciseEditorDialog::saveState()
{
    m_settingsStorage->setRawValue("size", size(), objectName());
}

void ExerciseEditorDialog::restoreState()
{
    resize(m_settingsStorage->rawValue("size", size(), objectName()).toSize());
    ui->wStagesEventFilterProvider->setSettingsStorage(m_settingsStorage);
    ui->wModesEventFilterProvider->setSettingsStorage(m_settingsStorage);
}
