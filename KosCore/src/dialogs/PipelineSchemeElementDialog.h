#ifndef PIPELINESCHEMEELEMENTDIALOG_H
#define PIPELINESCHEMEELEMENTDIALOG_H

class PipelineSchemeElement;

#include "KosTypes.h"

#include <QDialog>

namespace Ui
{
    class PipelineSchemeElementDialog;
}

class PipelineSchemeElementDialog : public QDialog
{

    Q_OBJECT

public:

    PipelineSchemeElementDialog(PipelineSchemeElement * pipelineSchemeElement,
                                QWidget * parent = 0);
    ~PipelineSchemeElementDialog();

private slots:
    void on_buttonBox_accepted();

private:

    void load();
    void save();

private:

    Ui::PipelineSchemeElementDialog * ui;

    PipelineSchemeElement * m_pipelineSchemeElement;

    QList<KosTypes::PipelineState> m_pipelineStates;
    QList<KosTypes::SubstanceType> m_substanceTypes;

};

#endif // PIPELINESCHEMEELEMENTDIALOG_H
