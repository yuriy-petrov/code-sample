#ifndef BASICSCHEMEELEMENTDIALOG_H
#define BASICSCHEMEELEMENTDIALOG_H

class QAbstractButton;
class SettingsStorage;
class CanvasSchemeElement;

#include "BasicSchemeElement.h"
#include "KosTypes.h"

#include <QDialog>

namespace Ui
{
    class BasicSchemeElementDialog;
}

class BasicSchemeElementDialog : public QDialog
{

    Q_OBJECT

public:

    BasicSchemeElementDialog(SettingsStorage * settingsStorage,
                             CanvasSchemeElement * canvasSchemeElement,
                             BasicSchemeElement * basicSchemeElement,
                             QWidget * parent = 0);
    ~BasicSchemeElementDialog();

private slots:

    void on_buttonBox_accepted();

    void on_cbType_currentIndexChanged(int index);
    void on_bgRotation_buttonToggled(QAbstractButton * button, bool checked);
    void on_bgMirrored_buttonToggled(QAbstractButton * button, bool checked);
    void on_sbState_valueChanged(int arg1);
    void on_tbOtherColor_clicked();

    void on_cbSubstanceType_currentIndexChanged(int index);

private:

    qreal rotateAngleFromUi();

private slots:

    void updatePixmap();

    void load(BasicSchemeElement * basicSchemeElement);
    void save(BasicSchemeElement * basicSchemeElement);

private:

    Ui::BasicSchemeElementDialog * ui;

    SettingsStorage * m_settingsStorage;
    CanvasSchemeElement * m_canvasSchemeElement;
    BasicSchemeElement * m_basicSchemeElement;

    QList<KosTypes::BasicElementType> m_basicSchemeElementTypes;
    QList<KosTypes::SubstanceType> m_substanceTypes;

    bool m_isConfigured;

};

#endif // BASICSCHEMEELEMENTDIALOG_H
