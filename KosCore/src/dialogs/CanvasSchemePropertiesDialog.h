#ifndef CANVASSCHEMEPROPERTIESDIALOG_H
#define CANVASSCHEMEPROPERTIESDIALOG_H

class CanvasSchemeElement;
class SchemeScene;

#include <QDialog>

namespace Ui
{
    class CanvasSchemePropertiesDialog;
}

class CanvasSchemePropertiesDialog : public QDialog
{

    Q_OBJECT

public:

    CanvasSchemePropertiesDialog(CanvasSchemeElement * canvasSchemeElement,
                                 SchemeScene * schemeScene,
                                 QWidget * parent = 0);
    ~CanvasSchemePropertiesDialog();

private slots:

    void on_buttonBox_accepted();

    void on_tbGetZoom_clicked();

private:

    void load();
    void save();

private:

    Ui::CanvasSchemePropertiesDialog * ui;

    CanvasSchemeElement * m_canvasSchemeElement;
    SchemeScene * m_schemeScene;
};

#endif // CANVASSCHEMEPROPERTIESDIALOG_H
