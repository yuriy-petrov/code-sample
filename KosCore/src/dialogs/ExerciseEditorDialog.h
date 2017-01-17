#ifndef EXERCISEEDITORDIALOG_H
#define EXERCISEEDITORDIALOG_H

#include <QDialog>
#include <SettingsStorage.h>
#include <Exercise.h>

class SnapshotTableModel;
class ConditionsModel;
class SnapshotValvesModel;
class SnapshotPipesModel;
class SnapshotRinsersModel;
class SnapshotCoalescentFiltersModel;
class SnapshotHeatExchangersModel;
class SnapshotSeparatorsModel;
class CellStackEnableModel;


namespace Ui {
class ExerciseEditorDialog;
}

class ExerciseEditorDialog : public QDialog
{

    Q_OBJECT

public:

    explicit ExerciseEditorDialog(SettingsStorage * settingsStorage,
                                  const QStringList & schemeKeys,
                                  QWidget *parent = 0);
    ~ExerciseEditorDialog();

    void setExercise(Exercise::Pointer exercise);
    void applyChanges(); // применяет изменения к Exercise, переданному в setExercise

private:
    void exerciseToUi();
    void uiToExercise();
    void exerciseToEditableSnapshot();
    void exerciseToHystatMode();
    Q_SLOT void conditionsFullfilled(bool value);
    void saveState();
    void restoreState();


private:
    Ui::ExerciseEditorDialog *ui;
    SettingsStorage * m_settingsStorage;
    Exercise::Pointer m_Exercise;
    Snapshot m_EditableSnapshot;
    SnapshotTableModel * m_SnapshotModel;
    SnapshotValvesModel * m_SnapshotValvesModel;
    SnapshotPipesModel * m_SnapshotPipesModel;
    SnapshotRinsersModel * m_SnapshotRinsersModel;
    SnapshotCoalescentFiltersModel * m_SnapshotCoalescentModel;
    SnapshotHeatExchangersModel * m_SnapshotHeatExchangersModel;
    SnapshotSeparatorsModel * m_SeparatorsModel;
    SnapshotSeparatorsModel * m_WaterLocksModel;
    CellStackEnableModel * m_CSEnableModel;
    ConditionsModel * m_BasicCondsModel;
    ConditionsModel * m_N2PurgeCondsModel;
    ConditionsModel * m_H2ProdCondsModel;
    ConditionsModel * m_Cs1CondsModel;
    ConditionsModel * m_Cs2CondsModel;
};

#endif // EXERCISEEDITORDIALOG_H
