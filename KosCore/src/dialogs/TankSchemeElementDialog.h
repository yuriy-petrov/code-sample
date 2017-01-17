#ifndef TANKSCHEMEELEMENTDIALOG_H
#define TANKSCHEMEELEMENTDIALOG_H

class TankSchemeElement;

#include "KosTypes.h"

#include <QDialog>

namespace Ui
{
    class TankSchemeElementDialog;
}

class TankSchemeElementDialog : public QDialog
{

    Q_OBJECT

public:

    TankSchemeElementDialog(TankSchemeElement * tankSchemeElement,
                            QWidget * parent = 0);
    ~TankSchemeElementDialog();

private slots:

    void on_buttonBox_accepted();

private slots:

    void updatePixmap();

private:

    void load(TankSchemeElement * tankSchemeElement);
    void save(TankSchemeElement * tankSchemeElement);

private:

    Ui::TankSchemeElementDialog * ui;

    TankSchemeElement * m_tankSchemeElement;

    QList<KosTypes::SubstanceType> m_substanceTypes;
    bool m_isConfigured;

};

#endif // TANKSCHEMEELEMENTDIALOG_H
