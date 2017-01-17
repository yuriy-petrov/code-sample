#ifndef MODELSETTINGSWIDGETPRIVATE_H
#define MODELSETTINGSWIDGETPRIVATE_H

#include <QWidget>
#include <QAbstractButton>
#include <QObject>
#include <QItemSelection>

#include "noisevariancemodel.h"
#include "modelparametersmodel.h"

namespace Ui {
class ModelSettingsWidget;
}

class ModelSettingsWidgetPrivate : public QObject
{
    Q_OBJECT
    friend class ModelSettingsWidget;

public:
    explicit ModelSettingsWidgetPrivate(QWidget *parent = 0);
    virtual ~ModelSettingsWidgetPrivate();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonRemove_clicked();

    void on_tableViewNoiseSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected);

private:
    Ui::ModelSettingsWidget *ui;
    Model::NoiseVariance m_NoiseVariance;
    NoiseVarianceModel m_NoiseVarianceModel;
    Model::Parameters::Type m_ModelParameters;
    ModelParametersModel m_ModelParametersModel;
};

#endif // MODELSETTINGSWIDGETPRIVATE_H
