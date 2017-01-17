QT += core gui widgets network webkitwidgets svg multimedia

TARGET = KosCore
TEMPLATE = lib
CONFIG += plugin

ROOT_DIR = ../
include("../Kos.pri")

DESTDIR = $$LIB_DIR

LIBS += -lSystemUtils -ldatastorage

INCLUDEPATH = \
    src \
    src/providers \
    src/widgets \
    src/managers \
    src/dialogs \
    src/datatypes \
    src/models \
    src/private \
    src/scheme \
    src/scheme/elements \
    src/scheme/graphicsitems \
    src/export \
    src/delegates \
    src/CimrexUI \
    src/CimrexUI/base \
    src/CimrexUI/commands \
    src/CimrexUI/interfaces \
    src/CimrexUI/mustache \
    src/CimrexUI/controller \
    src/eventlogs \
    src/eventfilters \
    $$INCLUDEPATH

HEADERS += \
    src/widgets/AbstractSettingsWidget.h \
    src/widgets/ServerSettingsWidget.h \
    src/widgets/InterfaceSettingsWidget.h \
    src/providers/TransceiverProvider.h \
    src/managers/SettingsManager.h \
    src/managers/TranslationManager.h \
    src/dialogs/SettingsDialog.h \
    src/StringsKeys.h \
    src/ClientState.h \
    src/datatypes/Exercise.h \
    src/widgets/storagesettingswidget.h \
    src/scheme/SchemeElementContainer.h \
    src/scheme/SchemeItemContainer.h \
    src/scheme/AbstractSchemeItemContainer.h \
    src/scheme/SchemeScene.h \
    src/scheme/elements/BasicSchemeElement.h \
    src/scheme/graphicsitems/BasicSchemeItem.h \
    src/scheme/graphicsitems/CanvasSchemeItem.h \
    src/providers/SchemeDataProvider.h \
    src/dialogs/CanvasSchemePropertiesDialog.h \
    src/dialogs/BasicSchemeElementDialog.h \
    src/scheme/AbstractSchemeElementContainer.h \
    src/chartscolors.h \
    src/scheme/elements/PipelineSchemeElement.h \
    src/scheme/graphicsitems/PipelineSchemeItem.h \
    src/dialogs/SchemeElementDialog.h \
    src/scheme/elements/CanvasSchemeElement.h \
    src/widgets/chartssettingswidget.h \
    src/private/chartssettingswidgetprivate.h \
    src/models/chartssettingsmodel.h \
    src/scheme/elements/AbstractSchemeElement.h \
    src/dialogs/PipelineSchemeElementDialog.h \
    src/scheme/elements/ValveSchemeElement.h \
    src/datatypes/KosTypes.h \
    src/dialogs/ValveSchemeElementDialog.h \
    src/datatypes/KosTypesHelper.h \
    src/scheme/graphicsitems/ValveSchemeItem.h \
    src/datatypes/KosUtils.h \
    src/widgets/SchemeView.h \
    src/dialogs/ExerciseEditorDialog.h \
    src/models/snapshottablemodel.h \
    src/models/conditionsmodel.h \
    src/SchemeKeys.h \
    src/noisevariance.h \
    src/widgets/modelsettingswidget.h \
    src/private/modelsettingswidgetprivate.h \
    src/models/noisevariancemodel.h \
    src/delegates/comboboxitemdelegate.h \
    src/modeltypes.h \
    src/datatypes/valve.h \
    src/CimrexUI/base/Action.h \
    src/CimrexUI/base/ConfigReader.h \
    src/CimrexUI/base/ContextHandler.h \
    src/CimrexUI/base/HTMLTemplate.h \
    src/CimrexUI/base/Page.h \
    src/CimrexUI/commands/DecrementCommand.h \
    src/CimrexUI/commands/GoBackCommand.h \
    src/CimrexUI/commands/GoDefaultCommand.h \
    src/CimrexUI/commands/GoToCommand.h \
    src/CimrexUI/commands/IncrementCommand.h \
    src/CimrexUI/interfaces/ICommand.h \
    src/CimrexUI/interfaces/IContextCommand.h \
    src/CimrexUI/mustache/mustache.h \
    src/CimrexUI/ControllerWidget.h \
    src/CimrexUI/LEDWidget.h \
    src/CimrexUI/controller/CimrexModelBinding.h \
    src/scheme/graphicsitems/TextSchemeItem.h \
    src/dialogs/TextSchemeElementDialog.h \
    src/scheme/elements/TankSchemeElement.h \
    src/scheme/graphicsitems/TankSchemeItem.h \
    src/dialogs/TankSchemeElementDialog.h \
    src/schemesnapshotcontroller.h \
    src/private/schemesnapshotcontrollerprivate.h \
    src/models/snapshotvalvesmodel.h \
    src/scheme/elements/TextSchemeElement.h \
    src/datatypes/metatypehelper.h \
    src/CimrexUI/commands/SendCommand.h \
    src/CimrexUI/base/ICimrexButton.h \
    src/ChartsUnits.h \
    src/datatypes/SnapshotKeyHash.h \
    src/models/chartsunitsmodel.h \
    src/datatypes/ChartsUnit.h \
    src/datatypes/ChartsUnitsLinker.h \
    src/widgets/ValvesSettingsWidget.h \
    src/datatypes/pipe.h \
    src/datatypes/separator.h \
    src/eventlogs/SchemeEventLogElement.h \
    src/widgets/SchemeSettingsWidget.h \
    src/scheme/elements/LevelSchemeElement.h \
    src/dialogs/LevelSchemeElementDialog.h \
    src/scheme/graphicsitems/LevelSchemeItem.h \
    src/scheme/graphicsitems/AbstractSchemeItem.h \
    src/managers/SchemeSceneManager.h \
    src/scheme/SchemeItemHelper.h \
    src/eventlogs/CimrexLogElement.h \
    src/models/abstractsnapshotsubstancemodel.h \
    src/models/snapshotpipesmodel.h \
    src/models/snapshotrinsersmodel.h \
    src/models/snapshotcoalescentfiltersmodel.h \
    src/models/snapshotheatexchangersmodel.h \
    src/models/snapshotseparatorsmodel.h \
    src/datatypes/ModelTypesExtractor.h \
    src/datatypes/modelparameters.h \
    src/models/modelparametersmodel.h \
    src/widgets/ItemContainersWidget.h \
    src/datatypes/stage.h \
    src/widgets/ElementsMoveWidget.h \
    src/managers/GroupSchemeSceneManager.h \
    src/widgets/GroupSchemeView.h \
    src/widgets/playersettingswidget.h \
    src/private/playersettingswidgetprivate.h \
    src/datatypes/stages.h \
    src/models/stagesmodel.h \
    src/delegates/directoryselectordelegate.h \
    src/widgets/clockindicatorwidget.h \
    src/private/clockindicatorprivate.h \
    src/widgets/powerroomwidget.h \
    src/private/powerroomwidgetprivate.h \
    src/widgets/equipmentroomwidget.h \
    src/private/equipmentroomwidgetprivate.h \
    src/widgets/abstractvalvewidget.h \
    src/widgets/handvalvewidget.h \
    src/widgets/ballvalvewidget.h \
    src/widgets/manometerwidget.h \
    src/private/manometerwidgetprivate.h \
    src/widgets/powerswitchwidget.h \
    src/CimrexUI/commands/LineUpCommand.h \
    src/CimrexUI/commands/LineDownCommand.h \
    src/eventfilters/AbstractEventFilter.h \
    src/eventlogs/AbstractEventLogElement.h \
    src/eventfilters/BlockEventFilter.h \
    src/eventfilters/StageEventFilter.h \
    src/eventfilters/EventFilterProvider.h \
    src/eventfilters/SchemeEventFilter.h \
    src/widgets/AbstractEventFilterWidget.h \
    src/widgets/SchemeEventFilterWidget.h \
    src/widgets/EventFilterProviderWidget.h \
    src/models/eventfiltermodel.h \
    src/models/blockeventfiltermodel.h \
    src/models/stageeventfiltermodel.h \
    src/dialogs/EventFilterDialog.h \
    src/eventlogs/modeleventlogelement.h \
    src/eventlogs/modeleventloghelper.h \
    src/models/cellstackenablemodel.h \
    src/providers/EventLogAnalyzer.h \
    src/providers/EventLogProvider.h \
    src/eventlogs/CommentEventLogElement.h \
    src/widgets/hystatmodeeventfilterwidget.h \
    src/datatypes/modeltypeshelper.h \
    src/widgets/modeleventfilterwidget.h \
    src/eventfilters/modeleventfilter.h \
    src/widgets/powersweventfilterwidget.h \
    src/widgets/CimrexEventFilterWidget.h \
    src/eventfilters/CimrexEventFilter.h \
    src/delegates/multilinedelegate.h \
    src/widgets/cellstackeventfilterwidget.h \
    src/CimrexUI/commands/InvertCommand.h \
    src/widgets/PixmapWidget.h \
    src/eventfilters/SnapshotCondition.h \
    src/models/SnapshotConditionModel.h \
    src/CimrexUI/controller/buttoneventfilter.h \
    src/widgets/hwswitcheventfilterwidget.h \
    src/delegates/modelvaluesdelegate.h \
    src/CimrexUI/commands/EnableAll.h \
    src/CimrexUI/commands/DisableAll.h \
    src/providers/alarmcontroller.h \
    src/widgets/soundsettingswidget.h \
    src/private/soundsettingswidgetprivate.h \
    src/providers/TroubleListController.h \
    src/datatypes/Trouble.h \
    src/widgets/TroubleListWidget.h \
    src/models/TroubleListModel.h \
    src/widgets/TroubleListSettingsWidget.h \
    src/widgets/AlignmentWidget.h

SOURCES += \
    src/widgets/AbstractSettingsWidget.cpp \
    src/widgets/ServerSettingsWidget.cpp \
    src/widgets/InterfaceSettingsWidget.cpp \
    src/providers/TransceiverProvider.cpp \
    src/managers/SettingsManager.cpp \
    src/dialogs/SettingsDialog.cpp \
    src/managers/TranslationManager.cpp \
    src/ClientState.cpp \
    src/datatypes/Exercise.cpp \
    src/widgets/storagesettingswidget.cpp \
    src/scheme/SchemeScene.cpp \
    src/scheme/elements/BasicSchemeElement.cpp \
    src/scheme/graphicsitems/BasicSchemeItem.cpp \
    src/scheme/graphicsitems/CanvasSchemeItem.cpp \
    src/providers/SchemeDataProvider.cpp \
    src/dialogs/CanvasSchemePropertiesDialog.cpp \
    src/dialogs/BasicSchemeElementDialog.cpp \
    src/scheme/AbstractSchemeElementContainer.cpp \
    src/scheme/AbstractSchemeItemContainer.cpp \
    src/chartscolors.cpp \
    src/scheme/elements/PipelineSchemeElement.cpp \
    src/scheme/graphicsitems/PipelineSchemeItem.cpp \
    src/scheme/elements/AbstractSchemeElement.cpp \
    src/dialogs/SchemeElementDialog.cpp \
    src/scheme/elements/CanvasSchemeElement.cpp \
    src/widgets/chartssettingswidget.cpp \
    src/private/chartssettingswidgetprivate.cpp \
    src/models/chartssettingsmodel.cpp \
    src/dialogs/PipelineSchemeElementDialog.cpp \
    src/scheme/elements/ValveSchemeElement.cpp \
    src/dialogs/ValveSchemeElementDialog.cpp \
    src/datatypes/KosTypesHelper.cpp \
    src/scheme/graphicsitems/ValveSchemeItem.cpp \
    src/datatypes/KosUtils.cpp \
    src/widgets/SchemeView.cpp \
    src/dialogs/ExerciseEditorDialog.cpp \
    src/models/snapshottablemodel.cpp \
    src/models/conditionsmodel.cpp \
    src/noisevariance.cpp \
    src/widgets/modelsettingswidget.cpp \
    src/private/modelsettingswidgetprivate.cpp \
    src/models/noisevariancemodel.cpp \
    src/delegates/comboboxitemdelegate.cpp \
    src/CimrexUI/base/Action.cpp \
    src/CimrexUI/base/ConfigReader.cpp \
    src/CimrexUI/base/ContextHandler.cpp \
    src/CimrexUI/base/HTMLTemplate.cpp \
    src/CimrexUI/base/Page.cpp \
    src/CimrexUI/commands/DecrementCommand.cpp \
    src/CimrexUI/commands/GoBackCommand.cpp \
    src/CimrexUI/commands/GoDefaultCommand.cpp \
    src/CimrexUI/commands/GoToCommand.cpp \
    src/CimrexUI/commands/IncrementCommand.cpp \
    src/CimrexUI/interfaces/ICommand.cpp \
    src/CimrexUI/interfaces/IContextCommand.cpp \
    src/CimrexUI/mustache/mustache.cpp \
    src/CimrexUI/ControllerWidget.cpp \
    src/CimrexUI/LEDWidget.cpp \
    src/CimrexUI/controller/CimrexModelBinding.cpp \
    src/scheme/graphicsitems/TextSchemeItem.cpp \
    src/dialogs/TextSchemeElementDialog.cpp \
    src/scheme/elements/TankSchemeElement.cpp \
    src/scheme/graphicsitems/TankSchemeItem.cpp \
    src/dialogs/TankSchemeElementDialog.cpp \
    src/schemesnapshotcontroller.cpp \
    src/private/schemesnapshotcontrollerprivate.cpp \
    src/models/snapshotvalvesmodel.cpp \
    src/scheme/elements/TextSchemeElement.cpp \
    src/datatypes/metatypehelper.cpp \
    src/CimrexUI/commands/SendCommand.cpp \
    src/CimrexUI/base/ICimrexButton.cpp \
    src/ChartsUnits.cpp \
    src/models/chartsunitsmodel.cpp \
    src/datatypes/ChartsUnitsLinker.cpp \
    src/widgets/ValvesSettingsWidget.cpp \
    src/datatypes/pipe.cpp \
    src/datatypes/separator.cpp \
    src/widgets/SchemeSettingsWidget.cpp \
    src/eventlogs/SchemeEventLogElement.cpp \
    src/scheme/elements/LevelSchemeElement.cpp \
    src/dialogs/LevelSchemeElementDialog.cpp \
    src/scheme/graphicsitems/LevelSchemeItem.cpp \
    src/scheme/graphicsitems/AbstractSchemeItem.cpp \
    src/managers/SchemeSceneManager.cpp \
    src/scheme/SchemeItemHelper.cpp \
    src/eventlogs/CimrexLogElement.cpp \
    src/models/abstractsnapshotsubstancemodel.cpp \
    src/models/snapshotpipesmodel.cpp \
    src/models/snapshotrinsersmodel.cpp \
    src/models/snapshotcoalescentfiltersmodel.cpp \
    src/models/snapshotheatexchangersmodel.cpp \
    src/models/snapshotseparatorsmodel.cpp \
    src/datatypes/modelparameters.cpp \
    src/models/modelparametersmodel.cpp \
    src/widgets/ItemContainersWidget.cpp \
    src/datatypes/stage.cpp \
    src/widgets/ElementsMoveWidget.cpp \
    src/managers/GroupSchemeSceneManager.cpp \
    src/widgets/GroupSchemeView.cpp \
    src/widgets/playersettingswidget.cpp \
    src/private/playersettingswidgetprivate.cpp \
    src/datatypes/stages.cpp \
    src/models/stagesmodel.cpp \
    src/delegates/directoryselectordelegate.cpp \
    src/widgets/clockindicatorwidget.cpp \
    src/private/clockindicatorprivate.cpp \
    src/widgets/powerroomwidget.cpp \
    src/private/powerroomwidgetprivate.cpp \
    src/widgets/equipmentroomwidget.cpp \
    src/private/equipmentroomwidgetprivate.cpp \
    src/widgets/abstractvalvewidget.cpp \
    src/widgets/handvalvewidget.cpp \
    src/widgets/ballvalvewidget.cpp \
    src/widgets/manometerwidget.cpp \
    src/private/manometerwidgetprivate.cpp \
    src/widgets/powerswitchwidget.cpp \
    src/CimrexUI/commands/LineUpCommand.cpp \
    src/CimrexUI/commands/LineDownCommand.cpp \
    src/eventfilters/AbstractEventFilter.cpp \
    src/eventlogs/AbstractEventLogElement.cpp \
    src/eventfilters/BlockEventFilter.cpp \
    src/eventfilters/StageEventFilter.cpp \
    src/eventfilters/EventFilterProvider.cpp \
    src/eventfilters/SchemeEventFilter.cpp \
    src/widgets/AbstractEventFilterWidget.cpp \
    src/widgets/SchemeEventFilterWidget.cpp \
    src/widgets/EventFilterProviderWidget.cpp \
    src/models/eventfiltermodel.cpp \
    src/models/blockeventfiltermodel.cpp \
    src/models/stageeventfiltermodel.cpp \
    src/dialogs/EventFilterDialog.cpp \
    src/eventlogs/modeleventlogelement.cpp \
    src/eventlogs/modeleventloghelper.cpp \
    src/models/cellstackenablemodel.cpp \
    src/providers/EventLogAnalyzer.cpp \
    src/providers/EventLogProvider.cpp \
    src/eventlogs/CommentEventLogElement.cpp \
    src/widgets/hystatmodeeventfilterwidget.cpp \
    src/datatypes/modeltypeshelper.cpp \
    src/widgets/modeleventfilterwidget.cpp \
    src/eventfilters/modeleventfilter.cpp \
    src/widgets/powersweventfilterwidget.cpp \
    src/widgets/CimrexEventFilterWidget.cpp \
    src/eventfilters/CimrexEventFilter.cpp \
    src/delegates/multilinedelegate.cpp \
    src/widgets/cellstackeventfilterwidget.cpp \
    src/CimrexUI/commands/InvertCommand.cpp \
    src/widgets/PixmapWidget.cpp \
    src/eventfilters/SnapshotCondition.cpp \
    src/models/SnapshotConditionModel.cpp \
    src/CimrexUI/controller/buttoneventfilter.cpp \
    src/widgets/hwswitcheventfilterwidget.cpp \
    src/delegates/modelvaluesdelegate.cpp \
    src/CimrexUI/commands/EnableAll.cpp \
    src/CimrexUI/commands/DisableAll.cpp \
    src/providers/alarmcontroller.cpp \
    src/widgets/soundsettingswidget.cpp \
    src/private/soundsettingswidgetprivate.cpp \
    src/providers/TroubleListController.cpp \
    src/datatypes/Trouble.cpp \
    src/widgets/TroubleListWidget.cpp \
    src/models/TroubleListModel.cpp \
    src/widgets/TroubleListSettingsWidget.cpp \
    src/widgets/AlignmentWidget.cpp

FORMS += \
    src/widgets/ServerSettingsWidget.ui \
    src/widgets/InterfaceSettingsWidget.ui \
    src/dialogs/SettingsDialog.ui \
    src/widgets/storagesettingswidget.ui \
    src/dialogs/CanvasSchemePropertiesDialog.ui \
    src/dialogs/BasicSchemeElementDialog.ui \
    src/dialogs/SchemeElementDialog.ui \
    src/widgets/chartssettingswidget.ui \
    src/dialogs/PipelineSchemeElementDialog.ui \
    src/dialogs/ValveSchemeElementDialog.ui \
    src/dialogs/ExerciseEditorDialog.ui \
    src/widgets/modelsettingswidget.ui \
    src/CimrexUI/ui/ControllerWidget.ui \
    src/dialogs/TextSchemeElementDialog.ui \
    src/dialogs/TankSchemeElementDialog.ui \
    src/widgets/ValvesSettingsWidget.ui \
    src/widgets/SchemeSettingsWidget.ui \
    src/dialogs/LevelSchemeElementDialog.ui \
    src/widgets/ItemContainersWidget.ui \
    src/widgets/playersettingswidget.ui \
    src/widgets/clockindicatorwidget.ui \
    src/widgets/powerroomwidget.ui \
    src/widgets/equipmentroomwidget.ui \
    src/widgets/abstractvalvewidget.ui \
    src/widgets/manometerwidget.ui \
    src/widgets/SchemeEventFilterWidget.ui \
    src/widgets/EventFilterProviderWidget.ui \
    src/dialogs/EventFilterDialog.ui \
    src/widgets/hystatmodeeventfilterwidget.ui \
    src/widgets/modeleventfilterwidget.ui \
    src/widgets/powersweventfilterwidget.ui \
    src/widgets/CimrexEventFilterWidget.ui \
    src/widgets/cellstackeventfilterwidget.ui \
    src/widgets/hwswitcheventfilterwidget.ui \
    src/widgets/soundsettingswidget.ui \
    src/widgets/TroubleListWidget.ui \
    src/widgets/TroubleListSettingsWidget.ui \
    src/widgets/AlignmentWidget.ui

TRANSLATIONS = $$TARGET"_ru.ts"

headers.path = $$INCLUDE_DIR
headers.files = \
    src/*.h \
    src/providers/*.h \
    src/widgets/*.h \
    src/managers/*.h \
    src/dialogs/*.h \
    src/datatypes/*.h \
    src/scheme/elements/*.h \
    src/scheme/*.h \
    src/scheme/graphicsitems/*.h \
    src/CimrexUI/base/*.h \
    src/CimrexUI/commands/*.h \
    src/CimrexUI/interfaces/*.h \
    src/CimrexUI/mustache/*.h \
    src/CimrexUI/controller/*.h \
    src/CimrexUI/*.h \
    src/eventlogs/*.h \
    src/eventfilters/*.h

INSTALLS += headers

RESOURCES += \
    src/CimrexUI/resources/CimtexResources.qrc

OTHER_FILES += \
    src/CimrexUI/resources/images/up_led.png \
    src/CimrexUI/resources/templates/setpoints/setpoint.html \
    src/CimrexUI/resources/templates/basic/basic.html \
    src/CimrexUI/resources/images/up_led_red.png \
    src/CimrexUI/resources/images/f_led_default.png
