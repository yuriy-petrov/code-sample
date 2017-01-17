#ifndef TEXTSCHEMEELEMENTDIALOG_H
#define TEXTSCHEMEELEMENTDIALOG_H

class QAbstractButton;
class SettingsStorage;

#include "TextSchemeElement.h"

#include <QDialog>

namespace Ui
{
    class TextSchemeElementDialog;
}

class TextSchemeElementDialog : public QDialog
{

    Q_OBJECT

public:

    TextSchemeElementDialog(SettingsStorage * settingsStorage,
                            TextSchemeElement * textSchemeElement,
                            QWidget * parent = 0);
    ~TextSchemeElementDialog();

private:

    qreal rotateAngleFromUi();

    void load(TextSchemeElement * textSchemeElement);
    void save(TextSchemeElement * textSchemeElement);

private slots:

    void updatePixmap();

    void on_bgFrameType_buttonToggled(QAbstractButton * button, bool checked);
    void on_bgRotation_buttonToggled(QAbstractButton * button, bool checked);
    void on_buttonBox_accepted();

    void on_sbFontSize_valueChanged(int arg1);

private:

    Ui::TextSchemeElementDialog * ui;

    SettingsStorage * m_settingsStorage;
    TextSchemeElement * m_textSchemeElement;

};

#endif // TEXTSCHEMEELEMENTDIALOG_H
