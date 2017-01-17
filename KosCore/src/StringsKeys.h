#ifndef STRINGSKEYS_H
#define STRINGSKEYS_H

#include <QStringList>

namespace SettingsKeys
{
    static const QString LANGUAGE = "LANGUAGE";
    static const QString LANGUAGE_DEFAULT = "en";

    static const QString SCHEME_EXTENSION = "sch";
    static const QString EXERCISE_EXTENSION = "exc";

    static const QString SERVER_ADDRESS = "SERVER_ADDRESS";
    static const QString SERVER_PORT = "SERVER_PORT";

    static const QString STORAGE_ROOT = "STORAGE_ROOT";
    static const QString EXERCISES_ROOT = "EXERCISES_ROOT";

    static const QString SCHEME_DEFAULT_SIZE = "SCHEME_DEFAULT_SIZE";
    static const QString SCHEME_DEFAULT_GRID_STEP = "SCHEME_DEFAULT_GRID_STEP";

    static const QString SCHEME_FILES = "SCHEME_FILES";

    static const QString SCHEME_PIPELINE_HIGHLIGHT_WIDTH_DELTA = "SCHEME_PIPELINE_HIGHLIGHT_WIDTH_DELTA";

    static const QString SCHEME_PIPELINE_POINT_SIZE = "SCHEME_PIPELINE_POINT_SIZE";
    static const QString SCHEME_PIPELINE_POINT_HIGHLIGHT_SIZE = "SCHEME_PIPELINE_POINT_HIGHLIGHT_SIZE";

    static const QString OXYGEN_COLOR = "OXYGEN_COLOR";
    static const QString HYDROGEN_COLOR = "HYDROGEN_COLOR";
    static const QString ELECTROLYTE_COLOR = "ELECTROLYTE_COLOR";

    static const QString CHARTS_COLORS = "CHARTS_COLORS";
    static const QString CHARTS_UNITS = "CHARTS_UNITS";
    static const QString CHARTS_UNITS_LINKS = "CHARTS_UNITS_LINKS";

    static const QString MODEL_NOISE_VARIANCE = "MODEL_NOISE_VARIANCE";
    static const QString CLIENT_INTERACTIVE_VALVE_LIST = "CLIENT_INTERACTIVE_VALVE_LIST";
    static const QString MODEL_PARAMETERS = "MODEL_PARAMETERS";

    static const QString SCHEME_FONT_FAMILY = "SCHEME_FONT_FAMILY";
    static const QString SCHEME_FONT_SIZE = "SCHEME_FONT_SIZE";

    static const QString TRANSLATION_DIR = "TRANSLATION_DIR";

    static const QString PLAYER_STAGES_DIR = "PLAYER_STAGES_DIR";
    static const QString PLAYER_STAGES = "PLAYER_STAGES";

    static const QString ALARM_SOUND = "ALARM_SOUND";
    static const QString ALARM_SOUND_VOLUME = "ALARM_SOUND_VOLUME";

    static const QString TROUBLE_LIST = "TROUBLE_LIST";
}

namespace Commands
{
    static const QString COMMAND = "COMMAND";

    static const QString C2S_AUTHORIZE = "C2S_AUTHORIZE";
    static const QString S2C_AUTHORIZE_SUCCESS = "S2C_AUTHORIZE_SUCCESS";
    static const QString S2C_AUTHORIZE_FAIL = "S2C_AUTHORIZE_FAIL";

    static const QString C2S_UNAUTHORIZE = "C2S_UNAUTHORIZE";
    static const QString S2C_UNAUTHORIZE_SUCCESS = "S2C_UNAUTHORIZE_SUCCESS";

    static const QString S2C_EXERCISE_START = "S2C_EXERCISE_START";
    static const QString C2S_EXERCISE_STARTED = "C2S_EXERCISE_STARTED";

    static const QString S2C_EXERCISE_STOP = "S2C_EXERCISE_STOP";
    static const QString C2S_EXERCISE_STOPPED = "C2S_EXERCISE_STOPPED";

    static const QString C2S_SIMULATION = "C2S_SIMULATION";

    static const QString C2S_EVENT_LOG = "C2S_EVENT_LOG";

    static const QString S2C_EXERCISE_SUCCESSFULLY_FINISHED = "S2C_EXERCISE_SUCCESSFULLY_FINISHED";
    static const QString S2C_EXERCISE_UNSUCCESSFULLY_FINISHED = "S2C_EXERCISE_UNSUCCESSFULLY_FINISHED";

    static const QString S2C_TROUBLES_SET = "S2C_TROUBLES_SET";
    static const QString C2S_TROUBLES_SET = "C2S_TROUBLES_SET";

    namespace Args
    {
        static const QString C2S_USER_NAME = "C2S_USER_NAME";
        static const QString S2C_USER_NAME = "S2C_USER_NAME";
        static const QString S2C_SCHEMES = "S2C_SCHEMES";
        static const QString S2C_TROUBLE_LIST = "S2C_TROUBLE_LIST";
        static const QString S2C_EXERCISE = "S2C_EXERCISE";
        static const QString S2C_INTERACTIVE_VALVES = "S2C_INTERACTIVE_VALVES";
        static const QString C2S_SIMULATION_DATA = "C2S_SIMULATION_DATA";
        static const QString S2C_MODEL_NOISE = "S2C_MODEL_NOISE";
        static const QString C2S_EVENT_LOG_ELEMENT = "C2S_EVENT_LOG_ELEMENT";
        static const QString S2C_MODEL_PARAMETERS = "S2C_MODEL_PARAMETERS";
        static const QString S2C_EXERCISE_ERROR = "S2C_EXERCISE_ERROR";
        static const QString S2C_TROUBLES_ACTIVE = "S2C_TROUBLES";
        static const QString C2S_TROUBLES_ACTIVE = "C2S_TROUBLES";
    }
}

namespace Model
{
    static const QString HYSTAT_Mode = "Mode"; // Режим работы

    static const QString HW_SWITCH = "HW_SWITCH"; // Положение ключа

    static const QString EMERGENCY_BUTTON = "EMERGENCY_BUTTON"; // Кнопка экстренного отключения
    static const QString RESET_BUTTON = "RESET_BUTTON"; // Кнопка сброса

    static const QString DEPRESSURISATION_REQUEST = "DEPRESSURISATION_REQUEST";

    static const QString ALARM = "ALARM";

    namespace Power
    {
        static const QString Switch = "POWER_SW"; // положение рубильника
    }

    namespace ChartsValues // double
    {
        static const QString PTCLC = "PTCLC";
        static const QString TTCLC = "TTCLC";
        static const QString UPS = "UPS";
        static const QString OTA = "OTA";

        static const QString PTGS = "PTGS";

        static const QString PTGS_H = "PTGS_H";
        static const QString PTGS_O = "PTGS_O";

        static const QString LTH = "LTH";
        static const QString LTO = "LTO";

        static const QString ITCS1 = "ITCS1";
        static const QString CellVoltCS1 = "CellVoltCS1";
        static const QString UTCS1a = "UTCS1a";
        static const QString UTCS1b = "UTCS1b";
        static const QString TTCS1 = "TTCS1";

        static const QString ITCS2 = "ITCS2";
        static const QString CellVoltCS2 = "CellVoltCS2";
        static const QString UTCS2a = "UTCS2a";
        static const QString UTCS2b = "UTCS2b";
        static const QString TTCS2 = "TTCS2";

        static const QString HTO = "HTO";
        static const QString OTH = "OTH";

        static const QString Tot_Prod = "Tot_Prod";
        static const QString Tot_Prod_Avg_LastSec = "Tot_Prod_Avg_LastSec";

        static const QString PTU_H = "PTU_H";
        static const QString CT = "CT";

        static QStringList keys()
        {
            return QStringList()
                    << PTCLC
                    << TTCLC
                    << UPS
                    << OTA
                    << PTGS
                    << LTH
                    << LTO
                    << ITCS1
                    << CellVoltCS1
                    << UTCS1a
                    << UTCS1b
                    << TTCS1
                    << ITCS2
                    << CellVoltCS2
                    << UTCS2a
                    << UTCS2b
                    << TTCS2
                    << HTO
                    << OTH
                    << Tot_Prod
                    << Tot_Prod_Avg_LastSec
                    << PTU_H
                    << CT
                    ;
        }
    } // namespace ChartsValues

    namespace Purge {
        static const QString N2_PRESSURE = "N2_PRESSURE";
        static const QString REMAINING_TIME = "PURGE_REMAINING_TIME";
    } // namespace Purge

    namespace CellStack
    {
        namespace Enable // bool
        {
            static const QString CS1 = "CS1_ENABLE";
            static const QString CS2 = "CS2_ENABLE";
            static const QString CS3 = "CS3_ENABLE";
            static const QString CS4 = "CS4_ENABLE";

            static QStringList keys()
            {
                return QStringList()
                        << CS1
                        << CS2
                        << CS3
                        << CS4
                           ;
            }
        } // namespace Enable
    } // namespace CellStack

    namespace Pipes {
        static const QString VENT_STACK_H = "VENT_STACK_H";
        static const QString VENT_STACK_O = "VENT_STACK_O";
        static const QString MV_H_U_RCV = "MVH_U_to_RCV";
        static const QString RC_H_CF_H = "RC_H_to_CF_H";
        static const QString GAS_SEP_O_CF_O = "GAS_SEP_O_to_CF_O";
        static const QString CS1_to_GAS_SEP_H = "CS1_GAS_to_SEP_H";
        static const QString CS1_to_GAS_SEP_O = "CS1_GAS_to_SEP_O";
        static const QString CS2_to_GAS_SEP_H = "CS2_GAS_to_SEP_H";
        static const QString CS2_to_GAS_SEP_O = "CS2_GAS_to_SEP_O";
        static const QString GAS_SEP_H_CS = "GAS_SEP_H_to_CS";
        static const QString GAS_SEP_O_CS = "GAS_SEP_O_to_CS";
        static const QString RCV_N_BV_N1 = "RCV_N_to_BV_N1";
        static const QString BV_N1_MV_N2 = "BV_N1_to_MV_N2";
        static const QString MV_N2_HV_N = "MV_N2_to_HV_N";
        static const QString HV_N_GAS_SEP = "HV_N_to_GAS_SEP";

        static QStringList keys()
        {
            return QStringList()
                    << VENT_STACK_H
                    << VENT_STACK_O
                    << MV_H_U_RCV
                    << RC_H_CF_H
                    << GAS_SEP_O_CF_O
                    << CS1_to_GAS_SEP_H
                    << CS1_to_GAS_SEP_O
                    << CS2_to_GAS_SEP_H
                    << CS2_to_GAS_SEP_O
                    << GAS_SEP_H_CS
                    << GAS_SEP_O_CS
                    << RCV_N_BV_N1
                    << BV_N1_MV_N2
                    << MV_N2_HV_N
                    << HV_N_GAS_SEP
                    ;
        }
    } // namespace Pipes

    namespace Valves {
        static const QString MV1aO_A = "MV1aO_A";
        static const QString MV1bO_A = "MV1bO_A";
        static const QString MV1H_A = "MV1H_A";
        static const QString MV1aH_U = "MV1aH_U";
        static const QString MV1bH_U = "MV1bH_U";
        static const QString BV_N1 = "BV_N1";
        static const QString MV_N2 = "MV_N2";
        static const QString BV_N3 = "BV_N3";
        static const QString HV_N = "HV_N";
        // Receivers
        static const QString Dr_1H = "Dr_1H";
        static const QString Dr_2H = "Dr_2H";
        static const QString Dr_3H = "Dr_3H";
        static const QString Dr_4H = "Dr_4H";
        static const QString Dr_5H = "Dr_5H";
        static const QString Dr_6H = "Dr_6H";
        static const QString Dr_7H = "Dr_7H";
        static const QString Dr_8H = "Dr_8H";
        static const QString Dr_9H = "Dr_9H";
        static const QString Dr_10H = "Dr_10H";
        static const QString V26 = "V26";
        static const QString Dr_13H_R = "Dr_13H_R";
        static const QString V23_R = "V23_R";
        static const QString V2D_R = "V2D_R";
        static const QString OK_1H_R = "OK_1H_R";
        static const QString Dr_17H_R = "Dr_17H_R";
        static const QString V25_R = "V25_R";
        static const QString V21_A_1_R = "V21_A_1_R";
        static const QString V21_A_2_R = "V21_A_2_R";
        static const QString V26_R = "V26_R";
        static const QString V24_R = "V24_R";
        static const QString V1D_R = "V1D_R";
        static const QString OK_2H_R = "OK_2H_R";
        static const QString Dr_16H_R = "Dr_16H_R";
        static const QString V32A = "V32A";
        static const QString OP_H1 = "OP_H1";
        static const QString V20 = "V20";
        static const QString V19 = "V19";
        static const QString V22_R = "V22_R";
        static const QString V32 = "V32";
        static const QString V28 = "V28";
        static const QString V30 = "V30";
        static const QString Dr_4AZ = "Dr_4AZ";
        static const QString Dr_3AZ = "Dr_3AZ";
        static const QString Dr_2AZ = "Dr_2AZ";
        static const QString Dr_1AZ = "Dr_1AZ";
        static const QString V4AZ = "V4AZ";
        static const QString V3AZ = "V3AZ";
        static const QString V2AZ = "V2AZ";
        static const QString V1AZ = "V1AZ";
        static const QString V27 = "V27";
        static const QString V29 = "V29";
        static const QString V25 = "V25";
        static const QString V31A = "V31A";
        static const QString Dr_12H_R = "Dr_12H_R";
        static const QString OP_H2 = "OP_H2";
        static const QString V31 = "V31";
        static const QString M7_H = "M7_H";
        static const QString V108 = "V108";
        static const QString V109 = "V109";
        static const QString V110AZ = "V110AZ";
        static const QString V112AZ = "V112AZ";
        static const QString Dr_5AZ = "Dr_5AZ";
        static const QString OP_41 = "OP_41";
        static const QString V41 = "V41";
        static const QString V44 = "V44";
        static const QString V45P = "V45P";
        static const QString OP_40 = "OP_40";
        static const QString V40 = "V40";
        static const QString V42 = "V42";
        static const QString Dr_11H = "Dr_11H";
        static const QString V43 = "V43";
        static const QString V7AZ_R = "V7AZ_R";
        static const QString V8_AZ_R = "V8_AZ_R";
        static const QString Dr_7AZ_R = "Dr_7AZ_R";
        static const QString OK1_AZ_R = "OK1_AZ_R";
        static const QString Dr_8A3_R = "Dr_8A3_R";
        static const QString V9_AZ_R = "V9_AZ_R";
        static const QString V11_AZ_R = "V11_AZ_R";
        static const QString V12_AZ_R = "V12_AZ_R";
        static const QString V10_AZ_R = "V10_AZ_R";
        static const QString V5AZ = "V5AZ";
        static const QString V6AZ = "V6AZ";
        static const QString Dr_AZ = "Dr_AZ";
        static const QString OK1_AZ = "OK1_AZ";
        static const QString V117AZ = "V117AZ";
        static const QString V118AZ = "V118AZ";
        static const QString Dr_6AZ = "Dr_6AZ";
        static const QString V119AZ = "V119AZ";
        static const QString OK_AZ = "OK_AZ";
        static const QString V107_AZ = "V107_AZ";
        static const QString V106_AZ = "V106_AZ";
        static const QString V105_AZ = "V105_AZ";
        static const QString V104_AZ = "V104_AZ";
        // Electrolyser-2
        static const QString HV_O_HTO = "HV_O_HTO";
        static const QString PCV_O_HTO = "PCV_O_HTO";
        static const QString BV_O_HTO = "BV_O_HTO";
        static const QString MV_O_HTO = "MV_O_HTO";
        static const QString SV_O = "SV_O";
        static const QString HV_O_A = "HV_O_A";
        static const QString HV_H_A = "HV_H_A";
        static const QString XV_H_U = "XV_H_U";
        static const QString NRV1_H_U = "NRV1_H_U";
        static const QString NRV_N = "NRV_N";
        static const QString MV_F_P_PW = "MV_F_P_PW";
        static const QString NRV_F_P_FW = "NRV_F_P_FW";
        static const QString BV_P_F_OUT = "BV_P_F_OUT";
        static const QString BV_P_F_In = "BV_P_F_In";
        static const QString BV_BT_H_D = "BV_BT_H_D";
        static const QString SV_F = "SV_F";
        static const QString CV_F = "CV_F";
        static const QString MV_BT_H_D = "MV_BT_H_D";
        static const QString MV_BT_O_D = "MV_BT_O_D";
        static const QString MV_F_BT_H = "MV_F_BT_H";
        static const QString MV_F_D = "MV_F_D";
        static const QString HV_GC2 = "HV_GC2";
        static const QString HV_GC1 = "HV_GC1";
        static const QString CV_GC = "CV_GC";
        static const QString HV_CW_GC = "HV_CW_GC";
        static const QString HV_EC1 = "HV_EC1";
        static const QString HV_EC2 = "HV_EC2";
        static const QString CV_EC = "CV_EC";
        static const QString Dr_100_R = "Dr_100_R";
        static const QString Dr_200_R = "Dr_200_R";
        static const QString B_100_R = "B_100_R";
        static const QString RHV_BP_DC = "RHV_BP_DC";
        static const QString RV_BP_DC = "RV_BP_DC";
        static const QString BVP_CLC_In = "BVP_CLC_In";
        static const QString F_CLC = "F_CLC";
        static const QString Dr_1 = "Dr_1";
        static const QString BV_EV = "BV_EV";
        static const QString Dr_2 = "Dr_2";
        static const QString RHVDT_PR_In = "RHVDT_PR_In";
        static const QString RHVDT_PR_Out = "RHVDT_PR_Out";
        static const QString RVBP_CLC = "RVBP_CLC";
        static const QString BVP_EC_IN = "BVP_EC_IN";
        static const QString Dr_3 = "Dr_3";
        static const QString BVP_EC_Out = "BVP_EC_Out";
        static const QString RHVDT_GC = "RHVDT_GC";
        static const QString RHVEC_Out = "RHVEC_Out";
        static const QString HV_E_D2 = "HV_E_D2";
        static const QString HV_E_D1 = "HV_E_D1";

        // Electrolyser-1
        static const QString EL1_NRV2_N = "EL1_NRV2_N";
        static const QString EL1_MV_F_H = "EL1_MV_F_H";
        static const QString EL1_NRV_F_H = "EL1_NRV_F_H";
        static const QString EL1_BV_P_F_OUT = "EL1_BV_P_F_OUT";
        static const QString EL1_HV_N = "EL1_HV_N";
        static const QString EL1_RHV_CW_GC = "EL1_RHV_CW_GC";
        static const QString EL1_SV_GC = "EL1_SV_GC";
        static const QString EL1_MV_N2 = "EL1_MV_N2";
        static const QString EL1_MV_N3 = "EL1_MV_N3";
        static const QString EL1_MV_N1 = "EL1_MV_N1";
        static const QString EL1_MV1a_O_A = "EL1_MV1a_O_A";
        static const QString EL1_MV1b_O_A = "EL1_MV1b_O_A";
        static const QString EL1_HV_O_A = "EL1_HV_O_A";
        static const QString EL1_SV_O = "EL1_SV_O";
        static const QString EL1_SV_H = "EL1_SV_H";
        static const QString EL1_MV1a_H_U = "EL1_MV1a_H_U";
        static const QString EL1_MV1b_H_U = "EL1_MV1b_H_U";
        static const QString EL1_MV1_H_A = "EL1_MV1_H_A";
        static const QString EL1_HV_H_A = "EL1_HV_H_A";
        static const QString EL1_HV_O_HTO = "EL1_HV_O_HTO";
        static const QString EL1_PCV_O_HTO = "EL1_PCV_O_HTO";
        static const QString EL1_BV_O_HTO = "EL1_BV_O_HTO";
        static const QString EL1_MV_CG_HTO = "EL1_MV_CG_HTO";
        static const QString EL1_MV_O_HTO = "EL1_MV_O_HTO";
        static const QString EL1_BV_BT_H_D = "EL1_BV_BT_H_D";
        static const QString EL1_CV_F_H = "EL1_CV_F_H";
        static const QString EL1_SV_N = "EL1_SV_N";
        static const QString EL1_XV_H_U = "EL1_XV_H_U";
        static const QString EL1_NRV1_H_U = "EL1_NRV1_H_U";
        static const QString EL1_HV_E_D1 = "EL1_HV_E_D1";
        static const QString EL1_SV_EC = "EL1_SV_EC";
        static const QString EL1_MV_H_U = "EL1_MV_H_U";
        static const QString EL1_A16 = "EL1_A16";
        static const QString EL1_N1 = "EL1_N1";
        static const QString EL1_PCV_IA = "EL1_PCV_IA";
        static const QString EL1_BV_IA = "EL1_BV_IA";
        static const QString EL1_BV_GC_Deo_In = "EL1_BV_GC_Deo_In";
        static const QString EL1_BV_GC_Deo_Out = "EL1_BV_GC_Deo_Out";
        static const QString EL1_BV_H = "EL1_BV_H";
        static const QString EL1_RHV_CW_Deo = "EL1_RHV_CW_Deo";
        static const QString EL1_NRV1_N = "EL1_NRV1_N";
        static const QString EL1_HV_N_Deo = "EL1_HV_N_Deo";
        static const QString EL1_XV_N_D2 = "EL1_XV_N_D2";
        static const QString EL1_XV_N_D1 = "EL1_XV_N_D1";
        static const QString EL1_PCV_N_Deo = "EL1_PCV_N_Deo";
        static const QString EL1_XV_N_D3 = "EL1_XV_N_D3";
        static const QString EL1_SV_Deo = "EL1_SV_Deo";
        static const QString EL1_SV_GC_Deo = "EL1_SV_GC_Deo";
        static const QString EL1_SV_Da_H = "EL1_SV_Da_H";
        static const QString EL1_XV_Da_H_U = "EL1_XV_Da_H_U";
        static const QString EL1_XV_E_Da_H = "EL1_XV_E_Da_H";
        static const QString EL1_XV_Db_H_U = "EL1_XV_Db_H_U";
        static const QString EL1_XV_R_Db_H = "EL1_XV_R_Db_H";
        static const QString EL1_SV_Db_H = "EL1_SV_Db_H";
        static const QString EL1_BRV_RG_H = "EL1_BRV_RG_H";
        static const QString EL1_RHV_RG_H = "EL1_RHV_RG_H";
        static const QString EL1_MV2_H_A = "EL1_MV2_H_A";
        static const QString EL1_HV2_H_A = "EL1_HV2_H_A";
        static const QString EL1_HV3_H_A = "EL1_HV3_H_A";
        static const QString EL1_XV3_H_A = "EL1_XV3_H_A";
        static const QString EL1_BPR_H_U = "EL1_BPR_H_U";
        static const QString EL1_XV2_H_U = "EL1_XV2_H_U";
        static const QString EL1_HV_S2_H = "EL1_HV_S2_H";
        static const QString EL1_NRV2_H_U = "EL1_NRV2_H_U";
        static const QString EL1_BV_H_U = "EL1_BV_H_U";
        static const QString EL1_XV_Da_H_A = "EL1_XV_Da_H_A";
        static const QString EL1_XV_Db_H_A = "EL1_XV_Db_H_A";
        static const QString EL1_HV_H_D = "EL1_HV_H_D";
        static const QString EL1_XV_H_Da_H = "EL1_XV_H_Da_H";
        static const QString El1_XV_H_Db_H = "El1_XV_H_Db_H";
        static const QString EL1_MV_AD_H_A = "EL1_MV_AD_H_A";

        static QStringList keys()
        {
            return QStringList()
                << MV1aO_A
                << MV1bO_A
                << MV1H_A
                << MV1aH_U
                << MV1bH_U
                << BV_N1
                << MV_N2
                << BV_N3
                << HV_N
                << Dr_1H
                << Dr_2H
                << Dr_3H
                << Dr_4H
                << Dr_5H
                << Dr_6H
                << Dr_7H
                << Dr_8H
                << Dr_9H
                << Dr_10H
                << V26
                << Dr_13H_R
                << V23_R
                << V2D_R
                << OK_1H_R
                << Dr_17H_R
                << V25_R
                << V21_A_1_R
                << V21_A_2_R
                << V26_R
                << V24_R
                << V1D_R
                << OK_2H_R
                << Dr_16H_R
                << V32A
                << OP_H1
                << V20
                << V19
                << V22_R
                << V32
                << V28
                << V30
                << Dr_4AZ
                << Dr_3AZ
                << Dr_2AZ
                << Dr_1AZ
                << V4AZ
                << V3AZ
                << V2AZ
                << V1AZ
                << V27
                << V29
                << V25
                << V31A
                << Dr_12H_R
                << OP_H2
                << V31
                << M7_H
                << V108
                << V109
                << V110AZ
                << V112AZ
                << Dr_5AZ
                << OP_41
                << V41
                << V44
                << V45P
                << OP_40
                << V40
                << V42
                << Dr_11H
                << V43
                << V7AZ_R
                << V8_AZ_R
                << Dr_7AZ_R
                << OK1_AZ_R
                << Dr_8A3_R
                << V9_AZ_R
                << V11_AZ_R
                << V12_AZ_R
                << V10_AZ_R
                << V5AZ
                << V6AZ
                << Dr_AZ
                << OK1_AZ
                << V117AZ
                << V118AZ
                << Dr_6AZ
                << V119AZ
                << OK_AZ
                << V107_AZ
                << V106_AZ
                << V105_AZ
                << V104_AZ
                << HV_O_HTO
                << PCV_O_HTO
                << BV_O_HTO
                << MV_O_HTO
                << SV_O
                << HV_O_A
                << HV_H_A
                << XV_H_U
                << NRV1_H_U
                << NRV_N
                << MV_F_P_PW
                << NRV_F_P_FW
                << BV_P_F_OUT
                << BV_P_F_In
                << BV_BT_H_D
                << SV_F
                << CV_F
                << MV_BT_H_D
                << MV_BT_O_D
                << MV_F_BT_H
                << MV_F_D
                << HV_GC2
                << HV_GC1
                << CV_GC
                << HV_CW_GC
                << HV_EC1
                << HV_EC2
                << CV_EC
                << Dr_100_R
                << Dr_200_R
                << B_100_R
                << RHV_BP_DC
                << RV_BP_DC
                << BVP_CLC_In
                << F_CLC
                << Dr_1
                << BV_EV
                << Dr_2
                << BVP_CLC_In
                << RHVDT_PR_In
                << RHVDT_PR_Out
                << RVBP_CLC
                << BVP_EC_IN
                << Dr_3
                << BVP_EC_Out
                << RHVDT_GC
                << RHVEC_Out
                << HV_E_D2
                << HV_E_D1

                << EL1_NRV2_N
                << EL1_MV_F_H
                << EL1_NRV_F_H
                << EL1_BV_P_F_OUT
                << EL1_HV_N
                << EL1_RHV_CW_GC
                << EL1_SV_GC
                << EL1_MV_N2
                << EL1_MV_N3
                << EL1_MV_N1
                << EL1_MV1a_O_A
                << EL1_MV1b_O_A
                << EL1_HV_O_A
                << EL1_SV_O
                << EL1_SV_H
                << EL1_MV1a_H_U
                << EL1_MV1b_H_U
                << EL1_MV1_H_A
                << EL1_HV_H_A
                << EL1_HV_O_HTO
                << EL1_PCV_O_HTO
                << EL1_BV_O_HTO
                << EL1_MV_CG_HTO
                << EL1_MV_O_HTO
                << EL1_BV_BT_H_D
                << EL1_CV_F_H
                << EL1_SV_N
                << EL1_XV_H_U
                << EL1_NRV1_H_U
                << EL1_HV_E_D1
                << EL1_SV_EC
                << EL1_MV_H_U
                << EL1_A16
                << EL1_N1
                << EL1_PCV_IA
                << EL1_BV_IA
                << EL1_BV_GC_Deo_In
                << EL1_BV_GC_Deo_Out
                << EL1_BV_H
                << EL1_RHV_CW_Deo
                << EL1_NRV1_N
                << EL1_HV_N_Deo
                << EL1_XV_N_D2
                << EL1_XV_N_D1
                << EL1_PCV_N_Deo
                << EL1_XV_N_D3
                << EL1_SV_Deo
                << EL1_SV_GC_Deo
                << EL1_SV_Da_H
                << EL1_XV_Da_H_U
                << EL1_XV_E_Da_H
                << EL1_XV_Db_H_U
                << EL1_XV_R_Db_H
                << EL1_SV_Db_H
                << EL1_BRV_RG_H
                << EL1_RHV_RG_H
                << EL1_MV2_H_A
                << EL1_HV2_H_A
                << EL1_HV3_H_A
                << EL1_XV3_H_A
                << EL1_BPR_H_U
                << EL1_XV2_H_U
                << EL1_HV_S2_H
                << EL1_NRV2_H_U
                << EL1_BV_H_U
                << EL1_XV_Da_H_A
                << EL1_XV_Db_H_A
                << EL1_HV_H_D
                << EL1_XV_H_Da_H
                << El1_XV_H_Db_H
                << EL1_MV_AD_H_A;
        }
    } // namespace Valve

    namespace Separators
    {
        static const QString GAS_SEP_H = "GAS_SEP_H";
        static const QString GAS_SEP_O = "GAS_SEP_O";
        static const QString EL1_GAS_SEP_H = "EL1_GAS_SEP_H";
        static const QString EL1_GAS_SEP_O = "EL1_GAS_SEP_O";

        static QStringList keys()
        {
            return QStringList()
                    << GAS_SEP_H
                    << GAS_SEP_O
                    << EL1_GAS_SEP_H
                    << EL1_GAS_SEP_O
                       ;
        }
    }

    namespace WaterLocks
    {
        static const QString LS_WL_OL = "LS_WL_OL";
        static const QString LS_WL_HL = "LS_WL_HL";

        static QStringList keys()
        {
            return QStringList()
                    << LS_WL_HL
                    << LS_WL_OL
                       ;
        }
    }

    namespace CoalescentFilters
    {
        static const QString CF_O = "CF_O";
        static const QString CF_H = "CF_H";
        static const QString EL1_CF_O = "EL1_CF_O";
        static const QString EL1_CF_H = "EL1_CF_H";

        static QStringList keys()
        {
            return QStringList()
                    << CF_H
                    << CF_O
                    << EL1_CF_O
                    << EL1_CF_H
                       ;;
        }
    } //  namespace CoalescentFilters

    namespace Rinsers
    {
        static const QString RC_H = "RC_H";
        static const QString EL1_RC_H = "EL1_RC_H";

        static QStringList keys()
        {
            return QStringList()
                    << RC_H
                    << EL1_RC_H
                       ;;
        }
    } // namespace Rinsers

    namespace HeatExchangers
    {
        static const QString C_O = "C_O";
        static const QString C_CS12_O = "C_CS12_O";
        static const QString C_CS12_H = "C_CS12_H";

        static QStringList keys()
        {
            return QStringList()
                    << C_O
                    << C_CS12_H
                    << C_CS12_O
                       ;;
        }
    } // namespace HeatExchangers

    /*
     * НАЧАЛЬНЫЕ УСЛОВИЯ
     */
    namespace Conditions {
        namespace Result
        {
            static const QString Basic = "COND_BASIC";
            static const QString N2Purge = "COND_N2_PURGE";
            static const QString H2Production = "COND_H2_PRODUCTION";
            static const QString CS1 = "COND_CS1";
            static const QString CS2 = "COND_CS2";
            static const QString CS3 = "COND_CS3";
            static const QString CS4 = "COND_CS4";
        } // namespace Result

        /*
         * ОБЩИЕ НАЧАЛЬНЫЕ УСЛОВИЯ
         */
        namespace Basic {
            static const QString BASIC_STCD = "BASIC_STCD";
            static const QString EMS_A = "EMS_A";
            static const QString EMS_B = "EMS_B";
            static const QString EMS_C = "EMS_C";
            static const QString EMS_D = "EMS_D";
            static const QString HTA_PR_ROOM_OK_M = "HTA_PR_ROOM_OK_M";
            static const QString FUSE_MV_OK_M = "FUSE_MV_OK_M";
            static const QString _24V_SUPPLY_OK_M = "_24V_SUPPLY_OK_M";
            static const QString FUSE_F2_OK_M = "FUSE_F2_OK_M";
            static const QString FUSE_F3_OK_M = "FUSE_F3_OK_M";
            static const QString FUSE_F4_OK_M = "FUSE_F4_OK_M";
            static const QString FUSE_F5_OK_M = "FUSE_F5_OK_M";
            static const QString FUSE_F6_OK_M = "FUSE_F6_OK_M";
            static const QString _24V_UPS_HH_M = "_24V_UPS_HH_M";
            static const QString _24V_UPS_LL_M = "_24V_UPS_LL_M";
            static const QString OTA_HH_M = "OTA_HH_M";
            static const QString OTA_LL_M = "OTA_LL_M";
            static const QString MASTER_BASIC_STCD = "MASTER_BASIC_STCD";
            static const QString HTA_CPR_ROOM_OK_M = "HTA_CPR_ROOM_OK_M";
            static const QString PS_IA_OK_M = "PS_IA_OK_M";
            static const QString FUSE_F7_OK_M = "FUSE_F7_OK_M";
            static const QString DS_PROC_ROOM_OK_M = "DS_PROC_ROOM_OK_M";
            static const QString SM_AND_FIRE_ALARM_OK_M = "SM_AND_FIRE_ALARM_OK_M";
            static const QString PS_N2_L_OK_M = "PS_N2_L_OK_M";
            static const QString PS_N2_LL_OK_M = "PS_N2_LL_OK_M";
            static const QString HTA_DET_HEAD_FAIL = "HTA_DET_HEAD_FAIL";

            static QStringList keys()
            {
                return QStringList()
                        << EMS_A
                        << EMS_B
                        << EMS_C
                        << EMS_D
                        << HTA_PR_ROOM_OK_M
                        << FUSE_MV_OK_M
                        << _24V_SUPPLY_OK_M
                        << FUSE_F2_OK_M
                        << FUSE_F3_OK_M
                        << FUSE_F4_OK_M
                        << FUSE_F5_OK_M
                        << FUSE_F6_OK_M
                        << _24V_UPS_HH_M
                        << _24V_UPS_LL_M
                        << OTA_HH_M
                        << OTA_LL_M
                        << MASTER_BASIC_STCD
                        << HTA_CPR_ROOM_OK_M
                        << PS_IA_OK_M
                        << FUSE_F7_OK_M
                        << DS_PROC_ROOM_OK_M
                        << SM_AND_FIRE_ALARM_OK_M
                        << PS_N2_L_OK_M
                        << PS_N2_LL_OK_M
                        << HTA_DET_HEAD_FAIL
                           ;
            }

            static QStringList memorizedKeys()
            {
                return QStringList()
                        << HTA_PR_ROOM_OK_M
                        << FUSE_MV_OK_M
                        << _24V_SUPPLY_OK_M
                        << FUSE_F2_OK_M
                        << FUSE_F3_OK_M
                        << FUSE_F4_OK_M
                        << FUSE_F5_OK_M
                        << FUSE_F6_OK_M
                        << _24V_UPS_HH_M
                        << _24V_UPS_LL_M
                        << OTA_HH_M
                        << OTA_LL_M
                        << HTA_CPR_ROOM_OK_M
                        << PS_IA_OK_M
                        << FUSE_F7_OK_M
                        << DS_PROC_ROOM_OK_M
                        << SM_AND_FIRE_ALARM_OK_M
                        << PS_N2_L_OK_M
                        << PS_N2_LL_OK_M
                           ;
            }

            static QStringList editableKeys()
            {
                return QStringList()
                        << keys();
            }
        }
        /*
         * НАЧАЛЬНЫЕ УСЛОВИЯ ПРОДУВКИ АЗОТОМ
         */
        namespace N2Purge {
            static const QString LS_HG_H = "LS_HG_H";
            static const QString LS_HG_L = "LS_HG_L";
            static const QString LS_OG_H = "LS_OG_H";
            static const QString LS_OG_L = "LS_OG_L";
            static const QString PT_HH_M = "PT_HH_M";
            static const QString PT_BW_M = "PT_BW_M";
            static const QString LTH_HH_M = "LTH_HH_M";
            static const QString LTH_LL_M = "LTH_LL_M";
            static const QString LTO_HH_M = "LTO_HH_M";
            static const QString LTO_LL_M = "LTO_LL_M";
            static const QString N2_PURGE_OK = "N2_PURGE_OK";
            static const QString DEPR_TO_0_EN = "DEPR_TO_0_EN";
            static const QString NOT_HAND_MODE = "NOT_HAND_MODE";

            static QStringList keys()
            {
                return QStringList()
                        << LS_HG_H
                        << LS_HG_L
                        << LS_OG_H
                        << LS_OG_L
                        << PT_HH_M
                        << PT_BW_M
                        << LTH_HH_M
                        << LTH_LL_M
                        << LTO_HH_M
                        << LTO_LL_M
                        << N2_PURGE_OK
                        << DEPR_TO_0_EN
                        << NOT_HAND_MODE
                           ;
            }

            static QStringList memorizedKeys()
            {
                return QStringList()
                        << LTH_HH_M
                        << LTH_LL_M
                        << LTO_HH_M
                        << LTO_LL_M
                        ;
            }

            static QStringList editableKeys()
            {
                return QStringList()
                        << keys();
            }
        }
        /*
         * НАЧАЛЬНЫЕ УСЛОВИЯ ПРОИЗВОДСТВА ВОДОРОДА
         */
        namespace H2Production {
            static const QString N2_P_SC_OK = "N2_P_SC_OK";
            static const QString H2_D_SC_OK = "H2_D_SC_OK";
            static const QString MST_H2_P_SC_OK = "MST_H2_P_SC_OK";
            static const QString FANS_EPS_OK_M = "FANS_EPS_OK_M";
            static const QString PHASE_CHECKER_OK_M = "PHASE_CHECKER_OK_M";
            static const QString HW_HTO_H_OK_M = "HW_HTO_H_OK_M";
            static const QString HW_HTO_L_OK_M = "HW_HTO_L_OK_M";
            static const QString HTO_HH_M = "HTO_HH_M";
            static const QString HTO_LL_M = "HTO_LL_M";
            static const QString OH_FANS_OK_M = "OH_FANS_OK_M";
            static const QString CLOSED_LOOP_OK_M = "CLOSED_LOOP_OK_M";
            static const QString CW_PS_OK_M = "CW_PS_OK_M";
            static const QString CHILLER_OK_M = "CHILLER_OK_M";
            static const QString LS_DT1_OK_M = "LS_DT1_OK_M";
            static const QString LS_DT2_OK_M = "LS_DT2_OK_M";
            static const QString LS_H2_WL_OK_M = "LS_H2_WL_OK_M";
            static const QString LS_O2_WL_OK_M = "LS_O2_WL_OK_M";
            static const QString LS_WL_OK_M = "LS_WL_OK_M";
            static const QString DIFF_PRES_AIR_FLOW_SWITCH = "DIFF_PRES_AIR_FLOW_SWITCH";
            static const QString FS_HTO_OK_M = "FS_HTO_OK_M";
            static const QString LS_BT_LL_OK_M = "LS_BT_LL_OK_M";
            static const QString O2_DRIER_START_CONDITIONS = "O2_DRIER_START_CONDITIONS";
            static const QString MASTER_DRIER_STARTCOND_ARE_OK = "MASTER_DRIER_STARTCOND_ARE_OK";
            static const QString PROX_SWITCH_AIR_FLOW_OK_M = "PROX_SWITCH_AIR_FLOW_OK_M";
            static const QString PT_CHILL_HH_OK = "PT_CHILL_HH_OK";
            static const QString PT_CL_HH_OK = "PT_CL_HH_OK";
            static const QString PT_CHILL_LL_OK = "PT_CHILL_LL_OK";
            static const QString PT_CL_LL_OK = "PT_CL_LL_OK";

            static QStringList keys()
            {
                return QStringList()
                        << N2_P_SC_OK
                        << H2_D_SC_OK
                        << MST_H2_P_SC_OK
                        << FANS_EPS_OK_M
                        << PHASE_CHECKER_OK_M
                        << HW_HTO_H_OK_M
                        << HW_HTO_L_OK_M
                        << HTO_HH_M
                        << HTO_LL_M
                        << OH_FANS_OK_M
                        << CLOSED_LOOP_OK_M
                        << CW_PS_OK_M
                        << CHILLER_OK_M
                        << LS_DT1_OK_M
                        << LS_DT2_OK_M
                        << LS_H2_WL_OK_M
                        << LS_O2_WL_OK_M
                        << LS_WL_OK_M
                        << DIFF_PRES_AIR_FLOW_SWITCH
                        << FS_HTO_OK_M
                        << LS_BT_LL_OK_M
                        << O2_DRIER_START_CONDITIONS
                        << MASTER_DRIER_STARTCOND_ARE_OK
                        << PROX_SWITCH_AIR_FLOW_OK_M
                        << PT_CHILL_HH_OK
                        << PT_CL_HH_OK
                        << PT_CHILL_LL_OK
                        << PT_CL_LL_OK
                           ;
            }

            static QStringList memorizedKeys()
            {
                return QStringList()
                        << FANS_EPS_OK_M
                        << PHASE_CHECKER_OK_M
                        << HW_HTO_H_OK_M
                        << HW_HTO_L_OK_M
                        << HTO_HH_M
                        << HTO_LL_M
                        << OH_FANS_OK_M
                        << CLOSED_LOOP_OK_M
                        << CW_PS_OK_M
                        << CHILLER_OK_M
                        << LS_DT1_OK_M
                        << LS_DT2_OK_M
                        << LS_H2_WL_OK_M
                        << LS_O2_WL_OK_M
                        << LS_WL_OK_M
                        << FS_HTO_OK_M
                        << LS_BT_LL_OK_M
                        << PROX_SWITCH_AIR_FLOW_OK_M
                        ;
            }

            static QStringList editableKeys()
            {
                return QStringList()
                        << keys();
            }
        }
        /*
         * НАЧАЛЬНЫЕ УСЛОВИЯ МОДУЛЕЙ (ОБЩИЕ)
         */
        /*
         * НАЧАЛЬНЫЕ УСЛОВИЯ МОДУЛЯ 1
         */
        namespace CS1 {
            static const QString H2_P_SC_OK = "H2_P_SC_OK";
            static const QString EPS_DOOR_SW_1_OK_M = "EPS_DOOR-SW_1_OK_M";
            static const QString PHC_PR1 = "PHC_PR1";
            static const QString C_EPSCS1_OK_M = "C_EPSCS1_OK_M";
            static const QString CS1_T_SW_THYR_OK_M = "CS1_T-SW_THYR_OK_M";
            static const QString CS1_T_SW_DI_OK_M = "CS1_T-SW_DI_OK_M";
            static const QString TSCS1_OK_M = "TSCS1_OK_M";
            static const QString TTCS1_HH_M = "TTCS1_HH_M";
            static const QString TTCS1_LL_M = "TTCS1_LL_M";
            static const QString ITCS1_HH_M = "ITCS1_HH_M";
            static const QString ITCS1_LL_M = "ITCS1_LL_M";
            static const QString UTCS1A_HH_M = "UTCS1A_HH_M";
            static const QString UTCS1A_LL_M = "UTCS1A_LL_M";
            static const QString UTCS1B_HH_M = "UTCS1B_HH_M";
            static const QString UTCS1B_LL_M = "UTCS1B_LL_M";
            static const QString UTCS1A_LESS_UTCS1B_OK_M = "UTCS1A_LESS_UTCS1B_OK_M";
            static const QString UTCS1A_GREATER_UTCS1B_OK_M = "UTCS1A_GREATER_UTCS1B_OK_M";
            static const QString TS_CS1_FILTER = "TS_CS1_FILTER";

            static QStringList keys()
            {
                return QStringList()
                        << H2_P_SC_OK
                        << EPS_DOOR_SW_1_OK_M
                        << PHC_PR1
                        << C_EPSCS1_OK_M
                        << CS1_T_SW_THYR_OK_M
                        << CS1_T_SW_DI_OK_M
                        << TSCS1_OK_M
                        << TTCS1_HH_M
                        << TTCS1_LL_M
                        << ITCS1_HH_M
                        << ITCS1_LL_M
                        << UTCS1A_HH_M
                        << UTCS1A_LL_M
                        << UTCS1B_HH_M
                        << UTCS1B_LL_M
                        << UTCS1A_LESS_UTCS1B_OK_M
                        << UTCS1A_GREATER_UTCS1B_OK_M
                        << TS_CS1_FILTER
                           ;
            }

            static QStringList memorizedKeys()
            {
                return QStringList()
                        << EPS_DOOR_SW_1_OK_M
                        << C_EPSCS1_OK_M
                        << CS1_T_SW_THYR_OK_M
                        << CS1_T_SW_DI_OK_M
                        << TSCS1_OK_M
                        << TTCS1_HH_M
                        << TTCS1_LL_M
                        << ITCS1_HH_M
                        << ITCS1_LL_M
                        << UTCS1A_HH_M
                        << UTCS1A_LL_M
                        << UTCS1B_HH_M
                        << UTCS1B_LL_M
                        << UTCS1A_LESS_UTCS1B_OK_M
                        << UTCS1A_GREATER_UTCS1B_OK_M
                        ;
            }

            static QStringList editableKeys()
            {
                return QStringList()
                        << keys();
            }
        }
        /*
         * НАЧАЛЬНЫЕ УСЛОВИЯ МОДУЛЯ 2
         */
        namespace CS2 {
            static const QString H2_P_SC_OK = "H2_P_SC_OK";
            static const QString EPS_DOOR_SW_1_OK_M = "EPS_DOOR-SW_1_OK_M";
            static const QString PHC_PR1 = "PHC_PR1";
            static const QString C_EPSCS2_OK_M = "C_EPSCS2_OK_M";
            static const QString CS2_T_SW_THYR_OK_M = "CS2_T-SW_THYR_OK_M";
            static const QString CS2_T_SW_DI_OK_M = "CS2_T-SW_DI_OK_M";
            static const QString TSCS2_OK_M = "TSCS2_OK_M";
            static const QString TTCS2_HH_M = "TTCS2_HH_M";
            static const QString TTCS2_LL_M = "TTCS2_LL_M";
            static const QString ITCS2_HH_M = "ITCS2_HH_M";
            static const QString ITCS2_LL_M = "ITCS2_LL_M";
            static const QString UTCS2A_HH_M = "UTCS2A_HH_M";
            static const QString UTCS2A_LL_M = "UTCS2A_LL_M";
            static const QString UTCS2B_HH_M = "UTCS2B_HH_M";
            static const QString UTCS2B_LL_M = "UTCS2B_LL_M";
            static const QString UTCS2A_LESS_UTCS2B_OK_M = "UTCS2A_LESS_UTCS2B_OK_M";
            static const QString UTCS2A_GREATER_UTCS2B_OK_M = "UTCS2A_GREATER_UTCS2B_OK_M";
            static const QString TS_CS2_FILTER = "TS_CS2_FILTER";

            static QStringList keys()
            {
                return QStringList()
                        << H2_P_SC_OK
                        << EPS_DOOR_SW_1_OK_M
                        << PHC_PR1
                        << C_EPSCS2_OK_M
                        << CS2_T_SW_THYR_OK_M
                        << CS2_T_SW_DI_OK_M
                        << TSCS2_OK_M
                        << TTCS2_HH_M
                        << TTCS2_LL_M
                        << ITCS2_HH_M
                        << ITCS2_LL_M
                        << UTCS2A_HH_M
                        << UTCS2A_LL_M
                        << UTCS2B_HH_M
                        << UTCS2B_LL_M
                        << UTCS2A_LESS_UTCS2B_OK_M
                        << UTCS2A_GREATER_UTCS2B_OK_M
                        << TS_CS2_FILTER
                           ;
            }

            static QStringList memorizedKeys()
            {
                return QStringList()
                        << EPS_DOOR_SW_1_OK_M
                        << C_EPSCS2_OK_M
                        << CS2_T_SW_THYR_OK_M
                        << CS2_T_SW_DI_OK_M
                        << TSCS2_OK_M
                        << TTCS2_HH_M
                        << TTCS2_LL_M
                        << ITCS2_HH_M
                        << ITCS2_LL_M
                        << UTCS2A_HH_M
                        << UTCS2A_LL_M
                        << UTCS2B_HH_M
                        << UTCS2B_LL_M
                        << UTCS2A_LESS_UTCS2B_OK_M
                        << UTCS2A_GREATER_UTCS2B_OK_M
                        ;
            }

            static QStringList editableKeys()
            {
                return QStringList()
                        << keys();
            }
        }

        static QStringList memorizedKeys()
        {
            return QStringList()
                    << Basic::memorizedKeys()
                    << N2Purge::memorizedKeys()
                    << H2Production::memorizedKeys()
                    << CS1::memorizedKeys()
                    << CS2::memorizedKeys()
                    ;
        }

        static QStringList editableKeys()
        {
            return QStringList()
                    << Basic::editableKeys()
                    << N2Purge::editableKeys()
                    << H2Production::editableKeys()
                    << CS1::editableKeys()
                    << CS2::editableKeys()

                       ;;
        }

    } // namespace Conditions

    static QStringList initialKeys()
    {
        return
                ChartsValues::keys()
                << Purge::N2_PRESSURE;
                ;
    }

    static QStringList noiseableKeys()
    {
        return ChartsValues::keys();
    }

    namespace Manometers
    {
        static const QString M_PTGS = "M_PTGS";
        static const QString M_RCV_N = "M_RCV_N";

        static QStringList keys()
        {
            return QStringList()
                    << M_PTGS
                    << M_RCV_N
                    ;
        }
    }

    namespace Parameters
    {
        static const QString N2PURGE_PRESSURE_TIME_CONSTANT = "N2PURGE_PRESSURE_TIME_CONSTANT";
        static const QString N2PURGE_INITIAL_PRESSURE = "N2PURGE_INITIAL_PRESSURE";
        static const QString N2PURGE_MIN_PRESSURE = "N2PURGE_MIN_PRESSURE";
        static const QString N2PURGE_MAX_PRESSURE = "N2PURGE_MAX_PRESSURE";
        static const QString N2PURGE_INTERVAL_SEC = "N2PURGE_INTERVAL_SEC";
        static const QString H2PURGE_INTERVAL_SEC = "H2PURGE_INTERVAL_SEC";
        static const QString LEVEL_SENSITIVITY_THR = "LEVEL_SENSITIVITY_THR";
        static const QString LEVEL_ADJUSTMENT_THR = "LEVEL_ADJUSTMENT_THR";
        static const QString MAX_LEVEL = "MAX_LEVEL";
        static const QString LEVEL_RANGE_MAX = "LEVEL_RANGE_MAX";
        static const QString LEVEL_RANGE_MIN = "LEVEL_RANGE_MIN";
        static const QString DEPRESSURIZATION_THR = "DEPRESSURIZATION_THR";
        static const QString EMERGENCY_DEPRESSURIZATION_THR = "EMERGENCY_DEPRESSURIZATION_THR";

        static QStringList keys()
        {
            return QStringList()
                    << N2PURGE_PRESSURE_TIME_CONSTANT
                    << N2PURGE_INITIAL_PRESSURE
                    << N2PURGE_MIN_PRESSURE
                    << N2PURGE_MAX_PRESSURE
                    << N2PURGE_INTERVAL_SEC
                    << H2PURGE_INTERVAL_SEC
                    << LEVEL_SENSITIVITY_THR
                    << LEVEL_ADJUSTMENT_THR
                    << MAX_LEVEL
                    << LEVEL_RANGE_MAX
                    << LEVEL_RANGE_MIN
                    << DEPRESSURIZATION_THR
                    << EMERGENCY_DEPRESSURIZATION_THR
                    ;
        }
    }

    namespace LED {
        static const QString LED_1 = "led_1";
        static const QString LED_2 = "led_2";
        static const QString LED_3 = "led_3";
        static const QString LED_4 = "led_4";
        static const QString LED_5 = "led_5";
        static const QString LED_6 = "led_6";
        static const QString LED_7 = "led_7";
        static const QString LED_8 = "led_8";
        static const QString LED_9 = "led_9";
        static const QString LED_10 = "led_10";
        static const QString LED_11 = "led_11";
        static const QString LED_12 = "led_12";
        static const QString LED_13 = "led_13";
        static const QString LED_14 = "led_14";
        static const QString LED_15 = "led_15";
        static const QString LED_16 = "led_16";

        static QStringList keys()
        {
            return QStringList()
                    << LED_1
                    << LED_2
                    << LED_3
                    << LED_4
                    << LED_5
                    << LED_6
                    << LED_7
                    << LED_8
                    << LED_9
                    << LED_10
                    << LED_11
                    << LED_12
                    << LED_13
                    << LED_14
                    << LED_15
                    << LED_16
                    ;
        }
    }

} // namespace Model

#endif // STRINGSKEYS_H
