#ifndef SCHEMEELEMENTDIALOG_H
#define SCHEMEELEMENTDIALOG_H

class AbstractSchemeElement;

#include <QDialog>

namespace Ui
{
    class SchemeElementDialog;
}

class SchemeElementDialog : public QDialog
{

    Q_OBJECT

public:

    SchemeElementDialog(AbstractSchemeElement * schemeElement,
                        QWidget * parent = 0);
    ~SchemeElementDialog();

private slots:

    void on_buttonBox_accepted();

private:

    void load();
    void save();

private:

    Ui::SchemeElementDialog * ui;

    AbstractSchemeElement * m_schemeElement;

};

#endif // SCHEMEELEMENTDIALOG_H
