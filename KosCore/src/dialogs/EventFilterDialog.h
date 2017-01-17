#ifndef EVENTFILTERDIALOG_H
#define EVENTFILTERDIALOG_H

class AbstractEventFilter;
class AbstractEventFilterWidget;
class SnapshotConditionModel;
class SnapshotCondition;

#include <QDialog>

namespace Ui
{
    class EventFilterDialog;
}

class EventFilterDialog : public QDialog
{

    Q_OBJECT

public:

    EventFilterDialog(AbstractEventFilter * prevEventFilter,
                      QWidget * parent = 0);
    ~EventFilterDialog();

    AbstractEventFilter * prevEventFilter() const;
    AbstractEventFilter * nextEventFilter() const;

private slots:

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_cbType_currentIndexChanged(int index);

    void on_tbSnapshotConditionAppend_clicked();

    void on_tbSnapshotConditionRemove_clicked();

private:

    void clear();

private:

    Ui::EventFilterDialog * ui;

    AbstractEventFilter * m_prevEventFilter;
    AbstractEventFilter * m_nextEventFilter;
    AbstractEventFilterWidget * m_eventFilterWidget;

    SnapshotCondition * m_snapshotCondition;
    SnapshotConditionModel * m_snapshotConditionModel;

};

#endif // EVENTFILTERDIALOG_H
