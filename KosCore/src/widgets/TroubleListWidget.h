#ifndef TROUBLELISTWIDGET_H
#define TROUBLELISTWIDGET_H

class TroubleListController;
class QCheckBox;

#include <QWidget>

#include "Trouble.h"

namespace Ui
{
    class TroubleListWidget;
}

class TroubleListWidget : public QWidget
{

    Q_OBJECT

public:

    explicit TroubleListWidget(QWidget * parent = 0);
    ~TroubleListWidget();

    bool isCheckboxEnabled() const;
    void setCheckboxEnabled(bool isCheckboxEnabled);

public slots:

    void setTroubleListController(TroubleListController * troubleListController);

private slots:

    void troublesChanged(QList<Trouble> troubles);
    void activeTroublesChanged(QSet<QString> activeTroubles);
    void checkboxToggled(bool toggled);

private:

    Ui::TroubleListWidget * ui;

    TroubleListController * m_troubleListController;
    QHash<QString,QCheckBox*> m_checkboxes;
    bool m_isCheckboxEnabled;

};

#endif // TROUBLELISTWIDGET_H
