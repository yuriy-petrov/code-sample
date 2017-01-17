#ifndef VALVESCHEMEELEMENTDIALOG_H
#define VALVESCHEMEELEMENTDIALOG_H

class ValveSchemeElement;
class SettingsStorage;
class QAbstractButton;
class CanvasSchemeElement;

#include "KosTypes.h"

#include <QDialog>

namespace Ui
{
    class ValveSchemeElementDialog;
}

class ValveSchemeElementDialog : public QDialog
{

    Q_OBJECT

public:

    ValveSchemeElementDialog(SettingsStorage * settingsStorage,
                             CanvasSchemeElement * canvasSchemeElement,
                             ValveSchemeElement * valveSchemeElement,
                             QWidget * parent = 0);
    ~ValveSchemeElementDialog();

private slots:

    void on_buttonBox_accepted();

private slots:

    void updatePixmap();

private:

    qreal rotateAngleFromUi();

    void load(ValveSchemeElement * valveSchemeElement);
    void save(ValveSchemeElement * valveSchemeElement);

private:

    Ui::ValveSchemeElementDialog * ui;

    SettingsStorage * m_settingsStorage;
    CanvasSchemeElement * m_canvasSchemeElement;
    ValveSchemeElement * m_valveSchemeElement;

    QList<KosTypes::ValveType> m_valveTypes;
    QList<KosTypes::SubstanceType> m_substanceTypes;

    bool m_isConfigured;

};

#endif // VALVESCHEMEELEMENTDIALOG_H
