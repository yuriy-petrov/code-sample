#ifndef LEVELSCHEMEELEMENTDIALOG_H
#define LEVELSCHEMEELEMENTDIALOG_H

class LevelSchemeElement;
class CanvasSchemeElement;

#include "KosTypes.h"

#include <QDialog>

namespace Ui
{
    class LevelSchemeElementDialog;
}

class LevelSchemeElementDialog : public QDialog
{

    Q_OBJECT

public:

    LevelSchemeElementDialog(CanvasSchemeElement * canvasSchemeElement,
                             LevelSchemeElement * levelSchemeElement,
                             QWidget *parent = 0);
    ~LevelSchemeElementDialog();

private slots:

    void updatePixmap();

    void on_buttonBox_accepted();

private:

    void load(LevelSchemeElement * levelSchemeElement);
    void save(LevelSchemeElement * levelSchemeElement);

private:

    Ui::LevelSchemeElementDialog * ui;

    CanvasSchemeElement * m_canvasSchemeElement;
    LevelSchemeElement * m_levelSchemeElement;

    QList<KosTypes::LevelElementType> m_levelElementTypes;
    QList<KosTypes::SubstanceType> m_substanceTypes;

    bool m_isConfigured;

};

#endif // LEVELSCHEMEELEMENTDIALOG_H
