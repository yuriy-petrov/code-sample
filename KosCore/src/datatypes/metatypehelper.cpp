#include "metatypehelper.h"
#include "modeltypes.h"
#include "modelparameters.h"

MetaTypeHelper::MetaTypeHelper()
{
    qRegisterMetaType<Model::HwSwitchPos>();
    qRegisterMetaTypeStreamOperators<Model::HwSwitchPos>();

    qRegisterMetaType<Model::Valve>();
    qRegisterMetaTypeStreamOperators<Model::Valve>();

    qRegisterMetaType<Model::HystatMode::Type>();
    qRegisterMetaTypeStreamOperators<Model::HystatMode::Type>();

    qRegisterMetaType<Model::Pipe>();
    qRegisterMetaTypeStreamOperators<Model::Pipe>();

    qRegisterMetaType<Model::Separator>();
    qRegisterMetaTypeStreamOperators<Model::Separator>();

    qRegisterMetaType<Model::CoalescentFilter>();
    qRegisterMetaTypeStreamOperators<Model::CoalescentFilter>();

    qRegisterMetaType<Model::Rinser>();
    qRegisterMetaTypeStreamOperators<Model::Rinser>();

    qRegisterMetaType<Model::HeatExchanger>();
    qRegisterMetaTypeStreamOperators<Model::HeatExchanger>();

    qRegisterMetaType<Model::Parameters::Type>();
    qRegisterMetaTypeStreamOperators<Model::Parameters::Type>();
}
