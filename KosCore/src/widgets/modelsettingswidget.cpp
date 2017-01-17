#include <log.h>
#include "modelsettingswidget.h"
#include "ui_modelsettingswidget.h"
#include "modelsettingswidgetprivate.h"
#include "StringsKeys.h"

ModelSettingsWidget::ModelSettingsWidget(bool isInterfaceEditable,
                                         QWidget *parent)
    : AbstractSettingsWidget(parent)
    , m_Private(new ModelSettingsWidgetPrivate(this))
{
}

ModelSettingsWidget::~ModelSettingsWidget()
{
}

bool ModelSettingsWidget::isSettingsValid()
{
    return true;
}

QString ModelSettingsWidget::settingsInvalidText()
{
    return QString();
}

void ModelSettingsWidget::settingsLoad()
{
    m_Private->m_NoiseVariance = Model::NoiseVariance::fromString(
                m_settingsStorage->value(SettingsKeys::MODEL_NOISE_VARIANCE).toString());
    m_Private->m_NoiseVarianceModel.setNoiseVariance(m_Private->m_NoiseVariance);

    m_Private->m_ModelParameters = Model::Parameters::Type::fromString(
                m_settingsStorage->value(SettingsKeys::MODEL_PARAMETERS).toString());
    m_Private->m_ModelParametersModel.setParameters(m_Private->m_ModelParameters);

    m_Private->ui->pushButtonAdd->setEnabled(!m_Private->m_NoiseVarianceModel.isFull());

    LOG << "LOAD:" << m_Private->m_NoiseVariance;
    LOG << "LOAD:" << m_Private->m_ModelParameters;
}

void ModelSettingsWidget::settingsSave()
{
    LOG << "SAVE:" << m_Private->m_NoiseVarianceModel.noiseVariance();
    m_settingsStorage->setValue(SettingsKeys::MODEL_NOISE_VARIANCE, m_Private->m_NoiseVarianceModel.noiseVariance().toString());

    LOG << "SAVE:" << m_Private->m_ModelParametersModel.parameters();
    m_settingsStorage->setValue(SettingsKeys::MODEL_PARAMETERS, m_Private->m_ModelParametersModel.parameters().toString());
}
