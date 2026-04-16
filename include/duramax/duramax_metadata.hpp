#pragma once

#include "duramax_ids.hpp"

#include <array>
#include <cstdint>
#include <span>
#include <string_view>

namespace duramax {

struct MessageMeta {
    MessageId id;
    std::uint32_t frame_id;
    std::uint8_t dlc;
    bool is_extended;
    std::uint32_t cycle_time_ms;
    std::string_view dbc_name;
    std::string_view cpp_name;
    std::uint16_t signal_offset;
    std::uint16_t signal_count;
};

struct SignalMeta {
    SignalId id;
    MessageId message_id;
    std::uint16_t start_bit;
    std::uint8_t bit_length;
    ByteOrder byte_order;
    bool is_signed;
    double scale;
    double offset;
    SignalType type;
    bool has_choices;
    std::string_view dbc_name;
    std::string_view cpp_name;
    std::string_view message_dbc_name;
    std::string_view unit;
    std::string_view choice_enum_name;
};

inline constexpr std::array<MessageMeta, kMessageCount> kMessagesById{ {
    MessageMeta{
        .id = MessageId::eec5_electronic_engine_control_5,
        .frame_id = 0x18FDD500u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 250,
        .dbc_name = "EEC5_Electronic_Engine_Control_5",
        .cpp_name = "eec5_electronic_engine_control_5",
        .signal_offset = 0,
        .signal_count = 6,
    },
    MessageMeta{
        .id = MessageId::eec9_electronic_engine_control_9,
        .frame_id = 0x10FCFD00u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 100,
        .dbc_name = "EEC9_Electronic_Engine_Control_9",
        .cpp_name = "eec9_electronic_engine_control_9",
        .signal_offset = 6,
        .signal_count = 3,
    },
    MessageMeta{
        .id = MessageId::ebcc_engine_exhaust_brake_cont,
        .frame_id = 0x10FCE300u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 100,
        .dbc_name = "EBCC_Engine_Exhaust_Brake_Cont",
        .cpp_name = "ebcc_engine_exhaust_brake_cont",
        .signal_offset = 9,
        .signal_count = 5,
    },
    MessageMeta{
        .id = MessageId::et3_engine_temperature_3,
        .frame_id = 0x18FE6900u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 1000,
        .dbc_name = "ET3_Engine_Temperature_3",
        .cpp_name = "et3_engine_temperature_3",
        .signal_offset = 14,
        .signal_count = 4,
    },
    MessageMeta{
        .id = MessageId::dm21_diagnostic_readiness_2,
        .frame_id = 0x18C1FF00u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "DM21_Diagnostic_Readiness_2",
        .cpp_name = "dm21_diagnostic_readiness_2",
        .signal_offset = 18,
        .signal_count = 1,
    },
    MessageMeta{
        .id = MessageId::dm26_diagnostic_readiness_3,
        .frame_id = 0x18FDB800u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "DM26_Diagnostic_Readiness_3",
        .cpp_name = "dm26_diagnostic_readiness_3",
        .signal_offset = 19,
        .signal_count = 1,
    },
    MessageMeta{
        .id = MessageId::ic1_intake_exhaust_cond_1,
        .frame_id = 0x18FEF600u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 500,
        .dbc_name = "IC1_Intake_Exhaust_Cond_1",
        .cpp_name = "ic1_intake_exhaust_cond_1",
        .signal_offset = 20,
        .signal_count = 7,
    },
    MessageMeta{
        .id = MessageId::amb_ambient_conditions,
        .frame_id = 0x18FEF500u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 1000,
        .dbc_name = "AMB_Ambient_Conditions",
        .cpp_name = "amb_ambient_conditions",
        .signal_offset = 27,
        .signal_count = 5,
    },
    MessageMeta{
        .id = MessageId::eec1_electronic_engine_control_1,
        .frame_id = 0x0CF00400u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 50,
        .dbc_name = "EEC1_Electronic_Engine_Control_1",
        .cpp_name = "eec1_electronic_engine_control_1",
        .signal_offset = 32,
        .signal_count = 8,
    },
    MessageMeta{
        .id = MessageId::eec2_electronic_engine_control_2,
        .frame_id = 0x0CF00300u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 50,
        .dbc_name = "EEC2_Electronic_Engine_Control_2",
        .cpp_name = "eec2_electronic_engine_control_2",
        .signal_offset = 40,
        .signal_count = 14,
    },
    MessageMeta{
        .id = MessageId::eec3_electronic_engine_control_3,
        .frame_id = 0x18FEDF00u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 250,
        .dbc_name = "EEC3_Electronic_Engine_Control_3",
        .cpp_name = "eec3_electronic_engine_control_3",
        .signal_offset = 54,
        .signal_count = 9,
    },
    MessageMeta{
        .id = MessageId::efl_p1_eng_fluid_level_press_1,
        .frame_id = 0x18FEEF00u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 500,
        .dbc_name = "EFL_P1_Eng_Fluid_Level_Press_1",
        .cpp_name = "efl_p1_eng_fluid_level_press_1",
        .signal_offset = 63,
        .signal_count = 7,
    },
    MessageMeta{
        .id = MessageId::efl_p2_eng_fluid_level_press_2,
        .frame_id = 0x18FEDB00u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 500,
        .dbc_name = "EFL_P2_Eng_Fluid_Level_Press_2",
        .cpp_name = "efl_p2_eng_fluid_level_press_2",
        .signal_offset = 70,
        .signal_count = 4,
    },
    MessageMeta{
        .id = MessageId::et1_engine_temperature_1,
        .frame_id = 0x18FEEE00u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 1000,
        .dbc_name = "ET1_Engine_Temperature_1",
        .cpp_name = "et1_engine_temperature_1",
        .signal_offset = 74,
        .signal_count = 6,
    },
    MessageMeta{
        .id = MessageId::lfe1_fuel_economy_liquid_1,
        .frame_id = 0x18FEF200u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 100,
        .dbc_name = "LFE1_Fuel_Economy_Liquid_1",
        .cpp_name = "lfe1_fuel_economy_liquid_1",
        .signal_offset = 80,
        .signal_count = 5,
    },
    MessageMeta{
        .id = MessageId::transportprotocol_header,
        .frame_id = 0x18ECFF00u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "TransportProtocol_Header",
        .cpp_name = "transportprotocol_header",
        .signal_offset = 85,
        .signal_count = 12,
    },
    MessageMeta{
        .id = MessageId::transportprotocol_data,
        .frame_id = 0x18EBFF00u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "TransportProtocol_Data",
        .cpp_name = "transportprotocol_data",
        .signal_offset = 97,
        .signal_count = 1,
    },
    MessageMeta{
        .id = MessageId::dm01_active_diagnostics,
        .frame_id = 0x18FECA00u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "DM01_Active_Diagnostics",
        .cpp_name = "dm01_active_diagnostics",
        .signal_offset = 98,
        .signal_count = 9,
    },
    MessageMeta{
        .id = MessageId::tsc1_31,
        .frame_id = 0x0C000031u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 10,
        .dbc_name = "TSC1_31",
        .cpp_name = "tsc1_31",
        .signal_offset = 107,
        .signal_count = 10,
    },
    MessageMeta{
        .id = MessageId::cac1_charge_air_cooler_1,
        .frame_id = 0x18FCF600u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 1000,
        .dbc_name = "CAC1_Charge_Air_Cooler_1",
        .cpp_name = "cac1_charge_air_cooler_1",
        .signal_offset = 117,
        .signal_count = 3,
    },
    MessageMeta{
        .id = MessageId::hours_engine_hours_revolutions,
        .frame_id = 0x18FEE500u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "HOURS_Engine_Hours_Revolutions",
        .cpp_name = "hours_engine_hours_revolutions",
        .signal_offset = 120,
        .signal_count = 2,
    },
    MessageMeta{
        .id = MessageId::tci5_turbocharger_information_5,
        .frame_id = 0x18FE9700u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 1000,
        .dbc_name = "TCI5_Turbocharger_Information_5",
        .cpp_name = "tci5_turbocharger_information_5",
        .signal_offset = 122,
        .signal_count = 4,
    },
    MessageMeta{
        .id = MessageId::vep1_vehicle_electrical_power_1,
        .frame_id = 0x18FEF700u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 1000,
        .dbc_name = "VEP1_Vehicle_Electrical_Power_1",
        .cpp_name = "vep1_vehicle_electrical_power_1",
        .signal_offset = 126,
        .signal_count = 5,
    },
    MessageMeta{
        .id = MessageId::eec20_electronic_engine_control,
        .frame_id = 0x18FC0B00u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 250,
        .dbc_name = "EEC20_Electronic_Engine_Control_",
        .cpp_name = "eec20_electronic_engine_control",
        .signal_offset = 131,
        .signal_count = 1,
    },
    MessageMeta{
        .id = MessageId::easi_engine_air_system_info,
        .frame_id = 0x0CF03900u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 20,
        .dbc_name = "EASI_Engine_Air_System_Info",
        .cpp_name = "easi_engine_air_system_info",
        .signal_offset = 132,
        .signal_count = 1,
    },
    MessageMeta{
        .id = MessageId::tsc1_03,
        .frame_id = 0x0C000003u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 10,
        .dbc_name = "TSC1_03",
        .cpp_name = "tsc1_03",
        .signal_offset = 133,
        .signal_count = 10,
    },
    MessageMeta{
        .id = MessageId::tsc1_0b,
        .frame_id = 0x0C00000Bu,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 10,
        .dbc_name = "TSC1_0B",
        .cpp_name = "tsc1_0b",
        .signal_offset = 143,
        .signal_count = 10,
    },
    MessageMeta{
        .id = MessageId::dm07,
        .frame_id = 0x18E3005Eu,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "DM07",
        .cpp_name = "dm07",
        .signal_offset = 153,
        .signal_count = 4,
    },
    MessageMeta{
        .id = MessageId::dm08,
        .frame_id = 0x18FED000u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "DM08",
        .cpp_name = "dm08",
        .signal_offset = 157,
        .signal_count = 5,
    },
    MessageMeta{
        .id = MessageId::erc1_electronic_retarder_cntrl,
        .frame_id = 0x18F00029u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 100,
        .dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .cpp_name = "erc1_electronic_retarder_cntrl",
        .signal_offset = 162,
        .signal_count = 13,
    },
    MessageMeta{
        .id = MessageId::etc1_electronic_trans_cntrl_1,
        .frame_id = 0x0CF00203u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 10,
        .dbc_name = "ETC1_Electronic_Trans_Cntrl_1",
        .cpp_name = "etc1_electronic_trans_cntrl_1",
        .signal_offset = 175,
        .signal_count = 11,
    },
    MessageMeta{
        .id = MessageId::etc2_electronic_trans_cntrl_2,
        .frame_id = 0x18F00503u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 100,
        .dbc_name = "ETC2_Electronic_Trans_Cntrl_2",
        .cpp_name = "etc2_electronic_trans_cntrl_2",
        .signal_offset = 186,
        .signal_count = 5,
    },
    MessageMeta{
        .id = MessageId::rqst_00_5e,
        .frame_id = 0x18EA005Eu,
        .dlc = 3,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "RQST_00_5E",
        .cpp_name = "rqst_00_5e",
        .signal_offset = 191,
        .signal_count = 1,
    },
    MessageMeta{
        .id = MessageId::rqst_00_21,
        .frame_id = 0x18EA0021u,
        .dlc = 3,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "RQST_00_21",
        .cpp_name = "rqst_00_21",
        .signal_offset = 192,
        .signal_count = 1,
    },
    MessageMeta{
        .id = MessageId::rqst_global_5e,
        .frame_id = 0x18EAFF5Eu,
        .dlc = 3,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "RQST_Global_5E",
        .cpp_name = "rqst_global_5e",
        .signal_offset = 193,
        .signal_count = 1,
    },
    MessageMeta{
        .id = MessageId::rqst_global_03,
        .frame_id = 0x18EAFF03u,
        .dlc = 3,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "RQST_Global_03",
        .cpp_name = "rqst_global_03",
        .signal_offset = 194,
        .signal_count = 1,
    },
    MessageMeta{
        .id = MessageId::tci_transfer_case_information,
        .frame_id = 0x18FD8321u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 1000,
        .dbc_name = "TCI_Transfer_Case_Information",
        .cpp_name = "tci_transfer_case_information",
        .signal_offset = 195,
        .signal_count = 5,
    },
    MessageMeta{
        .id = MessageId::trf1_transmission_fluids_1,
        .frame_id = 0x18FEF803u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 1000,
        .dbc_name = "TRF1_Transmission_Fluids_1",
        .cpp_name = "trf1_transmission_fluids_1",
        .signal_offset = 200,
        .signal_count = 8,
    },
    MessageMeta{
        .id = MessageId::ccss_cruise_control_vehicle_spd,
        .frame_id = 0x18FEED00u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 0,
        .dbc_name = "CCSS_Cruise_Control_Vehicle_Spd",
        .cpp_name = "ccss_cruise_control_vehicle_spd",
        .signal_offset = 208,
        .signal_count = 10,
    },
    MessageMeta{
        .id = MessageId::ccvs1_cruise_control_vehspd,
        .frame_id = 0x18FEF100u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 100,
        .dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .cpp_name = "ccvs1_cruise_control_vehspd",
        .signal_offset = 218,
        .signal_count = 20,
    },
    MessageMeta{
        .id = MessageId::ebc1_electronic_brake_cntrl,
        .frame_id = 0x18F0010Bu,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 100,
        .dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .cpp_name = "ebc1_electronic_brake_cntrl",
        .signal_offset = 238,
        .signal_count = 23,
    },
    MessageMeta{
        .id = MessageId::shutdn,
        .frame_id = 0x18FEE400u,
        .dlc = 8,
        .is_extended = true,
        .cycle_time_ms = 1000,
        .dbc_name = "SHUTDN",
        .cpp_name = "shutdn",
        .signal_offset = 261,
        .signal_count = 22,
    },
} };

inline constexpr std::array<SignalMeta, kSignalCount> kSignalsById{ {
    SignalMeta{
        .id = SignalId::eec5_electronic_engine_control_5__engine_turbocharger_1_calculated,
        .message_id = MessageId::eec5_electronic_engine_control_5,
        .start_bit = 0,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Turbocharger_1_Calculated",
        .cpp_name = "engine_turbocharger_1_calculated",
        .message_dbc_name = "EEC5_Electronic_Engine_Control_5",
        .unit = "deg C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec5_electronic_engine_control_5__commanded_vgt_position,
        .message_id = MessageId::eec5_electronic_engine_control_5,
        .start_bit = 32,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.0025,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Commanded_VGT_Position",
        .cpp_name = "commanded_vgt_position",
        .message_dbc_name = "EEC5_Electronic_Engine_Control_5",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch,
        .message_id = MessageId::eec5_electronic_engine_control_5,
        .start_bit = 48,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "Engine_Variable_Geometry_Turboch",
        .cpp_name = "engine_variable_geometry_turboch",
        .message_dbc_name = "EEC5_Electronic_Engine_Control_5",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode,
        .message_id = MessageId::eec5_electronic_engine_control_5,
        .start_bit = 50,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "Engine_Fuel_Control_Control_Mode",
        .cpp_name = "engine_fuel_control_control_mode",
        .message_dbc_name = "EEC5_Electronic_Engine_Control_5",
        .unit = "",
        .choice_enum_name = "Eec5ElectronicEngineControl5EngineFuelControlControlModeState",
    },
    SignalMeta{
        .id = SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode,
        .message_id = MessageId::eec5_electronic_engine_control_5,
        .start_bit = 52,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "Engine_VGT_Control_Mode",
        .cpp_name = "engine_vgt_control_mode",
        .message_dbc_name = "EEC5_Electronic_Engine_Control_5",
        .unit = "",
        .choice_enum_name = "Eec5ElectronicEngineControl5EngineVgtControlModeState",
    },
    SignalMeta{
        .id = SignalId::eec5_electronic_engine_control_5__actual_vgt_position,
        .message_id = MessageId::eec5_electronic_engine_control_5,
        .start_bit = 56,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Actual_VGT_Position",
        .cpp_name = "actual_vgt_position",
        .message_dbc_name = "EEC5_Electronic_Engine_Control_5",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec9_electronic_engine_control_9__engine_exhaust_gas_recirculation,
        .message_id = MessageId::eec9_electronic_engine_control_9,
        .start_bit = 0,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.0025,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Exhaust_Gas_Recirculation",
        .cpp_name = "engine_exhaust_gas_recirculation",
        .message_dbc_name = "EEC9_Electronic_Engine_Control_9",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure,
        .message_id = MessageId::eec9_electronic_engine_control_9,
        .start_bit = 32,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.00390625,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Commanded_Fuel_Rail_Pressure",
        .cpp_name = "commanded_fuel_rail_pressure",
        .message_dbc_name = "EEC9_Electronic_Engine_Control_9",
        .unit = "Mpa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec9_electronic_engine_control_9__commanded_engine_fuel_injection,
        .message_id = MessageId::eec9_electronic_engine_control_9,
        .start_bit = 48,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.00390625,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Commanded_Engine_Fuel_Injection_",
        .cpp_name = "commanded_engine_fuel_injection",
        .message_dbc_name = "EEC9_Electronic_Engine_Control_9",
        .unit = "Mpa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure,
        .message_id = MessageId::ebcc_engine_exhaust_brake_cont,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 2.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "Actual_Boost_Pressure",
        .cpp_name = "actual_boost_pressure",
        .message_dbc_name = "EBCC_Engine_Exhaust_Brake_Cont",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure,
        .message_id = MessageId::ebcc_engine_exhaust_brake_cont,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 2.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "Desired_Boost_Pressure",
        .cpp_name = "desired_boost_pressure",
        .message_dbc_name = "EBCC_Engine_Exhaust_Brake_Cont",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ebcc_engine_exhaust_brake_cont__engine_exhaust_brake_actuator_co,
        .message_id = MessageId::ebcc_engine_exhaust_brake_cont,
        .start_bit = 16,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Exhaust_Brake_Actuator_Co",
        .cpp_name = "engine_exhaust_brake_actuator_co",
        .message_dbc_name = "EBCC_Engine_Exhaust_Brake_Cont",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou,
        .message_id = MessageId::ebcc_engine_exhaust_brake_cont,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 2.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "Engine_Turbocharger_2_Turbine_Ou",
        .cpp_name = "engine_turbocharger_2_turbine_ou",
        .message_dbc_name = "EBCC_Engine_Exhaust_Brake_Cont",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu,
        .message_id = MessageId::ebcc_engine_exhaust_brake_cont,
        .start_bit = 32,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 2.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "Desired_Engine_Turbocharger_2_Tu",
        .cpp_name = "desired_engine_turbocharger_2_tu",
        .message_dbc_name = "EBCC_Engine_Exhaust_Brake_Cont",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::et3_engine_temperature_3__engine_intake_manifold_1_air_tem,
        .message_id = MessageId::et3_engine_temperature_3,
        .start_bit = 0,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Intake_Manifold_1_Air_Tem",
        .cpp_name = "engine_intake_manifold_1_air_tem",
        .message_dbc_name = "ET3_Engine_Temperature_3",
        .unit = "deg C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::et3_engine_temperature_3__engine_coolant_temperature_high,
        .message_id = MessageId::et3_engine_temperature_3,
        .start_bit = 16,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Coolant_Temperature__High",
        .cpp_name = "engine_coolant_temperature_high",
        .message_dbc_name = "ET3_Engine_Temperature_3",
        .unit = "deg C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::et3_engine_temperature_3__engine_intake_valve_actuation_sy,
        .message_id = MessageId::et3_engine_temperature_3,
        .start_bit = 32,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Intake_Valve_Actuation_Sy",
        .cpp_name = "engine_intake_valve_actuation_sy",
        .message_dbc_name = "ET3_Engine_Temperature_3",
        .unit = "deg C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::et3_engine_temperature_3__engine_cac_outlet_temperature,
        .message_id = MessageId::et3_engine_temperature_3,
        .start_bit = 48,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_CAC_Outlet_Temperature",
        .cpp_name = "engine_cac_outlet_temperature",
        .message_dbc_name = "ET3_Engine_Temperature_3",
        .unit = "deg C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on,
        .message_id = MessageId::dm21_diagnostic_readiness_2,
        .start_bit = 32,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "Engine_Run_Time_With_MIL_On",
        .cpp_name = "engine_run_time_with_mil_on",
        .message_dbc_name = "DM21_Diagnostic_Readiness_2",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::dm26_diagnostic_readiness_3__time_since_engine_start,
        .message_id = MessageId::dm26_diagnostic_readiness_3,
        .start_bit = 0,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "Time_Since_Engine_Start",
        .cpp_name = "time_since_engine_start",
        .message_dbc_name = "DM26_Diagnostic_Readiness_3",
        .unit = "s",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ic1_intake_exhaust_cond_1__aft1dpfinpress,
        .message_id = MessageId::ic1_intake_exhaust_cond_1,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.5,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "AFT1DPFInPress",
        .cpp_name = "aft1dpfinpress",
        .message_dbc_name = "IC1_Intake_Exhaust_Cond_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press,
        .message_id = MessageId::ic1_intake_exhaust_cond_1,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 2.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "EngIntakeManifold1Press",
        .cpp_name = "engintakemanifold1press",
        .message_dbc_name = "IC1_Intake_Exhaust_Cond_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp,
        .message_id = MessageId::ic1_intake_exhaust_cond_1,
        .start_bit = 16,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -40.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngIntakeManifold1Temp",
        .cpp_name = "engintakemanifold1temp",
        .message_dbc_name = "IC1_Intake_Exhaust_Cond_1",
        .unit = "ï¿½C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ic1_intake_exhaust_cond_1__engairintakepress,
        .message_id = MessageId::ic1_intake_exhaust_cond_1,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 2.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "EngAirIntakePress",
        .cpp_name = "engairintakepress",
        .message_dbc_name = "IC1_Intake_Exhaust_Cond_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ic1_intake_exhaust_cond_1__engairfilter1diffpress,
        .message_id = MessageId::ic1_intake_exhaust_cond_1,
        .start_bit = 32,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.05,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngAirFilter1DiffPress",
        .cpp_name = "engairfilter1diffpress",
        .message_dbc_name = "IC1_Intake_Exhaust_Cond_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ic1_intake_exhaust_cond_1__engexhaustgastemp,
        .message_id = MessageId::ic1_intake_exhaust_cond_1,
        .start_bit = 40,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngExhaustGasTemp",
        .cpp_name = "engexhaustgastemp",
        .message_dbc_name = "IC1_Intake_Exhaust_Cond_1",
        .unit = "ï¿½C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ic1_intake_exhaust_cond_1__engcoolantfilterdiffpress,
        .message_id = MessageId::ic1_intake_exhaust_cond_1,
        .start_bit = 56,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.5,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngCoolantFilterDiffPress",
        .cpp_name = "engcoolantfilterdiffpress",
        .message_dbc_name = "IC1_Intake_Exhaust_Cond_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::amb_ambient_conditions__barometric_pressurebarometric_pr,
        .message_id = MessageId::amb_ambient_conditions,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.5,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Barometric_PressureBarometric_Pr",
        .cpp_name = "barometric_pressurebarometric_pr",
        .message_dbc_name = "AMB_Ambient_Conditions",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::amb_ambient_conditions__cabinteriortemp,
        .message_id = MessageId::amb_ambient_conditions,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "CabInteriorTemp",
        .cpp_name = "cabinteriortemp",
        .message_dbc_name = "AMB_Ambient_Conditions",
        .unit = "ï¿½C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::amb_ambient_conditions__ambient_air_temperature,
        .message_id = MessageId::amb_ambient_conditions,
        .start_bit = 24,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Ambient_Air_Temperature",
        .cpp_name = "ambient_air_temperature",
        .message_dbc_name = "AMB_Ambient_Conditions",
        .unit = "ï¿½C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::amb_ambient_conditions__engine_air_intake_temperature,
        .message_id = MessageId::amb_ambient_conditions,
        .start_bit = 40,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -40.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Air_Intake_Temperature",
        .cpp_name = "engine_air_intake_temperature",
        .message_dbc_name = "AMB_Ambient_Conditions",
        .unit = "ï¿½C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::amb_ambient_conditions__roadsurfacetemp,
        .message_id = MessageId::amb_ambient_conditions,
        .start_bit = 48,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "RoadSurfaceTemp",
        .cpp_name = "roadsurfacetemp",
        .message_dbc_name = "AMB_Ambient_Conditions",
        .unit = "ï¿½C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec1_electronic_engine_control_1__engine_torque_mode,
        .message_id = MessageId::eec1_electronic_engine_control_1,
        .start_bit = 0,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "Engine_Torque_Mode",
        .cpp_name = "engine_torque_mode",
        .message_dbc_name = "EEC1_Electronic_Engine_Control_1",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution,
        .message_id = MessageId::eec1_electronic_engine_control_1,
        .start_bit = 4,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.125,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ActlEngPrcntTorqueHighResolution",
        .cpp_name = "actlengprcnttorquehighresolution",
        .message_dbc_name = "EEC1_Electronic_Engine_Control_1",
        .unit = "%",
        .choice_enum_name = "Eec1ElectronicEngineControl1ActlengprcnttorquehighresolutionState",
    },
    SignalMeta{
        .id = SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq,
        .message_id = MessageId::eec1_electronic_engine_control_1,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Drivers_Demand_Engine_Prcnt_Torq",
        .cpp_name = "drivers_demand_engine_prcnt_torq",
        .message_dbc_name = "EEC1_Electronic_Engine_Control_1",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque,
        .message_id = MessageId::eec1_electronic_engine_control_1,
        .start_bit = 16,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Actual_Engine_Percent_Torque",
        .cpp_name = "actual_engine_percent_torque",
        .message_dbc_name = "EEC1_Electronic_Engine_Control_1",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec1_electronic_engine_control_1__engine_speed,
        .message_id = MessageId::eec1_electronic_engine_control_1,
        .start_bit = 24,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.125,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Speed",
        .cpp_name = "engine_speed",
        .message_dbc_name = "EEC1_Electronic_Engine_Control_1",
        .unit = "rpm",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl,
        .message_id = MessageId::eec1_electronic_engine_control_1,
        .start_bit = 40,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "SrcAddrssOfCntrllngDvcForEngCtrl",
        .cpp_name = "srcaddrssofcntrllngdvcforengctrl",
        .message_dbc_name = "EEC1_Electronic_Engine_Control_1",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec1_electronic_engine_control_1__engstartermode,
        .message_id = MessageId::eec1_electronic_engine_control_1,
        .start_bit = 48,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngStarterMode",
        .cpp_name = "engstartermode",
        .message_dbc_name = "EEC1_Electronic_Engine_Control_1",
        .unit = "",
        .choice_enum_name = "Eec1ElectronicEngineControl1EngstartermodeState",
    },
    SignalMeta{
        .id = SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque,
        .message_id = MessageId::eec1_electronic_engine_control_1,
        .start_bit = 56,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Demand_Percent_Torque",
        .cpp_name = "engine_demand_percent_torque",
        .message_dbc_name = "EEC1_Electronic_Engine_Control_1",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 0,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "AccelPedal1LowIdleSwitch",
        .cpp_name = "accelpedal1lowidleswitch",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "",
        .choice_enum_name = "Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 2,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "AccelPedalKickdownSwitch",
        .cpp_name = "accelpedalkickdownswitch",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "",
        .choice_enum_name = "Eec2ElectronicEngineControl2AccelpedalkickdownswitchState",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 4,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "RoadSpeedLimitStatus",
        .cpp_name = "roadspeedlimitstatus",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "",
        .choice_enum_name = "Eec2ElectronicEngineControl2RoadspeedlimitstatusState",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 6,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "AccelPedal2LowIdleSwitch",
        .cpp_name = "accelpedal2lowidleswitch",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "",
        .choice_enum_name = "Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__accelpedalpos1,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "AccelPedalPos1",
        .cpp_name = "accelpedalpos1",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 16,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "EngPercentLoadAtCurrentSpeed",
        .cpp_name = "engpercentloadatcurrentspeed",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "RemoteAccelPedalPos",
        .cpp_name = "remoteaccelpedalpos",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__accelpedalpos2,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 32,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "AccelPedalPos2",
        .cpp_name = "accelpedalpos2",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 40,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "VhcleAccelerationRateLimitStatus",
        .cpp_name = "vhcleaccelerationratelimitstatus",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "",
        .choice_enum_name = "Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 42,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "MmntaryEngMaxPowerEnableFeedback",
        .cpp_name = "mmntaryengmaxpowerenablefeedback",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "",
        .choice_enum_name = "Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 44,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "DPFThermalManagementActive",
        .cpp_name = "dpfthermalmanagementactive",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "",
        .choice_enum_name = "Eec2ElectronicEngineControl2DpfthermalmanagementactiveState",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 46,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "SCRThermalManagementActive",
        .cpp_name = "scrthermalmanagementactive",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "",
        .choice_enum_name = "Eec2ElectronicEngineControl2ScrthermalmanagementactiveState",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__actlmaxavailableengpercenttorque,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 48,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "ActlMaxAvailableEngPercentTorque",
        .cpp_name = "actlmaxavailableengpercenttorque",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque,
        .message_id = MessageId::eec2_electronic_engine_control_2,
        .start_bit = 56,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EstPumpingPercentTorque",
        .cpp_name = "estpumpingpercenttorque",
        .message_dbc_name = "EEC2_Electronic_Engine_Control_2",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque,
        .message_id = MessageId::eec3_electronic_engine_control_3,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "NominalFrictionPercentTorque",
        .cpp_name = "nominalfrictionpercenttorque",
        .message_dbc_name = "EEC3_Electronic_Engine_Control_3",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec3_electronic_engine_control_3__enginesdesiredoperatingspeed,
        .message_id = MessageId::eec3_electronic_engine_control_3,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.125,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EnginesDesiredOperatingSpeed",
        .cpp_name = "enginesdesiredoperatingspeed",
        .message_dbc_name = "EEC3_Electronic_Engine_Control_3",
        .unit = "rpm",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm,
        .message_id = MessageId::eec3_electronic_engine_control_3,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "EngnsDsrdOprtngSpdAsymmtryAdjstm",
        .cpp_name = "engnsdsrdoprtngspdasymmtryadjstm",
        .message_dbc_name = "EEC3_Electronic_Engine_Control_3",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque,
        .message_id = MessageId::eec3_electronic_engine_control_3,
        .start_bit = 32,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EstEngPrsiticLossesPercentTorque",
        .cpp_name = "estengprsiticlossespercenttorque",
        .message_dbc_name = "EEC3_Electronic_Engine_Control_3",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec3_electronic_engine_control_3__aft1exhgasmfr,
        .message_id = MessageId::eec3_electronic_engine_control_3,
        .start_bit = 40,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.2,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "AFT1ExhGasMFR",
        .cpp_name = "aft1exhgasmfr",
        .message_dbc_name = "EEC3_Electronic_Engine_Control_3",
        .unit = "kg/h",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec3_electronic_engine_control_3__aft1indewpoint,
        .message_id = MessageId::eec3_electronic_engine_control_3,
        .start_bit = 56,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "AFT1InDewPoint",
        .cpp_name = "aft1indewpoint",
        .message_dbc_name = "EEC3_Electronic_Engine_Control_3",
        .unit = "",
        .choice_enum_name = "Eec3ElectronicEngineControl3Aft1indewpointState",
    },
    SignalMeta{
        .id = SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint,
        .message_id = MessageId::eec3_electronic_engine_control_3,
        .start_bit = 58,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "AFT1ExhDewPoint",
        .cpp_name = "aft1exhdewpoint",
        .message_dbc_name = "EEC3_Electronic_Engine_Control_3",
        .unit = "",
        .choice_enum_name = "Eec3ElectronicEngineControl3Aft1exhdewpointState",
    },
    SignalMeta{
        .id = SignalId::eec3_electronic_engine_control_3__aft2indewpoint,
        .message_id = MessageId::eec3_electronic_engine_control_3,
        .start_bit = 60,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "AFT2InDewPoint",
        .cpp_name = "aft2indewpoint",
        .message_dbc_name = "EEC3_Electronic_Engine_Control_3",
        .unit = "",
        .choice_enum_name = "Eec3ElectronicEngineControl3Aft2indewpointState",
    },
    SignalMeta{
        .id = SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint,
        .message_id = MessageId::eec3_electronic_engine_control_3,
        .start_bit = 62,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "AFT2ExhDewPoint",
        .cpp_name = "aft2exhdewpoint",
        .message_dbc_name = "EEC3_Electronic_Engine_Control_3",
        .unit = "",
        .choice_enum_name = "Eec3ElectronicEngineControl3Aft2exhdewpointState",
    },
    SignalMeta{
        .id = SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress,
        .message_id = MessageId::efl_p1_eng_fluid_level_press_1,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 4.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "EngFuelDeliveryPress",
        .cpp_name = "engfueldeliverypress",
        .message_dbc_name = "EFL_P1_Eng_Fluid_Level_Press_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::efl_p1_eng_fluid_level_press_1__engexcrankcaseblowbypress,
        .message_id = MessageId::efl_p1_eng_fluid_level_press_1,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.05,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngExCrankcaseBlowbyPress",
        .cpp_name = "engexcrankcaseblowbypress",
        .message_dbc_name = "EFL_P1_Eng_Fluid_Level_Press_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::efl_p1_eng_fluid_level_press_1__engoillevel,
        .message_id = MessageId::efl_p1_eng_fluid_level_press_1,
        .start_bit = 16,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngOilLevel",
        .cpp_name = "engoillevel",
        .message_dbc_name = "EFL_P1_Eng_Fluid_Level_Press_1",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::efl_p1_eng_fluid_level_press_1__engoilpress,
        .message_id = MessageId::efl_p1_eng_fluid_level_press_1,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 4.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "EngOilPress",
        .cpp_name = "engoilpress",
        .message_dbc_name = "EFL_P1_Eng_Fluid_Level_Press_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::efl_p1_eng_fluid_level_press_1__engcrankcasepress,
        .message_id = MessageId::efl_p1_eng_fluid_level_press_1,
        .start_bit = 32,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.0078125,
        .offset = -250.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngCrankcasePress",
        .cpp_name = "engcrankcasepress",
        .message_dbc_name = "EFL_P1_Eng_Fluid_Level_Press_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress,
        .message_id = MessageId::efl_p1_eng_fluid_level_press_1,
        .start_bit = 48,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 2.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "EngCoolantPress",
        .cpp_name = "engcoolantpress",
        .message_dbc_name = "EFL_P1_Eng_Fluid_Level_Press_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::efl_p1_eng_fluid_level_press_1__engcoolantlevel,
        .message_id = MessageId::efl_p1_eng_fluid_level_press_1,
        .start_bit = 56,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngCoolantLevel",
        .cpp_name = "engcoolantlevel",
        .message_dbc_name = "EFL_P1_Eng_Fluid_Level_Press_1",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectionctrlpress,
        .message_id = MessageId::efl_p2_eng_fluid_level_press_2,
        .start_bit = 0,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.00390625,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngInjectionCtrlPress",
        .cpp_name = "enginjectionctrlpress",
        .message_dbc_name = "EFL_P2_Eng_Fluid_Level_Press_2",
        .unit = "MPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail1press,
        .message_id = MessageId::efl_p2_eng_fluid_level_press_2,
        .start_bit = 16,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.00390625,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngInjectorMeteringRail1Press",
        .cpp_name = "enginjectormeteringrail1press",
        .message_dbc_name = "EFL_P2_Eng_Fluid_Level_Press_2",
        .unit = "MPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectortimingrail1press,
        .message_id = MessageId::efl_p2_eng_fluid_level_press_2,
        .start_bit = 32,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.00390625,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngInjectorTimingRail1Press",
        .cpp_name = "enginjectortimingrail1press",
        .message_dbc_name = "EFL_P2_Eng_Fluid_Level_Press_2",
        .unit = "MPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail2press,
        .message_id = MessageId::efl_p2_eng_fluid_level_press_2,
        .start_bit = 48,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.00390625,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngInjectorMeteringRail2Press",
        .cpp_name = "enginjectormeteringrail2press",
        .message_dbc_name = "EFL_P2_Eng_Fluid_Level_Press_2",
        .unit = "MPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::et1_engine_temperature_1__engcoolanttemp,
        .message_id = MessageId::et1_engine_temperature_1,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -40.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngCoolantTemp",
        .cpp_name = "engcoolanttemp",
        .message_dbc_name = "ET1_Engine_Temperature_1",
        .unit = "ï¿½C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::et1_engine_temperature_1__engfueltemp1,
        .message_id = MessageId::et1_engine_temperature_1,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -40.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngFuelTemp1",
        .cpp_name = "engfueltemp1",
        .message_dbc_name = "ET1_Engine_Temperature_1",
        .unit = "ï¿½C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::et1_engine_temperature_1__engoiltemp1,
        .message_id = MessageId::et1_engine_temperature_1,
        .start_bit = 16,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngOilTemp1",
        .cpp_name = "engoiltemp1",
        .message_dbc_name = "ET1_Engine_Temperature_1",
        .unit = "ï¿½C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::et1_engine_temperature_1__engturbooiltemp,
        .message_id = MessageId::et1_engine_temperature_1,
        .start_bit = 32,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngTurboOilTemp",
        .cpp_name = "engturbooiltemp",
        .message_dbc_name = "ET1_Engine_Temperature_1",
        .unit = "ï¿½C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::et1_engine_temperature_1__engintercoolertemp,
        .message_id = MessageId::et1_engine_temperature_1,
        .start_bit = 48,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -40.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngIntercoolerTemp",
        .cpp_name = "engintercoolertemp",
        .message_dbc_name = "ET1_Engine_Temperature_1",
        .unit = "ï¿½C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::et1_engine_temperature_1__engintercoolerthermostatopening,
        .message_id = MessageId::et1_engine_temperature_1,
        .start_bit = 56,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngIntercoolerThermostatOpening",
        .cpp_name = "engintercoolerthermostatopening",
        .message_dbc_name = "ET1_Engine_Temperature_1",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::lfe1_fuel_economy_liquid_1__engfuelrate,
        .message_id = MessageId::lfe1_fuel_economy_liquid_1,
        .start_bit = 0,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.05,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngFuelRate",
        .cpp_name = "engfuelrate",
        .message_dbc_name = "LFE1_Fuel_Economy_Liquid_1",
        .unit = "l/h",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::lfe1_fuel_economy_liquid_1__enginstantaneousfueleconomy,
        .message_id = MessageId::lfe1_fuel_economy_liquid_1,
        .start_bit = 16,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.00195312,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngInstantaneousFuelEconomy",
        .cpp_name = "enginstantaneousfueleconomy",
        .message_dbc_name = "LFE1_Fuel_Economy_Liquid_1",
        .unit = "km/L",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::lfe1_fuel_economy_liquid_1__engaveragefueleconomy,
        .message_id = MessageId::lfe1_fuel_economy_liquid_1,
        .start_bit = 32,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.00195312,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngAverageFuelEconomy",
        .cpp_name = "engaveragefueleconomy",
        .message_dbc_name = "LFE1_Fuel_Economy_Liquid_1",
        .unit = "km/L",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve1pos,
        .message_id = MessageId::lfe1_fuel_economy_liquid_1,
        .start_bit = 48,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngThrottleValve1Pos",
        .cpp_name = "engthrottlevalve1pos",
        .message_dbc_name = "LFE1_Fuel_Economy_Liquid_1",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve2pos,
        .message_id = MessageId::lfe1_fuel_economy_liquid_1,
        .start_bit = 56,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngThrottleValve2Pos",
        .cpp_name = "engthrottlevalve2pos",
        .message_dbc_name = "LFE1_Fuel_Economy_Liquid_1",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_header__controlbyte,
        .message_id = MessageId::transportprotocol_header,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ControlByte",
        .cpp_name = "controlbyte",
        .message_dbc_name = "TransportProtocol_Header",
        .unit = "",
        .choice_enum_name = "TransportprotocolHeaderControlbyteState",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_header__totalmessagesizeeoma,
        .message_id = MessageId::transportprotocol_header,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "TotalMessageSizeEoMA",
        .cpp_name = "totalmessagesizeeoma",
        .message_dbc_name = "TransportProtocol_Header",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_header__connectionabortreason,
        .message_id = MessageId::transportprotocol_header,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ConnectionAbortReason",
        .cpp_name = "connectionabortreason",
        .message_dbc_name = "TransportProtocol_Header",
        .unit = "",
        .choice_enum_name = "TransportprotocolHeaderConnectionabortreasonState",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_header__totalmessagesize,
        .message_id = MessageId::transportprotocol_header,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "TotalMessageSize",
        .cpp_name = "totalmessagesize",
        .message_dbc_name = "TransportProtocol_Header",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_header__numberofpacketsthatcanbesent,
        .message_id = MessageId::transportprotocol_header,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "NumberOfPacketsThatCanBeSent",
        .cpp_name = "numberofpacketsthatcanbesent",
        .message_dbc_name = "TransportProtocol_Header",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_header__totalmessagesizebam,
        .message_id = MessageId::transportprotocol_header,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "TotalMessageSizeBAM",
        .cpp_name = "totalmessagesizebam",
        .message_dbc_name = "TransportProtocol_Header",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_header__nextpacketnumbertobesent,
        .message_id = MessageId::transportprotocol_header,
        .start_bit = 16,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "NextPacketNumberToBeSent",
        .cpp_name = "nextpacketnumbertobesent",
        .message_dbc_name = "TransportProtocol_Header",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_header__totalnumberofpackets,
        .message_id = MessageId::transportprotocol_header,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "TotalNumberOfPackets",
        .cpp_name = "totalnumberofpackets",
        .message_dbc_name = "TransportProtocol_Header",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_header__totalnumberofpacketseoma,
        .message_id = MessageId::transportprotocol_header,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "TotalNumberOfPacketsEoMA",
        .cpp_name = "totalnumberofpacketseoma",
        .message_dbc_name = "TransportProtocol_Header",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_header__totalnumberofpacketsbam,
        .message_id = MessageId::transportprotocol_header,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "TotalNumberOfPacketsBAM",
        .cpp_name = "totalnumberofpacketsbam",
        .message_dbc_name = "TransportProtocol_Header",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_header__maximumnumberofpackets,
        .message_id = MessageId::transportprotocol_header,
        .start_bit = 32,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "MaximumNumberOfPackets",
        .cpp_name = "maximumnumberofpackets",
        .message_dbc_name = "TransportProtocol_Header",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_header__pgnumber,
        .message_id = MessageId::transportprotocol_header,
        .start_bit = 40,
        .bit_length = 24,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u32,
        .has_choices = true,
        .dbc_name = "PGNumber",
        .cpp_name = "pgnumber",
        .message_dbc_name = "TransportProtocol_Header",
        .unit = "",
        .choice_enum_name = "TransportprotocolHeaderPgnumberState",
    },
    SignalMeta{
        .id = SignalId::transportprotocol_data__sequencenumber,
        .message_id = MessageId::transportprotocol_data,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "SequenceNumber",
        .cpp_name = "sequencenumber",
        .message_dbc_name = "TransportProtocol_Data",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::dm01_active_diagnostics__protectlampstatus,
        .message_id = MessageId::dm01_active_diagnostics,
        .start_bit = 0,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ProtectLampStatus",
        .cpp_name = "protectlampstatus",
        .message_dbc_name = "DM01_Active_Diagnostics",
        .unit = "",
        .choice_enum_name = "Dm01ActiveDiagnosticsProtectlampstatusState",
    },
    SignalMeta{
        .id = SignalId::dm01_active_diagnostics__amberwarninglampstatus,
        .message_id = MessageId::dm01_active_diagnostics,
        .start_bit = 2,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "AmberWarningLampStatus",
        .cpp_name = "amberwarninglampstatus",
        .message_dbc_name = "DM01_Active_Diagnostics",
        .unit = "",
        .choice_enum_name = "Dm01ActiveDiagnosticsAmberwarninglampstatusState",
    },
    SignalMeta{
        .id = SignalId::dm01_active_diagnostics__redstoplampstate,
        .message_id = MessageId::dm01_active_diagnostics,
        .start_bit = 4,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "RedStopLampState",
        .cpp_name = "redstoplampstate",
        .message_dbc_name = "DM01_Active_Diagnostics",
        .unit = "",
        .choice_enum_name = "Dm01ActiveDiagnosticsRedstoplampstateState",
    },
    SignalMeta{
        .id = SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus,
        .message_id = MessageId::dm01_active_diagnostics,
        .start_bit = 6,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "MalfunctionIndicatorLampStatus",
        .cpp_name = "malfunctionindicatorlampstatus",
        .message_dbc_name = "DM01_Active_Diagnostics",
        .unit = "",
        .choice_enum_name = "Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState",
    },
    SignalMeta{
        .id = SignalId::dm01_active_diagnostics__flashprotectlamp,
        .message_id = MessageId::dm01_active_diagnostics,
        .start_bit = 8,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "FlashProtectLamp",
        .cpp_name = "flashprotectlamp",
        .message_dbc_name = "DM01_Active_Diagnostics",
        .unit = "",
        .choice_enum_name = "Dm01ActiveDiagnosticsFlashprotectlampState",
    },
    SignalMeta{
        .id = SignalId::dm01_active_diagnostics__flashamberwarninglamp,
        .message_id = MessageId::dm01_active_diagnostics,
        .start_bit = 10,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "FlashAmberWarningLamp",
        .cpp_name = "flashamberwarninglamp",
        .message_dbc_name = "DM01_Active_Diagnostics",
        .unit = "",
        .choice_enum_name = "Dm01ActiveDiagnosticsFlashamberwarninglampState",
    },
    SignalMeta{
        .id = SignalId::dm01_active_diagnostics__flashredstoplamp,
        .message_id = MessageId::dm01_active_diagnostics,
        .start_bit = 12,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "FlashRedStopLamp",
        .cpp_name = "flashredstoplamp",
        .message_dbc_name = "DM01_Active_Diagnostics",
        .unit = "",
        .choice_enum_name = "Dm01ActiveDiagnosticsFlashredstoplampState",
    },
    SignalMeta{
        .id = SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp,
        .message_id = MessageId::dm01_active_diagnostics,
        .start_bit = 14,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "FlashMalfuncIndicatorLamp",
        .cpp_name = "flashmalfuncindicatorlamp",
        .message_dbc_name = "DM01_Active_Diagnostics",
        .unit = "",
        .choice_enum_name = "Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState",
    },
    SignalMeta{
        .id = SignalId::dm01_active_diagnostics__dtc1,
        .message_id = MessageId::dm01_active_diagnostics,
        .start_bit = 16,
        .bit_length = 32,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u32,
        .has_choices = false,
        .dbc_name = "DTC1",
        .cpp_name = "dtc1",
        .message_dbc_name = "DM01_Active_Diagnostics",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tsc1_31__engoverridectrlmode,
        .message_id = MessageId::tsc1_31,
        .start_bit = 0,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngOverrideCtrlMode",
        .cpp_name = "engoverridectrlmode",
        .message_dbc_name = "TSC1_31",
        .unit = "",
        .choice_enum_name = "Tsc131EngoverridectrlmodeState",
    },
    SignalMeta{
        .id = SignalId::tsc1_31__engrequestedspeedctrlconditions,
        .message_id = MessageId::tsc1_31,
        .start_bit = 2,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngRequestedSpeedCtrlConditions",
        .cpp_name = "engrequestedspeedctrlconditions",
        .message_dbc_name = "TSC1_31",
        .unit = "",
        .choice_enum_name = "Tsc131EngrequestedspeedctrlconditionsState",
    },
    SignalMeta{
        .id = SignalId::tsc1_31__overridectrlmodepriority,
        .message_id = MessageId::tsc1_31,
        .start_bit = 4,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "OverrideCtrlModePriority",
        .cpp_name = "overridectrlmodepriority",
        .message_dbc_name = "TSC1_31",
        .unit = "",
        .choice_enum_name = "Tsc131OverridectrlmodepriorityState",
    },
    SignalMeta{
        .id = SignalId::tsc1_31__engrequestedspeed_speedlimit,
        .message_id = MessageId::tsc1_31,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.125,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngRequestedSpeed_SpeedLimit",
        .cpp_name = "engrequestedspeed_speedlimit",
        .message_dbc_name = "TSC1_31",
        .unit = "rpm",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tsc1_31__engrequestedtorque_torquelimit,
        .message_id = MessageId::tsc1_31,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngRequestedTorque_TorqueLimit",
        .cpp_name = "engrequestedtorque_torquelimit",
        .message_dbc_name = "TSC1_31",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tsc1_31__tsc1transrate,
        .message_id = MessageId::tsc1_31,
        .start_bit = 32,
        .bit_length = 3,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TSC1TransRate",
        .cpp_name = "tsc1transrate",
        .message_dbc_name = "TSC1_31",
        .unit = "",
        .choice_enum_name = "Tsc131Tsc1transrateState",
    },
    SignalMeta{
        .id = SignalId::tsc1_31__tsc1ctrlpurpose,
        .message_id = MessageId::tsc1_31,
        .start_bit = 35,
        .bit_length = 5,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TSC1CtrlPurpose",
        .cpp_name = "tsc1ctrlpurpose",
        .message_dbc_name = "TSC1_31",
        .unit = "",
        .choice_enum_name = "Tsc131Tsc1ctrlpurposeState",
    },
    SignalMeta{
        .id = SignalId::tsc1_31__engrequestedtorquehighresolution,
        .message_id = MessageId::tsc1_31,
        .start_bit = 40,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.125,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngRequestedTorqueHighResolution",
        .cpp_name = "engrequestedtorquehighresolution",
        .message_dbc_name = "TSC1_31",
        .unit = "%",
        .choice_enum_name = "Tsc131EngrequestedtorquehighresolutionState",
    },
    SignalMeta{
        .id = SignalId::tsc1_31__messagecounter,
        .message_id = MessageId::tsc1_31,
        .start_bit = 56,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "MessageCounter",
        .cpp_name = "messagecounter",
        .message_dbc_name = "TSC1_31",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tsc1_31__messagechecksum,
        .message_id = MessageId::tsc1_31,
        .start_bit = 60,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "MessageChecksum",
        .cpp_name = "messagechecksum",
        .message_dbc_name = "TSC1_31",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_intak,
        .message_id = MessageId::cac1_charge_air_cooler_1,
        .start_bit = 0,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Charge_Air_Cooler_1_Intak",
        .cpp_name = "engine_charge_air_cooler_1_intak",
        .message_dbc_name = "CAC1_Charge_Air_Cooler_1",
        .unit = "deg C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie,
        .message_id = MessageId::cac1_charge_air_cooler_1,
        .start_bit = 16,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Charge_Air_Cooler_1_Ambie",
        .cpp_name = "engine_charge_air_cooler_1_ambie",
        .message_dbc_name = "CAC1_Charge_Air_Cooler_1",
        .unit = "deg C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_effic,
        .message_id = MessageId::cac1_charge_air_cooler_1,
        .start_bit = 32,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Charge_Air_Cooler_1_Effic",
        .cpp_name = "engine_charge_air_cooler_1_effic",
        .message_dbc_name = "CAC1_Charge_Air_Cooler_1",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::hours_engine_hours_revolutions__engine_total_hours_of_operation,
        .message_id = MessageId::hours_engine_hours_revolutions,
        .start_bit = 0,
        .bit_length = 32,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.05,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Total_Hours_of_Operation_",
        .cpp_name = "engine_total_hours_of_operation",
        .message_dbc_name = "HOURS_Engine_Hours_Revolutions",
        .unit = "hr",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::hours_engine_hours_revolutions__engine_total_revolutions_249,
        .message_id = MessageId::hours_engine_hours_revolutions,
        .start_bit = 32,
        .bit_length = 32,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1000.0,
        .offset = 0.0,
        .type = SignalType::u32,
        .has_choices = false,
        .dbc_name = "Engine_Total_Revolutions__249_",
        .cpp_name = "engine_total_revolutions_249",
        .message_dbc_name = "HOURS_Engine_Hours_Revolutions",
        .unit = "r",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou,
        .message_id = MessageId::tci5_turbocharger_information_5,
        .start_bit = 0,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Turbocharger_1_Turbine_Ou",
        .cpp_name = "engine_turbocharger_1_turbine_ou",
        .message_dbc_name = "TCI5_Turbocharger_Information_5",
        .unit = "deg C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_2_turbine_ou,
        .message_id = MessageId::tci5_turbocharger_information_5,
        .start_bit = 16,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Turbocharger_2_Turbine_Ou",
        .cpp_name = "engine_turbocharger_2_turbine_ou",
        .message_dbc_name = "TCI5_Turbocharger_Information_5",
        .unit = "deg C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_3_turbine_ou,
        .message_id = MessageId::tci5_turbocharger_information_5,
        .start_bit = 32,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Turbocharger_3_Turbine_Ou",
        .cpp_name = "engine_turbocharger_3_turbine_ou",
        .message_dbc_name = "TCI5_Turbocharger_Information_5",
        .unit = "deg C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_4_turbine_ou,
        .message_id = MessageId::tci5_turbocharger_information_5,
        .start_bit = 48,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Turbocharger_4_Turbine_Ou",
        .cpp_name = "engine_turbocharger_4_turbine_ou",
        .message_dbc_name = "TCI5_Turbocharger_Information_5",
        .unit = "deg C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114,
        .message_id = MessageId::vep1_vehicle_electrical_power_1,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Net_Battery_Current__114_",
        .cpp_name = "net_battery_current_114",
        .message_dbc_name = "VEP1_Vehicle_Electrical_Power_1",
        .unit = "A",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::vep1_vehicle_electrical_power_1__alternator_current_115,
        .message_id = MessageId::vep1_vehicle_electrical_power_1,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "Alternator_Current__115_",
        .cpp_name = "alternator_current_115",
        .message_dbc_name = "VEP1_Vehicle_Electrical_Power_1",
        .unit = "A",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::vep1_vehicle_electrical_power_1__charging_system_potential_volta,
        .message_id = MessageId::vep1_vehicle_electrical_power_1,
        .start_bit = 16,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.05,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Charging_System_Potential__Volta",
        .cpp_name = "charging_system_potential_volta",
        .message_dbc_name = "VEP1_Vehicle_Electrical_Power_1",
        .unit = "V",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::vep1_vehicle_electrical_power_1__battery_potential_power_input_1,
        .message_id = MessageId::vep1_vehicle_electrical_power_1,
        .start_bit = 32,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.05,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Battery_Potential_Power_Input_1_",
        .cpp_name = "battery_potential_power_input_1",
        .message_dbc_name = "VEP1_Vehicle_Electrical_Power_1",
        .unit = "V",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158,
        .message_id = MessageId::vep1_vehicle_electrical_power_1,
        .start_bit = 48,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.05,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Keyswitch_Battery_Potential__158",
        .cpp_name = "keyswitch_battery_potential_158",
        .message_dbc_name = "VEP1_Vehicle_Electrical_Power_1",
        .unit = "V",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::eec20_electronic_engine_control__absolute_engine_load,
        .message_id = MessageId::eec20_electronic_engine_control,
        .start_bit = 40,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.025,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Absolute_Engine_Load",
        .cpp_name = "absolute_engine_load",
        .message_dbc_name = "EEC20_Electronic_Engine_Control_",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::easi_engine_air_system_info__engine_intake_maf,
        .message_id = MessageId::easi_engine_air_system_info,
        .start_bit = 16,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.000976562,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "Engine_Intake_MAF",
        .cpp_name = "engine_intake_maf",
        .message_dbc_name = "EASI_Engine_Air_System_Info",
        .unit = "kg/s",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tsc1_03__engoverridectrlmode,
        .message_id = MessageId::tsc1_03,
        .start_bit = 0,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngOverrideCtrlMode",
        .cpp_name = "engoverridectrlmode",
        .message_dbc_name = "TSC1_03",
        .unit = "",
        .choice_enum_name = "Tsc103EngoverridectrlmodeState",
    },
    SignalMeta{
        .id = SignalId::tsc1_03__engrequestedspeedctrlconditions,
        .message_id = MessageId::tsc1_03,
        .start_bit = 2,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngRequestedSpeedCtrlConditions",
        .cpp_name = "engrequestedspeedctrlconditions",
        .message_dbc_name = "TSC1_03",
        .unit = "",
        .choice_enum_name = "Tsc103EngrequestedspeedctrlconditionsState",
    },
    SignalMeta{
        .id = SignalId::tsc1_03__overridectrlmodepriority,
        .message_id = MessageId::tsc1_03,
        .start_bit = 4,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "OverrideCtrlModePriority",
        .cpp_name = "overridectrlmodepriority",
        .message_dbc_name = "TSC1_03",
        .unit = "",
        .choice_enum_name = "Tsc103OverridectrlmodepriorityState",
    },
    SignalMeta{
        .id = SignalId::tsc1_03__engrequestedspeed_speedlimit,
        .message_id = MessageId::tsc1_03,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.125,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngRequestedSpeed_SpeedLimit",
        .cpp_name = "engrequestedspeed_speedlimit",
        .message_dbc_name = "TSC1_03",
        .unit = "rpm",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tsc1_03__engrequestedtorque_torquelimit,
        .message_id = MessageId::tsc1_03,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngRequestedTorque_TorqueLimit",
        .cpp_name = "engrequestedtorque_torquelimit",
        .message_dbc_name = "TSC1_03",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tsc1_03__tsc1transrate,
        .message_id = MessageId::tsc1_03,
        .start_bit = 32,
        .bit_length = 3,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TSC1TransRate",
        .cpp_name = "tsc1transrate",
        .message_dbc_name = "TSC1_03",
        .unit = "",
        .choice_enum_name = "Tsc103Tsc1transrateState",
    },
    SignalMeta{
        .id = SignalId::tsc1_03__tsc1ctrlpurpose,
        .message_id = MessageId::tsc1_03,
        .start_bit = 35,
        .bit_length = 5,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TSC1CtrlPurpose",
        .cpp_name = "tsc1ctrlpurpose",
        .message_dbc_name = "TSC1_03",
        .unit = "",
        .choice_enum_name = "Tsc103Tsc1ctrlpurposeState",
    },
    SignalMeta{
        .id = SignalId::tsc1_03__engrequestedtorquehighresolution,
        .message_id = MessageId::tsc1_03,
        .start_bit = 40,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.125,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngRequestedTorqueHighResolution",
        .cpp_name = "engrequestedtorquehighresolution",
        .message_dbc_name = "TSC1_03",
        .unit = "%",
        .choice_enum_name = "Tsc103EngrequestedtorquehighresolutionState",
    },
    SignalMeta{
        .id = SignalId::tsc1_03__messagecounter,
        .message_id = MessageId::tsc1_03,
        .start_bit = 56,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "MessageCounter",
        .cpp_name = "messagecounter",
        .message_dbc_name = "TSC1_03",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tsc1_03__messagechecksum,
        .message_id = MessageId::tsc1_03,
        .start_bit = 60,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "MessageChecksum",
        .cpp_name = "messagechecksum",
        .message_dbc_name = "TSC1_03",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tsc1_0b__engoverridectrlmode,
        .message_id = MessageId::tsc1_0b,
        .start_bit = 0,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngOverrideCtrlMode",
        .cpp_name = "engoverridectrlmode",
        .message_dbc_name = "TSC1_0B",
        .unit = "",
        .choice_enum_name = "Tsc10bEngoverridectrlmodeState",
    },
    SignalMeta{
        .id = SignalId::tsc1_0b__engrequestedspeedctrlconditions,
        .message_id = MessageId::tsc1_0b,
        .start_bit = 2,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngRequestedSpeedCtrlConditions",
        .cpp_name = "engrequestedspeedctrlconditions",
        .message_dbc_name = "TSC1_0B",
        .unit = "",
        .choice_enum_name = "Tsc10bEngrequestedspeedctrlconditionsState",
    },
    SignalMeta{
        .id = SignalId::tsc1_0b__overridectrlmodepriority,
        .message_id = MessageId::tsc1_0b,
        .start_bit = 4,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "OverrideCtrlModePriority",
        .cpp_name = "overridectrlmodepriority",
        .message_dbc_name = "TSC1_0B",
        .unit = "",
        .choice_enum_name = "Tsc10bOverridectrlmodepriorityState",
    },
    SignalMeta{
        .id = SignalId::tsc1_0b__engrequestedspeed_speedlimit,
        .message_id = MessageId::tsc1_0b,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.125,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngRequestedSpeed_SpeedLimit",
        .cpp_name = "engrequestedspeed_speedlimit",
        .message_dbc_name = "TSC1_0B",
        .unit = "rpm",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tsc1_0b__engrequestedtorque_torquelimit,
        .message_id = MessageId::tsc1_0b,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngRequestedTorque_TorqueLimit",
        .cpp_name = "engrequestedtorque_torquelimit",
        .message_dbc_name = "TSC1_0B",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tsc1_0b__tsc1transrate,
        .message_id = MessageId::tsc1_0b,
        .start_bit = 32,
        .bit_length = 3,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TSC1TransRate",
        .cpp_name = "tsc1transrate",
        .message_dbc_name = "TSC1_0B",
        .unit = "",
        .choice_enum_name = "Tsc10bTsc1transrateState",
    },
    SignalMeta{
        .id = SignalId::tsc1_0b__tsc1ctrlpurpose,
        .message_id = MessageId::tsc1_0b,
        .start_bit = 35,
        .bit_length = 5,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TSC1CtrlPurpose",
        .cpp_name = "tsc1ctrlpurpose",
        .message_dbc_name = "TSC1_0B",
        .unit = "",
        .choice_enum_name = "Tsc10bTsc1ctrlpurposeState",
    },
    SignalMeta{
        .id = SignalId::tsc1_0b__engrequestedtorquehighresolution,
        .message_id = MessageId::tsc1_0b,
        .start_bit = 40,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.125,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngRequestedTorqueHighResolution",
        .cpp_name = "engrequestedtorquehighresolution",
        .message_dbc_name = "TSC1_0B",
        .unit = "%",
        .choice_enum_name = "Tsc10bEngrequestedtorquehighresolutionState",
    },
    SignalMeta{
        .id = SignalId::tsc1_0b__messagecounter,
        .message_id = MessageId::tsc1_0b,
        .start_bit = 56,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "MessageCounter",
        .cpp_name = "messagecounter",
        .message_dbc_name = "TSC1_0B",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tsc1_0b__messagechecksum,
        .message_id = MessageId::tsc1_0b,
        .start_bit = 60,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "MessageChecksum",
        .cpp_name = "messagechecksum",
        .message_dbc_name = "TSC1_0B",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::dm07__testidentifier,
        .message_id = MessageId::dm07,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TestIdentifier",
        .cpp_name = "testidentifier",
        .message_dbc_name = "DM07",
        .unit = "",
        .choice_enum_name = "Dm07TestidentifierState",
    },
    SignalMeta{
        .id = SignalId::dm07__spn1,
        .message_id = MessageId::dm07,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "SPN1",
        .cpp_name = "spn1",
        .message_dbc_name = "DM07",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::dm07__failuremodeidentifier1,
        .message_id = MessageId::dm07,
        .start_bit = 24,
        .bit_length = 5,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "FailureModeIdentifier1",
        .cpp_name = "failuremodeidentifier1",
        .message_dbc_name = "DM07",
        .unit = "",
        .choice_enum_name = "Dm07Failuremodeidentifier1State",
    },
    SignalMeta{
        .id = SignalId::dm07__spn1high,
        .message_id = MessageId::dm07,
        .start_bit = 29,
        .bit_length = 3,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "SPN1High",
        .cpp_name = "spn1high",
        .message_dbc_name = "DM07",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::dm08__testidentifier,
        .message_id = MessageId::dm08,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TestIdentifier",
        .cpp_name = "testidentifier",
        .message_dbc_name = "DM08",
        .unit = "",
        .choice_enum_name = "Dm08TestidentifierState",
    },
    SignalMeta{
        .id = SignalId::dm08__testtype,
        .message_id = MessageId::dm08,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "TestType",
        .cpp_name = "testtype",
        .message_dbc_name = "DM08",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::dm08__testvalue,
        .message_id = MessageId::dm08,
        .start_bit = 16,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "TestValue",
        .cpp_name = "testvalue",
        .message_dbc_name = "DM08",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::dm08__testlimitmaximum,
        .message_id = MessageId::dm08,
        .start_bit = 32,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "TestLimitMaximum",
        .cpp_name = "testlimitmaximum",
        .message_dbc_name = "DM08",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::dm08__testlimitminimum,
        .message_id = MessageId::dm08,
        .start_bit = 48,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "TestLimitMinimum",
        .cpp_name = "testlimitminimum",
        .message_dbc_name = "DM08",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__retardertorquemode,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 0,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "RetarderTorqueMode",
        .cpp_name = "retardertorquemode",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 4,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "RetarderEnableBrakeAssistSwitch",
        .cpp_name = "retarderenablebrakeassistswitch",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "",
        .choice_enum_name = "Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 6,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "RetarderEnableShiftAssistSwitch",
        .cpp_name = "retarderenableshiftassistswitch",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "",
        .choice_enum_name = "Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "ActualRetarderPercentTorque",
        .cpp_name = "actualretarderpercenttorque",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 16,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "IntendedRetarderPercentTorque",
        .cpp_name = "intendedretarderpercenttorque",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 24,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngCoolantLoadIncrease",
        .cpp_name = "engcoolantloadincrease",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "",
        .choice_enum_name = "Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 26,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "RetarderRequestingBrakeLight",
        .cpp_name = "retarderrequestingbrakelight",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "",
        .choice_enum_name = "Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 28,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "RetarderRoadSpeedLimitSwitch",
        .cpp_name = "retarderroadspeedlimitswitch",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "",
        .choice_enum_name = "Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 30,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "RetarderRoadSpeedExceededStatus",
        .cpp_name = "retarderroadspeedexceededstatus",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "",
        .choice_enum_name = "Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 32,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "SrcAddrssOfCntrllngDvcFrRtrdrCtr",
        .cpp_name = "srcaddrssofcntrllngdvcfrrtrdrctr",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 40,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "DrvrsDemandRetarderPercentTorque",
        .cpp_name = "drvrsdemandretarderpercenttorque",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__retarderselectionnonengine,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 48,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "RetarderSelectionNonengine",
        .cpp_name = "retarderselectionnonengine",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque,
        .message_id = MessageId::erc1_electronic_retarder_cntrl,
        .start_bit = 56,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "ActlMxAvlblRetarderPercentTorque",
        .cpp_name = "actlmxavlblretarderpercenttorque",
        .message_dbc_name = "ERC1_Electronic_Retarder_Cntrl",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged,
        .message_id = MessageId::etc1_electronic_trans_cntrl_1,
        .start_bit = 0,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TransDrivelineEngaged",
        .cpp_name = "transdrivelineengaged",
        .message_dbc_name = "ETC1_Electronic_Trans_Cntrl_1",
        .unit = "",
        .choice_enum_name = "Etc1ElectronicTransCntrl1TransdrivelineengagedState",
    },
    SignalMeta{
        .id = SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged,
        .message_id = MessageId::etc1_electronic_trans_cntrl_1,
        .start_bit = 2,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TrnsTorqueConverterLockupEngaged",
        .cpp_name = "trnstorqueconverterlockupengaged",
        .message_dbc_name = "ETC1_Electronic_Trans_Cntrl_1",
        .unit = "",
        .choice_enum_name = "Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState",
    },
    SignalMeta{
        .id = SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess,
        .message_id = MessageId::etc1_electronic_trans_cntrl_1,
        .start_bit = 4,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TransShiftInProcess",
        .cpp_name = "transshiftinprocess",
        .message_dbc_name = "ETC1_Electronic_Trans_Cntrl_1",
        .unit = "",
        .choice_enum_name = "Etc1ElectronicTransCntrl1TransshiftinprocessState",
    },
    SignalMeta{
        .id = SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess,
        .message_id = MessageId::etc1_electronic_trans_cntrl_1,
        .start_bit = 6,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TrnsTrqCnvrtrLckpTrnstnInProcess",
        .cpp_name = "trnstrqcnvrtrlckptrnstninprocess",
        .message_dbc_name = "ETC1_Electronic_Trans_Cntrl_1",
        .unit = "",
        .choice_enum_name = "Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState",
    },
    SignalMeta{
        .id = SignalId::etc1_electronic_trans_cntrl_1__transoutputshaftspeed,
        .message_id = MessageId::etc1_electronic_trans_cntrl_1,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.125,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "TransOutputShaftSpeed",
        .cpp_name = "transoutputshaftspeed",
        .message_dbc_name = "ETC1_Electronic_Trans_Cntrl_1",
        .unit = "rpm",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::etc1_electronic_trans_cntrl_1__percentclutchslip,
        .message_id = MessageId::etc1_electronic_trans_cntrl_1,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "PercentClutchSlip",
        .cpp_name = "percentclutchslip",
        .message_dbc_name = "ETC1_Electronic_Trans_Cntrl_1",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable,
        .message_id = MessageId::etc1_electronic_trans_cntrl_1,
        .start_bit = 32,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngMomentaryOverspeedEnable",
        .cpp_name = "engmomentaryoverspeedenable",
        .message_dbc_name = "ETC1_Electronic_Trans_Cntrl_1",
        .unit = "",
        .choice_enum_name = "Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState",
    },
    SignalMeta{
        .id = SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable,
        .message_id = MessageId::etc1_electronic_trans_cntrl_1,
        .start_bit = 34,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ProgressiveShiftDisable",
        .cpp_name = "progressiveshiftdisable",
        .message_dbc_name = "ETC1_Electronic_Trans_Cntrl_1",
        .unit = "",
        .choice_enum_name = "Etc1ElectronicTransCntrl1ProgressiveshiftdisableState",
    },
    SignalMeta{
        .id = SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable,
        .message_id = MessageId::etc1_electronic_trans_cntrl_1,
        .start_bit = 36,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "MomentaryEngMaxPowerEnable",
        .cpp_name = "momentaryengmaxpowerenable",
        .message_dbc_name = "ETC1_Electronic_Trans_Cntrl_1",
        .unit = "",
        .choice_enum_name = "Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState",
    },
    SignalMeta{
        .id = SignalId::etc1_electronic_trans_cntrl_1__transinputshaftspeed,
        .message_id = MessageId::etc1_electronic_trans_cntrl_1,
        .start_bit = 40,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.125,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "TransInputShaftSpeed",
        .cpp_name = "transinputshaftspeed",
        .message_dbc_name = "ETC1_Electronic_Trans_Cntrl_1",
        .unit = "rpm",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl,
        .message_id = MessageId::etc1_electronic_trans_cntrl_1,
        .start_bit = 56,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "SrcAddrssOfCntrllngDvcFrTrnsCtrl",
        .cpp_name = "srcaddrssofcntrllngdvcfrtrnsctrl",
        .message_dbc_name = "ETC1_Electronic_Trans_Cntrl_1",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::etc2_electronic_trans_cntrl_2__transselectedgear,
        .message_id = MessageId::etc2_electronic_trans_cntrl_2,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "TransSelectedGear",
        .cpp_name = "transselectedgear",
        .message_dbc_name = "ETC2_Electronic_Trans_Cntrl_2",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::etc2_electronic_trans_cntrl_2__transactualgearratio,
        .message_id = MessageId::etc2_electronic_trans_cntrl_2,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.001,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "TransActualGearRatio",
        .cpp_name = "transactualgearratio",
        .message_dbc_name = "ETC2_Electronic_Trans_Cntrl_2",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear,
        .message_id = MessageId::etc2_electronic_trans_cntrl_2,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = -125.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "TransCurrentGear",
        .cpp_name = "transcurrentgear",
        .message_dbc_name = "ETC2_Electronic_Trans_Cntrl_2",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange,
        .message_id = MessageId::etc2_electronic_trans_cntrl_2,
        .start_bit = 39,
        .bit_length = 16,
        .byte_order = ByteOrder::big_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "TransRequestedRange",
        .cpp_name = "transrequestedrange",
        .message_dbc_name = "ETC2_Electronic_Trans_Cntrl_2",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange,
        .message_id = MessageId::etc2_electronic_trans_cntrl_2,
        .start_bit = 55,
        .bit_length = 16,
        .byte_order = ByteOrder::big_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "TransCurrentRange",
        .cpp_name = "transcurrentrange",
        .message_dbc_name = "ETC2_Electronic_Trans_Cntrl_2",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::rqst_00_5e__parametergroupnumber,
        .message_id = MessageId::rqst_00_5e,
        .start_bit = 0,
        .bit_length = 24,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u32,
        .has_choices = false,
        .dbc_name = "ParameterGroupNumber",
        .cpp_name = "parametergroupnumber",
        .message_dbc_name = "RQST_00_5E",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::rqst_00_21__parametergroupnumber,
        .message_id = MessageId::rqst_00_21,
        .start_bit = 0,
        .bit_length = 24,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u32,
        .has_choices = false,
        .dbc_name = "ParameterGroupNumber",
        .cpp_name = "parametergroupnumber",
        .message_dbc_name = "RQST_00_21",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::rqst_global_5e__parametergroupnumber,
        .message_id = MessageId::rqst_global_5e,
        .start_bit = 0,
        .bit_length = 24,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u32,
        .has_choices = false,
        .dbc_name = "ParameterGroupNumber",
        .cpp_name = "parametergroupnumber",
        .message_dbc_name = "RQST_Global_5E",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::rqst_global_03__parametergroupnumber,
        .message_id = MessageId::rqst_global_03,
        .start_bit = 0,
        .bit_length = 24,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u32,
        .has_choices = false,
        .dbc_name = "ParameterGroupNumber",
        .cpp_name = "parametergroupnumber",
        .message_dbc_name = "RQST_Global_03",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tci_transfer_case_information__transfercasestatus,
        .message_id = MessageId::tci_transfer_case_information,
        .start_bit = 0,
        .bit_length = 3,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TransferCaseStatus",
        .cpp_name = "transfercasestatus",
        .message_dbc_name = "TCI_Transfer_Case_Information",
        .unit = "",
        .choice_enum_name = "TciTransferCaseInformationTransfercasestatusState",
    },
    SignalMeta{
        .id = SignalId::tci_transfer_case_information__dirstatus,
        .message_id = MessageId::tci_transfer_case_information,
        .start_bit = 3,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "DirStatus",
        .cpp_name = "dirstatus",
        .message_dbc_name = "TCI_Transfer_Case_Information",
        .unit = "",
        .choice_enum_name = "TciTransferCaseInformationDirstatusState",
    },
    SignalMeta{
        .id = SignalId::tci_transfer_case_information__actualgearratio,
        .message_id = MessageId::tci_transfer_case_information,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.01,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "ActualGearRatio",
        .cpp_name = "actualgearratio",
        .message_dbc_name = "TCI_Transfer_Case_Information",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tci_transfer_case_information__messagecounter,
        .message_id = MessageId::tci_transfer_case_information,
        .start_bit = 56,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "MessageCounter",
        .cpp_name = "messagecounter",
        .message_dbc_name = "TCI_Transfer_Case_Information",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::tci_transfer_case_information__messagechecksum,
        .message_id = MessageId::tci_transfer_case_information,
        .start_bit = 60,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "MessageChecksum",
        .cpp_name = "messagechecksum",
        .message_dbc_name = "TCI_Transfer_Case_Information",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::trf1_transmission_fluids_1__clutchpress,
        .message_id = MessageId::trf1_transmission_fluids_1,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 16.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "ClutchPress",
        .cpp_name = "clutchpress",
        .message_dbc_name = "TRF1_Transmission_Fluids_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::trf1_transmission_fluids_1__transoillevel1,
        .message_id = MessageId::trf1_transmission_fluids_1,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "TransOilLevel1",
        .cpp_name = "transoillevel1",
        .message_dbc_name = "TRF1_Transmission_Fluids_1",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::trf1_transmission_fluids_1__transfilterdiffpress,
        .message_id = MessageId::trf1_transmission_fluids_1,
        .start_bit = 16,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 2.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "TransFilterDiffPress",
        .cpp_name = "transfilterdiffpress",
        .message_dbc_name = "TRF1_Transmission_Fluids_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::trf1_transmission_fluids_1__transoilpress,
        .message_id = MessageId::trf1_transmission_fluids_1,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 16.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "TransOilPress",
        .cpp_name = "transoilpress",
        .message_dbc_name = "TRF1_Transmission_Fluids_1",
        .unit = "kPa",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::trf1_transmission_fluids_1__transoiltemp1,
        .message_id = MessageId::trf1_transmission_fluids_1,
        .start_bit = 32,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.03125,
        .offset = -273.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "TransOilTemp1",
        .cpp_name = "transoiltemp1",
        .message_dbc_name = "TRF1_Transmission_Fluids_1",
        .unit = "ï¿½C",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::trf1_transmission_fluids_1__transoillevel1high_low,
        .message_id = MessageId::trf1_transmission_fluids_1,
        .start_bit = 48,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.5,
        .offset = -62.5,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "TransOilLevel1High_Low",
        .cpp_name = "transoillevel1high_low",
        .message_dbc_name = "TRF1_Transmission_Fluids_1",
        .unit = "l",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer,
        .message_id = MessageId::trf1_transmission_fluids_1,
        .start_bit = 56,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TransOilLevel1CountdownTimer",
        .cpp_name = "transoillevel1countdowntimer",
        .message_dbc_name = "TRF1_Transmission_Fluids_1",
        .unit = "",
        .choice_enum_name = "Trf1TransmissionFluids1Transoillevel1countdowntimerState",
    },
    SignalMeta{
        .id = SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus,
        .message_id = MessageId::trf1_transmission_fluids_1,
        .start_bit = 60,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TransOilLevel1MeasurementStatus",
        .cpp_name = "transoillevel1measurementstatus",
        .message_dbc_name = "TRF1_Transmission_Fluids_1",
        .unit = "",
        .choice_enum_name = "Trf1TransmissionFluids1Transoillevel1measurementstatusState",
    },
    SignalMeta{
        .id = SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit,
        .message_id = MessageId::ccss_cruise_control_vehicle_spd,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "MaxVehicleSpeedLimit",
        .cpp_name = "maxvehiclespeedlimit",
        .message_dbc_name = "CCSS_Cruise_Control_Vehicle_Spd",
        .unit = "km/h",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed,
        .message_id = MessageId::ccss_cruise_control_vehicle_spd,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "CruiseCtrlHighSetLimitSpeed",
        .cpp_name = "cruisectrlhighsetlimitspeed",
        .message_dbc_name = "CCSS_Cruise_Control_Vehicle_Spd",
        .unit = "km/h",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed,
        .message_id = MessageId::ccss_cruise_control_vehicle_spd,
        .start_bit = 16,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "CruiseCtrlLowSetLimitSpeed",
        .cpp_name = "cruisectrllowsetlimitspeed",
        .message_dbc_name = "CCSS_Cruise_Control_Vehicle_Spd",
        .unit = "km/h",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit6808,
        .message_id = MessageId::ccss_cruise_control_vehicle_spd,
        .start_bit = 24,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.00390625,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "MaxVehicleSpeedLimit6808",
        .cpp_name = "maxvehiclespeedlimit6808",
        .message_dbc_name = "CCSS_Cruise_Control_Vehicle_Spd",
        .unit = "km/h",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd,
        .message_id = MessageId::ccss_cruise_control_vehicle_spd,
        .start_bit = 40,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "CtrlSysLowSetLmtSpd",
        .cpp_name = "ctrlsyslowsetlmtspd",
        .message_dbc_name = "CCSS_Cruise_Control_Vehicle_Spd",
        .unit = "km/h",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport,
        .message_id = MessageId::ccss_cruise_control_vehicle_spd,
        .start_bit = 48,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "CtrlDisCmdSupport",
        .cpp_name = "ctrldiscmdsupport",
        .message_dbc_name = "CCSS_Cruise_Control_Vehicle_Spd",
        .unit = "",
        .choice_enum_name = "CcssCruiseControlVehicleSpdCtrldiscmdsupportState",
    },
    SignalMeta{
        .id = SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport,
        .message_id = MessageId::ccss_cruise_control_vehicle_spd,
        .start_bit = 50,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "CtrlResumeCmdSupport",
        .cpp_name = "ctrlresumecmdsupport",
        .message_dbc_name = "CCSS_Cruise_Control_Vehicle_Spd",
        .unit = "",
        .choice_enum_name = "CcssCruiseControlVehicleSpdCtrlresumecmdsupportState",
    },
    SignalMeta{
        .id = SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport,
        .message_id = MessageId::ccss_cruise_control_vehicle_spd,
        .start_bit = 52,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "CtrlPauseCmdSupport",
        .cpp_name = "ctrlpausecmdsupport",
        .message_dbc_name = "CCSS_Cruise_Control_Vehicle_Spd",
        .unit = "",
        .choice_enum_name = "CcssCruiseControlVehicleSpdCtrlpausecmdsupportState",
    },
    SignalMeta{
        .id = SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport,
        .message_id = MessageId::ccss_cruise_control_vehicle_spd,
        .start_bit = 54,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "CtrlSetCmdSupport",
        .cpp_name = "ctrlsetcmdsupport",
        .message_dbc_name = "CCSS_Cruise_Control_Vehicle_Spd",
        .unit = "",
        .choice_enum_name = "CcssCruiseControlVehicleSpdCtrlsetcmdsupportState",
    },
    SignalMeta{
        .id = SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype,
        .message_id = MessageId::ccss_cruise_control_vehicle_spd,
        .start_bit = 56,
        .bit_length = 4,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "PowertrainAdaptiveCCType",
        .cpp_name = "powertrainadaptivecctype",
        .message_dbc_name = "CCSS_Cruise_Control_Vehicle_Spd",
        .unit = "",
        .choice_enum_name = "CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 0,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TwoSpeedAxleSwitch",
        .cpp_name = "twospeedaxleswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdTwospeedaxleswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 2,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ParkingBrakeSwitch",
        .cpp_name = "parkingbrakeswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdParkingbrakeswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 4,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "CruiseCtrlPauseSwitch",
        .cpp_name = "cruisectrlpauseswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdCruisectrlpauseswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 6,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ParkBrakeReleaseInhibitRq",
        .cpp_name = "parkbrakereleaseinhibitrq",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__wheelbasedvehiclespeed,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 8,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.00390625,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "WheelBasedVehicleSpeed",
        .cpp_name = "wheelbasedvehiclespeed",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "km/h",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 24,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "CruiseCtrlActive",
        .cpp_name = "cruisectrlactive",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdCruisectrlactiveState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 26,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "CruiseCtrlEnableSwitch",
        .cpp_name = "cruisectrlenableswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdCruisectrlenableswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__brakeswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 28,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "BrakeSwitch",
        .cpp_name = "brakeswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdBrakeswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__clutchswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 30,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ClutchSwitch",
        .cpp_name = "clutchswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdClutchswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 32,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "CruiseCtrlSetSwitch",
        .cpp_name = "cruisectrlsetswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdCruisectrlsetswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 34,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "CruiseCtrlCoastSwitch",
        .cpp_name = "cruisectrlcoastswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdCruisectrlcoastswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 36,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "CruiseCtrlResumeSwitch",
        .cpp_name = "cruisectrlresumeswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdCruisectrlresumeswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 38,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "CruiseCtrlAccelerateSwitch",
        .cpp_name = "cruisectrlaccelerateswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 40,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "CruiseCtrlSetSpeed",
        .cpp_name = "cruisectrlsetspeed",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "km/h",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 48,
        .bit_length = 5,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "PTOGovernorState",
        .cpp_name = "ptogovernorstate",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdPtogovernorstateState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 53,
        .bit_length = 3,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "CruiseCtrlStates",
        .cpp_name = "cruisectrlstates",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdCruisectrlstatesState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 56,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngIdleIncrementSwitch",
        .cpp_name = "engidleincrementswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdEngidleincrementswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 58,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngIdleDecrementSwitch",
        .cpp_name = "engidledecrementswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdEngidledecrementswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 60,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngTestModeSwitch",
        .cpp_name = "engtestmodeswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdEngtestmodeswitchState",
    },
    SignalMeta{
        .id = SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch,
        .message_id = MessageId::ccvs1_cruise_control_vehspd,
        .start_bit = 62,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngShutdownOverrideSwitch",
        .cpp_name = "engshutdownoverrideswitch",
        .message_dbc_name = "CCVS1__Cruise_Control_VehSpd",
        .unit = "",
        .choice_enum_name = "Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 0,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ASREngCtrlActive",
        .cpp_name = "asrengctrlactive",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlAsrengctrlactiveState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 2,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ASRBrakeCtrlActive",
        .cpp_name = "asrbrakectrlactive",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 4,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "AntiLockBrakingActive",
        .cpp_name = "antilockbrakingactive",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 6,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EBSBrakeSwitch",
        .cpp_name = "ebsbrakeswitch",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlEbsbrakeswitchState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__brakepedalpos,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "BrakePedalPos",
        .cpp_name = "brakepedalpos",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 16,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ABSOffroadSwitch",
        .cpp_name = "absoffroadswitch",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlAbsoffroadswitchState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 18,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ASROffroadSwitch",
        .cpp_name = "asroffroadswitch",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlAsroffroadswitchState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 20,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ASRHillHolderSwitch",
        .cpp_name = "asrhillholderswitch",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlAsrhillholderswitchState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 22,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TractionCtrlOverrideSwitch",
        .cpp_name = "tractionctrloverrideswitch",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 24,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "AccelInterlockSwitch",
        .cpp_name = "accelinterlockswitch",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlAccelinterlockswitchState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__engderateswitch,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 26,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngDerateSwitch",
        .cpp_name = "engderateswitch",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlEngderateswitchState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 28,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngAuxShutdownSwitch",
        .cpp_name = "engauxshutdownswitch",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 30,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "RemoteAccelEnableSwitch",
        .cpp_name = "remoteaccelenableswitch",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__engretarderselection,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 32,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 0.4,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "EngRetarderSelection",
        .cpp_name = "engretarderselection",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__absfullyoperational,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 40,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ABSFullyOperational",
        .cpp_name = "absfullyoperational",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlAbsfullyoperationalState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 42,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EBSRedWarningSignal",
        .cpp_name = "ebsredwarningsignal",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlEbsredwarningsignalState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 44,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ABS_EBSAmberWarningSignal",
        .cpp_name = "abs_ebsamberwarningsignal",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 46,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ATC_ASRInformationSignal",
        .cpp_name = "atc_asrinformationsignal",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 48,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "SrcAddrssOfCntrllngDvcFrBrkeCtrl",
        .cpp_name = "srcaddrssofcntrllngdvcfrbrkectrl",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__railroadmodesw,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 56,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "RailroadModeSw",
        .cpp_name = "railroadmodesw",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlRailroadmodeswState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 58,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "HaltBrakeSwitch",
        .cpp_name = "haltbrakeswitch",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlHaltbrakeswitchState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 60,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TrailerABSStatus",
        .cpp_name = "trailerabsstatus",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlTrailerabsstatusState",
    },
    SignalMeta{
        .id = SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal,
        .message_id = MessageId::ebc1_electronic_brake_cntrl,
        .start_bit = 62,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "TrctrMntdTrailerABSWarningSignal",
        .cpp_name = "trctrmntdtrailerabswarningsignal",
        .message_dbc_name = "EBC1_Electronic_Brake_Cntrl",
        .unit = "",
        .choice_enum_name = "Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engidleshutdownhasshutdowneng,
        .message_id = MessageId::shutdn,
        .start_bit = 0,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngIdleShutdownHasShutdownEng",
        .cpp_name = "engidleshutdownhasshutdowneng",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngidleshutdownhasshutdownengState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engidleshutdowndriveralertmode,
        .message_id = MessageId::shutdn,
        .start_bit = 2,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngIdleShutdownDriverAlertMode",
        .cpp_name = "engidleshutdowndriveralertmode",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngidleshutdowndriveralertmodeState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engidleshutdowntimeroverride,
        .message_id = MessageId::shutdn,
        .start_bit = 4,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngIdleShutdownTimerOverride",
        .cpp_name = "engidleshutdowntimeroverride",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngidleshutdowntimeroverrideState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engidleshutdowntimerstate,
        .message_id = MessageId::shutdn,
        .start_bit = 6,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngIdleShutdownTimerState",
        .cpp_name = "engidleshutdowntimerstate",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngidleshutdowntimerstateState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engidleshutdowntimerfunction,
        .message_id = MessageId::shutdn,
        .start_bit = 14,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngIdleShutdownTimerFunction",
        .cpp_name = "engidleshutdowntimerfunction",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngidleshutdowntimerfunctionState",
    },
    SignalMeta{
        .id = SignalId::shutdn__a_chighpressfanswitch,
        .message_id = MessageId::shutdn,
        .start_bit = 16,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "A_CHighPressFanSwitch",
        .cpp_name = "a_chighpressfanswitch",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnAChighpressfanswitchState",
    },
    SignalMeta{
        .id = SignalId::shutdn__refrigerantlowpressswitch,
        .message_id = MessageId::shutdn,
        .start_bit = 18,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "RefrigerantLowPressSwitch",
        .cpp_name = "refrigerantlowpressswitch",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnRefrigerantlowpressswitchState",
    },
    SignalMeta{
        .id = SignalId::shutdn__refrigeranthighpressswitch,
        .message_id = MessageId::shutdn,
        .start_bit = 20,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "RefrigerantHighPressSwitch",
        .cpp_name = "refrigeranthighpressswitch",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnRefrigeranthighpressswitchState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engwaittostartlamp,
        .message_id = MessageId::shutdn,
        .start_bit = 24,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngWaitToStartLamp",
        .cpp_name = "engwaittostartlamp",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngwaittostartlampState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engprtectionsystemhasshutdowneng,
        .message_id = MessageId::shutdn,
        .start_bit = 32,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngPrtectionSystemHasShutdownEng",
        .cpp_name = "engprtectionsystemhasshutdowneng",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngprtectionsystemhasshutdownengState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engprtctnsystmapprachingshutdown,
        .message_id = MessageId::shutdn,
        .start_bit = 34,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngPrtctnSystmApprachingShutdown",
        .cpp_name = "engprtctnsystmapprachingshutdown",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngprtctnsystmapprachingshutdownState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engprotectionsystemtimeroverride,
        .message_id = MessageId::shutdn,
        .start_bit = 36,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngProtectionSystemTimerOverride",
        .cpp_name = "engprotectionsystemtimeroverride",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngprotectionsystemtimeroverrideState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engprotectionsystemtimerstate,
        .message_id = MessageId::shutdn,
        .start_bit = 38,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngProtectionSystemTimerState",
        .cpp_name = "engprotectionsystemtimerstate",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngprotectionsystemtimerstateState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engprotectionsystemconfig,
        .message_id = MessageId::shutdn,
        .start_bit = 46,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngProtectionSystemConfig",
        .cpp_name = "engprotectionsystemconfig",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngprotectionsystemconfigState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engalarmacknowledge,
        .message_id = MessageId::shutdn,
        .start_bit = 48,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngAlarmAcknowledge",
        .cpp_name = "engalarmacknowledge",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngalarmacknowledgeState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engalarmoutputcmdstatus,
        .message_id = MessageId::shutdn,
        .start_bit = 50,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngAlarmOutputCmdStatus",
        .cpp_name = "engalarmoutputcmdstatus",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngalarmoutputcmdstatusState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engairshutoffcmdstatus,
        .message_id = MessageId::shutdn,
        .start_bit = 52,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngAirShutoffCmdStatus",
        .cpp_name = "engairshutoffcmdstatus",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngairshutoffcmdstatusState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engoverspeedtest,
        .message_id = MessageId::shutdn,
        .start_bit = 54,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngOverspeedTest",
        .cpp_name = "engoverspeedtest",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngoverspeedtestState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engairshutoffstatus,
        .message_id = MessageId::shutdn,
        .start_bit = 56,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngAirShutoffStatus",
        .cpp_name = "engairshutoffstatus",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngairshutoffstatusState",
    },
    SignalMeta{
        .id = SignalId::shutdn__ptoshutdownhasshutdowneng,
        .message_id = MessageId::shutdn,
        .start_bit = 58,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "PTOShutdownHasShutdownEng",
        .cpp_name = "ptoshutdownhasshutdowneng",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnPtoshutdownhasshutdownengState",
    },
    SignalMeta{
        .id = SignalId::shutdn__clntlvlengprtctionshutdownstatus,
        .message_id = MessageId::shutdn,
        .start_bit = 60,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "ClntLvlEngPrtctionShutdownStatus",
        .cpp_name = "clntlvlengprtctionshutdownstatus",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnClntlvlengprtctionshutdownstatusState",
    },
    SignalMeta{
        .id = SignalId::shutdn__engoilpresssw,
        .message_id = MessageId::shutdn,
        .start_bit = 62,
        .bit_length = 2,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "EngOilPressSw",
        .cpp_name = "engoilpresssw",
        .message_dbc_name = "SHUTDN",
        .unit = "",
        .choice_enum_name = "ShutdnEngoilpressswState",
    },
} };

inline constexpr std::array<SignalId, kSignalCount> kMessageSignalsFlat{ {
    SignalId::eec5_electronic_engine_control_5__engine_turbocharger_1_calculated,
    SignalId::eec5_electronic_engine_control_5__commanded_vgt_position,
    SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch,
    SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode,
    SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode,
    SignalId::eec5_electronic_engine_control_5__actual_vgt_position,
    SignalId::eec9_electronic_engine_control_9__engine_exhaust_gas_recirculation,
    SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure,
    SignalId::eec9_electronic_engine_control_9__commanded_engine_fuel_injection,
    SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure,
    SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure,
    SignalId::ebcc_engine_exhaust_brake_cont__engine_exhaust_brake_actuator_co,
    SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou,
    SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu,
    SignalId::et3_engine_temperature_3__engine_intake_manifold_1_air_tem,
    SignalId::et3_engine_temperature_3__engine_coolant_temperature_high,
    SignalId::et3_engine_temperature_3__engine_intake_valve_actuation_sy,
    SignalId::et3_engine_temperature_3__engine_cac_outlet_temperature,
    SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on,
    SignalId::dm26_diagnostic_readiness_3__time_since_engine_start,
    SignalId::ic1_intake_exhaust_cond_1__aft1dpfinpress,
    SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press,
    SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp,
    SignalId::ic1_intake_exhaust_cond_1__engairintakepress,
    SignalId::ic1_intake_exhaust_cond_1__engairfilter1diffpress,
    SignalId::ic1_intake_exhaust_cond_1__engexhaustgastemp,
    SignalId::ic1_intake_exhaust_cond_1__engcoolantfilterdiffpress,
    SignalId::amb_ambient_conditions__barometric_pressurebarometric_pr,
    SignalId::amb_ambient_conditions__cabinteriortemp,
    SignalId::amb_ambient_conditions__ambient_air_temperature,
    SignalId::amb_ambient_conditions__engine_air_intake_temperature,
    SignalId::amb_ambient_conditions__roadsurfacetemp,
    SignalId::eec1_electronic_engine_control_1__engine_torque_mode,
    SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution,
    SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq,
    SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque,
    SignalId::eec1_electronic_engine_control_1__engine_speed,
    SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl,
    SignalId::eec1_electronic_engine_control_1__engstartermode,
    SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque,
    SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch,
    SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch,
    SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus,
    SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch,
    SignalId::eec2_electronic_engine_control_2__accelpedalpos1,
    SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed,
    SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos,
    SignalId::eec2_electronic_engine_control_2__accelpedalpos2,
    SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus,
    SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback,
    SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive,
    SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive,
    SignalId::eec2_electronic_engine_control_2__actlmaxavailableengpercenttorque,
    SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque,
    SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque,
    SignalId::eec3_electronic_engine_control_3__enginesdesiredoperatingspeed,
    SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm,
    SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque,
    SignalId::eec3_electronic_engine_control_3__aft1exhgasmfr,
    SignalId::eec3_electronic_engine_control_3__aft1indewpoint,
    SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint,
    SignalId::eec3_electronic_engine_control_3__aft2indewpoint,
    SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint,
    SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress,
    SignalId::efl_p1_eng_fluid_level_press_1__engexcrankcaseblowbypress,
    SignalId::efl_p1_eng_fluid_level_press_1__engoillevel,
    SignalId::efl_p1_eng_fluid_level_press_1__engoilpress,
    SignalId::efl_p1_eng_fluid_level_press_1__engcrankcasepress,
    SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress,
    SignalId::efl_p1_eng_fluid_level_press_1__engcoolantlevel,
    SignalId::efl_p2_eng_fluid_level_press_2__enginjectionctrlpress,
    SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail1press,
    SignalId::efl_p2_eng_fluid_level_press_2__enginjectortimingrail1press,
    SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail2press,
    SignalId::et1_engine_temperature_1__engcoolanttemp,
    SignalId::et1_engine_temperature_1__engfueltemp1,
    SignalId::et1_engine_temperature_1__engoiltemp1,
    SignalId::et1_engine_temperature_1__engturbooiltemp,
    SignalId::et1_engine_temperature_1__engintercoolertemp,
    SignalId::et1_engine_temperature_1__engintercoolerthermostatopening,
    SignalId::lfe1_fuel_economy_liquid_1__engfuelrate,
    SignalId::lfe1_fuel_economy_liquid_1__enginstantaneousfueleconomy,
    SignalId::lfe1_fuel_economy_liquid_1__engaveragefueleconomy,
    SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve1pos,
    SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve2pos,
    SignalId::transportprotocol_header__controlbyte,
    SignalId::transportprotocol_header__totalmessagesizeeoma,
    SignalId::transportprotocol_header__connectionabortreason,
    SignalId::transportprotocol_header__totalmessagesize,
    SignalId::transportprotocol_header__numberofpacketsthatcanbesent,
    SignalId::transportprotocol_header__totalmessagesizebam,
    SignalId::transportprotocol_header__nextpacketnumbertobesent,
    SignalId::transportprotocol_header__totalnumberofpackets,
    SignalId::transportprotocol_header__totalnumberofpacketseoma,
    SignalId::transportprotocol_header__totalnumberofpacketsbam,
    SignalId::transportprotocol_header__maximumnumberofpackets,
    SignalId::transportprotocol_header__pgnumber,
    SignalId::transportprotocol_data__sequencenumber,
    SignalId::dm01_active_diagnostics__protectlampstatus,
    SignalId::dm01_active_diagnostics__amberwarninglampstatus,
    SignalId::dm01_active_diagnostics__redstoplampstate,
    SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus,
    SignalId::dm01_active_diagnostics__flashprotectlamp,
    SignalId::dm01_active_diagnostics__flashamberwarninglamp,
    SignalId::dm01_active_diagnostics__flashredstoplamp,
    SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp,
    SignalId::dm01_active_diagnostics__dtc1,
    SignalId::tsc1_31__engoverridectrlmode,
    SignalId::tsc1_31__engrequestedspeedctrlconditions,
    SignalId::tsc1_31__overridectrlmodepriority,
    SignalId::tsc1_31__engrequestedspeed_speedlimit,
    SignalId::tsc1_31__engrequestedtorque_torquelimit,
    SignalId::tsc1_31__tsc1transrate,
    SignalId::tsc1_31__tsc1ctrlpurpose,
    SignalId::tsc1_31__engrequestedtorquehighresolution,
    SignalId::tsc1_31__messagecounter,
    SignalId::tsc1_31__messagechecksum,
    SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_intak,
    SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie,
    SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_effic,
    SignalId::hours_engine_hours_revolutions__engine_total_hours_of_operation,
    SignalId::hours_engine_hours_revolutions__engine_total_revolutions_249,
    SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou,
    SignalId::tci5_turbocharger_information_5__engine_turbocharger_2_turbine_ou,
    SignalId::tci5_turbocharger_information_5__engine_turbocharger_3_turbine_ou,
    SignalId::tci5_turbocharger_information_5__engine_turbocharger_4_turbine_ou,
    SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114,
    SignalId::vep1_vehicle_electrical_power_1__alternator_current_115,
    SignalId::vep1_vehicle_electrical_power_1__charging_system_potential_volta,
    SignalId::vep1_vehicle_electrical_power_1__battery_potential_power_input_1,
    SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158,
    SignalId::eec20_electronic_engine_control__absolute_engine_load,
    SignalId::easi_engine_air_system_info__engine_intake_maf,
    SignalId::tsc1_03__engoverridectrlmode,
    SignalId::tsc1_03__engrequestedspeedctrlconditions,
    SignalId::tsc1_03__overridectrlmodepriority,
    SignalId::tsc1_03__engrequestedspeed_speedlimit,
    SignalId::tsc1_03__engrequestedtorque_torquelimit,
    SignalId::tsc1_03__tsc1transrate,
    SignalId::tsc1_03__tsc1ctrlpurpose,
    SignalId::tsc1_03__engrequestedtorquehighresolution,
    SignalId::tsc1_03__messagecounter,
    SignalId::tsc1_03__messagechecksum,
    SignalId::tsc1_0b__engoverridectrlmode,
    SignalId::tsc1_0b__engrequestedspeedctrlconditions,
    SignalId::tsc1_0b__overridectrlmodepriority,
    SignalId::tsc1_0b__engrequestedspeed_speedlimit,
    SignalId::tsc1_0b__engrequestedtorque_torquelimit,
    SignalId::tsc1_0b__tsc1transrate,
    SignalId::tsc1_0b__tsc1ctrlpurpose,
    SignalId::tsc1_0b__engrequestedtorquehighresolution,
    SignalId::tsc1_0b__messagecounter,
    SignalId::tsc1_0b__messagechecksum,
    SignalId::dm07__testidentifier,
    SignalId::dm07__spn1,
    SignalId::dm07__failuremodeidentifier1,
    SignalId::dm07__spn1high,
    SignalId::dm08__testidentifier,
    SignalId::dm08__testtype,
    SignalId::dm08__testvalue,
    SignalId::dm08__testlimitmaximum,
    SignalId::dm08__testlimitminimum,
    SignalId::erc1_electronic_retarder_cntrl__retardertorquemode,
    SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch,
    SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch,
    SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque,
    SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque,
    SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease,
    SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight,
    SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch,
    SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus,
    SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr,
    SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque,
    SignalId::erc1_electronic_retarder_cntrl__retarderselectionnonengine,
    SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque,
    SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged,
    SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged,
    SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess,
    SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess,
    SignalId::etc1_electronic_trans_cntrl_1__transoutputshaftspeed,
    SignalId::etc1_electronic_trans_cntrl_1__percentclutchslip,
    SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable,
    SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable,
    SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable,
    SignalId::etc1_electronic_trans_cntrl_1__transinputshaftspeed,
    SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl,
    SignalId::etc2_electronic_trans_cntrl_2__transselectedgear,
    SignalId::etc2_electronic_trans_cntrl_2__transactualgearratio,
    SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear,
    SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange,
    SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange,
    SignalId::rqst_00_5e__parametergroupnumber,
    SignalId::rqst_00_21__parametergroupnumber,
    SignalId::rqst_global_5e__parametergroupnumber,
    SignalId::rqst_global_03__parametergroupnumber,
    SignalId::tci_transfer_case_information__transfercasestatus,
    SignalId::tci_transfer_case_information__dirstatus,
    SignalId::tci_transfer_case_information__actualgearratio,
    SignalId::tci_transfer_case_information__messagecounter,
    SignalId::tci_transfer_case_information__messagechecksum,
    SignalId::trf1_transmission_fluids_1__clutchpress,
    SignalId::trf1_transmission_fluids_1__transoillevel1,
    SignalId::trf1_transmission_fluids_1__transfilterdiffpress,
    SignalId::trf1_transmission_fluids_1__transoilpress,
    SignalId::trf1_transmission_fluids_1__transoiltemp1,
    SignalId::trf1_transmission_fluids_1__transoillevel1high_low,
    SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer,
    SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus,
    SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit,
    SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed,
    SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed,
    SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit6808,
    SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd,
    SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport,
    SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport,
    SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport,
    SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport,
    SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype,
    SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch,
    SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch,
    SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch,
    SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq,
    SignalId::ccvs1_cruise_control_vehspd__wheelbasedvehiclespeed,
    SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive,
    SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch,
    SignalId::ccvs1_cruise_control_vehspd__brakeswitch,
    SignalId::ccvs1_cruise_control_vehspd__clutchswitch,
    SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch,
    SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch,
    SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch,
    SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch,
    SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed,
    SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate,
    SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates,
    SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch,
    SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch,
    SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch,
    SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch,
    SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive,
    SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive,
    SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive,
    SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch,
    SignalId::ebc1_electronic_brake_cntrl__brakepedalpos,
    SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch,
    SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch,
    SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch,
    SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch,
    SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch,
    SignalId::ebc1_electronic_brake_cntrl__engderateswitch,
    SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch,
    SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch,
    SignalId::ebc1_electronic_brake_cntrl__engretarderselection,
    SignalId::ebc1_electronic_brake_cntrl__absfullyoperational,
    SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal,
    SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal,
    SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal,
    SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl,
    SignalId::ebc1_electronic_brake_cntrl__railroadmodesw,
    SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch,
    SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus,
    SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal,
    SignalId::shutdn__engidleshutdownhasshutdowneng,
    SignalId::shutdn__engidleshutdowndriveralertmode,
    SignalId::shutdn__engidleshutdowntimeroverride,
    SignalId::shutdn__engidleshutdowntimerstate,
    SignalId::shutdn__engidleshutdowntimerfunction,
    SignalId::shutdn__a_chighpressfanswitch,
    SignalId::shutdn__refrigerantlowpressswitch,
    SignalId::shutdn__refrigeranthighpressswitch,
    SignalId::shutdn__engwaittostartlamp,
    SignalId::shutdn__engprtectionsystemhasshutdowneng,
    SignalId::shutdn__engprtctnsystmapprachingshutdown,
    SignalId::shutdn__engprotectionsystemtimeroverride,
    SignalId::shutdn__engprotectionsystemtimerstate,
    SignalId::shutdn__engprotectionsystemconfig,
    SignalId::shutdn__engalarmacknowledge,
    SignalId::shutdn__engalarmoutputcmdstatus,
    SignalId::shutdn__engairshutoffcmdstatus,
    SignalId::shutdn__engoverspeedtest,
    SignalId::shutdn__engairshutoffstatus,
    SignalId::shutdn__ptoshutdownhasshutdowneng,
    SignalId::shutdn__clntlvlengprtctionshutdownstatus,
    SignalId::shutdn__engoilpresssw,
} };

constexpr auto message_meta(MessageId id) -> const MessageMeta& {
    return kMessagesById[to_index(id)];
}

constexpr auto signal_meta(SignalId id) -> const SignalMeta& {
    return kSignalsById[to_index(id)];
}

constexpr auto message_name(MessageId id) -> std::string_view {
    return message_meta(id).dbc_name;
}

constexpr auto signal_name(SignalId id) -> std::string_view {
    return signal_meta(id).dbc_name;
}

constexpr auto signal_unit(SignalId id) -> std::string_view {
    return signal_meta(id).unit;
}

constexpr auto signal_parent_message_name(SignalId id) -> std::string_view {
    return signal_meta(id).message_dbc_name;
}

constexpr auto parent_message_id(SignalId id) -> MessageId {
    return signal_meta(id).message_id;
}

constexpr auto message_cycle_time_ms(MessageId id) -> std::uint32_t {
    return message_meta(id).cycle_time_ms;
}

constexpr auto message_signals(MessageId id) -> std::span<const SignalId> {
    const auto& mm = message_meta(id);
    return std::span<const SignalId>{
        kMessageSignalsFlat.data() + mm.signal_offset,
        mm.signal_count
    };
}

constexpr auto find_message_by_frame_id(std::uint32_t frame_id) -> const MessageMeta* {
    for (const auto& msg : kMessagesById) {
        if (msg.frame_id == frame_id) {
            return &msg;
        }
    }
    return nullptr;
}

template <SignalId Id>
struct signal_traits;

template <>
struct signal_traits<SignalId::eec5_electronic_engine_control_5__engine_turbocharger_1_calculated> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec5_electronic_engine_control_5__engine_turbocharger_1_calculated;
    static constexpr MessageId message_id = MessageId::eec5_electronic_engine_control_5;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::eec5_electronic_engine_control_5__commanded_vgt_position> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec5_electronic_engine_control_5__commanded_vgt_position;
    static constexpr MessageId message_id = MessageId::eec5_electronic_engine_control_5;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.0025;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch;
    static constexpr MessageId message_id = MessageId::eec5_electronic_engine_control_5;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode;
    static constexpr MessageId message_id = MessageId::eec5_electronic_engine_control_5;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 50;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode;
    static constexpr MessageId message_id = MessageId::eec5_electronic_engine_control_5;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 52;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec5_electronic_engine_control_5__actual_vgt_position> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec5_electronic_engine_control_5__actual_vgt_position;
    static constexpr MessageId message_id = MessageId::eec5_electronic_engine_control_5;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec9_electronic_engine_control_9__engine_exhaust_gas_recirculation> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec9_electronic_engine_control_9__engine_exhaust_gas_recirculation;
    static constexpr MessageId message_id = MessageId::eec9_electronic_engine_control_9;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.0025;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure;
    static constexpr MessageId message_id = MessageId::eec9_electronic_engine_control_9;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.00390625;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec9_electronic_engine_control_9__commanded_engine_fuel_injection> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec9_electronic_engine_control_9__commanded_engine_fuel_injection;
    static constexpr MessageId message_id = MessageId::eec9_electronic_engine_control_9;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.00390625;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure;
    static constexpr MessageId message_id = MessageId::ebcc_engine_exhaust_brake_cont;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 2.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure;
    static constexpr MessageId message_id = MessageId::ebcc_engine_exhaust_brake_cont;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 2.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__engine_exhaust_brake_actuator_co> {
    using value_type = double;
    static constexpr SignalId id = SignalId::ebcc_engine_exhaust_brake_cont__engine_exhaust_brake_actuator_co;
    static constexpr MessageId message_id = MessageId::ebcc_engine_exhaust_brake_cont;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou;
    static constexpr MessageId message_id = MessageId::ebcc_engine_exhaust_brake_cont;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 2.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu;
    static constexpr MessageId message_id = MessageId::ebcc_engine_exhaust_brake_cont;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 2.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::et3_engine_temperature_3__engine_intake_manifold_1_air_tem> {
    using value_type = double;
    static constexpr SignalId id = SignalId::et3_engine_temperature_3__engine_intake_manifold_1_air_tem;
    static constexpr MessageId message_id = MessageId::et3_engine_temperature_3;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::et3_engine_temperature_3__engine_coolant_temperature_high> {
    using value_type = double;
    static constexpr SignalId id = SignalId::et3_engine_temperature_3__engine_coolant_temperature_high;
    static constexpr MessageId message_id = MessageId::et3_engine_temperature_3;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::et3_engine_temperature_3__engine_intake_valve_actuation_sy> {
    using value_type = double;
    static constexpr SignalId id = SignalId::et3_engine_temperature_3__engine_intake_valve_actuation_sy;
    static constexpr MessageId message_id = MessageId::et3_engine_temperature_3;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::et3_engine_temperature_3__engine_cac_outlet_temperature> {
    using value_type = double;
    static constexpr SignalId id = SignalId::et3_engine_temperature_3__engine_cac_outlet_temperature;
    static constexpr MessageId message_id = MessageId::et3_engine_temperature_3;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on> {
    using value_type = std::uint16_t;
    static constexpr SignalId id = SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on;
    static constexpr MessageId message_id = MessageId::dm21_diagnostic_readiness_2;
    static constexpr SignalType signal_type = SignalType::u16;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm26_diagnostic_readiness_3__time_since_engine_start> {
    using value_type = std::uint16_t;
    static constexpr SignalId id = SignalId::dm26_diagnostic_readiness_3__time_since_engine_start;
    static constexpr MessageId message_id = MessageId::dm26_diagnostic_readiness_3;
    static constexpr SignalType signal_type = SignalType::u16;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ic1_intake_exhaust_cond_1__aft1dpfinpress> {
    using value_type = double;
    static constexpr SignalId id = SignalId::ic1_intake_exhaust_cond_1__aft1dpfinpress;
    static constexpr MessageId message_id = MessageId::ic1_intake_exhaust_cond_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.5;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press;
    static constexpr MessageId message_id = MessageId::ic1_intake_exhaust_cond_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 2.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp> {
    using value_type = double;
    static constexpr SignalId id = SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp;
    static constexpr MessageId message_id = MessageId::ic1_intake_exhaust_cond_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -40.0;
};
template <>
struct signal_traits<SignalId::ic1_intake_exhaust_cond_1__engairintakepress> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ic1_intake_exhaust_cond_1__engairintakepress;
    static constexpr MessageId message_id = MessageId::ic1_intake_exhaust_cond_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 2.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ic1_intake_exhaust_cond_1__engairfilter1diffpress> {
    using value_type = double;
    static constexpr SignalId id = SignalId::ic1_intake_exhaust_cond_1__engairfilter1diffpress;
    static constexpr MessageId message_id = MessageId::ic1_intake_exhaust_cond_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.05;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ic1_intake_exhaust_cond_1__engexhaustgastemp> {
    using value_type = double;
    static constexpr SignalId id = SignalId::ic1_intake_exhaust_cond_1__engexhaustgastemp;
    static constexpr MessageId message_id = MessageId::ic1_intake_exhaust_cond_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::ic1_intake_exhaust_cond_1__engcoolantfilterdiffpress> {
    using value_type = double;
    static constexpr SignalId id = SignalId::ic1_intake_exhaust_cond_1__engcoolantfilterdiffpress;
    static constexpr MessageId message_id = MessageId::ic1_intake_exhaust_cond_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.5;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::amb_ambient_conditions__barometric_pressurebarometric_pr> {
    using value_type = double;
    static constexpr SignalId id = SignalId::amb_ambient_conditions__barometric_pressurebarometric_pr;
    static constexpr MessageId message_id = MessageId::amb_ambient_conditions;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.5;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::amb_ambient_conditions__cabinteriortemp> {
    using value_type = double;
    static constexpr SignalId id = SignalId::amb_ambient_conditions__cabinteriortemp;
    static constexpr MessageId message_id = MessageId::amb_ambient_conditions;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::amb_ambient_conditions__ambient_air_temperature> {
    using value_type = double;
    static constexpr SignalId id = SignalId::amb_ambient_conditions__ambient_air_temperature;
    static constexpr MessageId message_id = MessageId::amb_ambient_conditions;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::amb_ambient_conditions__engine_air_intake_temperature> {
    using value_type = double;
    static constexpr SignalId id = SignalId::amb_ambient_conditions__engine_air_intake_temperature;
    static constexpr MessageId message_id = MessageId::amb_ambient_conditions;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -40.0;
};
template <>
struct signal_traits<SignalId::amb_ambient_conditions__roadsurfacetemp> {
    using value_type = double;
    static constexpr SignalId id = SignalId::amb_ambient_conditions__roadsurfacetemp;
    static constexpr MessageId message_id = MessageId::amb_ambient_conditions;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::eec1_electronic_engine_control_1__engine_torque_mode> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec1_electronic_engine_control_1__engine_torque_mode;
    static constexpr MessageId message_id = MessageId::eec1_electronic_engine_control_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution;
    static constexpr MessageId message_id = MessageId::eec1_electronic_engine_control_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 4;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 0.125;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq;
    static constexpr MessageId message_id = MessageId::eec1_electronic_engine_control_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque;
    static constexpr MessageId message_id = MessageId::eec1_electronic_engine_control_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::eec1_electronic_engine_control_1__engine_speed> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec1_electronic_engine_control_1__engine_speed;
    static constexpr MessageId message_id = MessageId::eec1_electronic_engine_control_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.125;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl;
    static constexpr MessageId message_id = MessageId::eec1_electronic_engine_control_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec1_electronic_engine_control_1__engstartermode> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec1_electronic_engine_control_1__engstartermode;
    static constexpr MessageId message_id = MessageId::eec1_electronic_engine_control_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque;
    static constexpr MessageId message_id = MessageId::eec1_electronic_engine_control_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 2;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 4;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 6;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalpos1> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__accelpedalpos1;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalpos2> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__accelpedalpos2;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 42;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 44;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 46;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__actlmaxavailableengpercenttorque> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__actlmaxavailableengpercenttorque;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque;
    static constexpr MessageId message_id = MessageId::eec2_electronic_engine_control_2;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque;
    static constexpr MessageId message_id = MessageId::eec3_electronic_engine_control_3;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::eec3_electronic_engine_control_3__enginesdesiredoperatingspeed> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec3_electronic_engine_control_3__enginesdesiredoperatingspeed;
    static constexpr MessageId message_id = MessageId::eec3_electronic_engine_control_3;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.125;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm;
    static constexpr MessageId message_id = MessageId::eec3_electronic_engine_control_3;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque;
    static constexpr MessageId message_id = MessageId::eec3_electronic_engine_control_3;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::eec3_electronic_engine_control_3__aft1exhgasmfr> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec3_electronic_engine_control_3__aft1exhgasmfr;
    static constexpr MessageId message_id = MessageId::eec3_electronic_engine_control_3;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.2;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec3_electronic_engine_control_3__aft1indewpoint> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec3_electronic_engine_control_3__aft1indewpoint;
    static constexpr MessageId message_id = MessageId::eec3_electronic_engine_control_3;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint;
    static constexpr MessageId message_id = MessageId::eec3_electronic_engine_control_3;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 58;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec3_electronic_engine_control_3__aft2indewpoint> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec3_electronic_engine_control_3__aft2indewpoint;
    static constexpr MessageId message_id = MessageId::eec3_electronic_engine_control_3;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 60;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint;
    static constexpr MessageId message_id = MessageId::eec3_electronic_engine_control_3;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 62;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress;
    static constexpr MessageId message_id = MessageId::efl_p1_eng_fluid_level_press_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 4.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engexcrankcaseblowbypress> {
    using value_type = double;
    static constexpr SignalId id = SignalId::efl_p1_eng_fluid_level_press_1__engexcrankcaseblowbypress;
    static constexpr MessageId message_id = MessageId::efl_p1_eng_fluid_level_press_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.05;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engoillevel> {
    using value_type = double;
    static constexpr SignalId id = SignalId::efl_p1_eng_fluid_level_press_1__engoillevel;
    static constexpr MessageId message_id = MessageId::efl_p1_eng_fluid_level_press_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engoilpress> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::efl_p1_eng_fluid_level_press_1__engoilpress;
    static constexpr MessageId message_id = MessageId::efl_p1_eng_fluid_level_press_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 4.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcrankcasepress> {
    using value_type = double;
    static constexpr SignalId id = SignalId::efl_p1_eng_fluid_level_press_1__engcrankcasepress;
    static constexpr MessageId message_id = MessageId::efl_p1_eng_fluid_level_press_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.0078125;
    static constexpr double offset = -250.0;
};
template <>
struct signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress;
    static constexpr MessageId message_id = MessageId::efl_p1_eng_fluid_level_press_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 2.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcoolantlevel> {
    using value_type = double;
    static constexpr SignalId id = SignalId::efl_p1_eng_fluid_level_press_1__engcoolantlevel;
    static constexpr MessageId message_id = MessageId::efl_p1_eng_fluid_level_press_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectionctrlpress> {
    using value_type = double;
    static constexpr SignalId id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectionctrlpress;
    static constexpr MessageId message_id = MessageId::efl_p2_eng_fluid_level_press_2;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.00390625;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail1press> {
    using value_type = double;
    static constexpr SignalId id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail1press;
    static constexpr MessageId message_id = MessageId::efl_p2_eng_fluid_level_press_2;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.00390625;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectortimingrail1press> {
    using value_type = double;
    static constexpr SignalId id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectortimingrail1press;
    static constexpr MessageId message_id = MessageId::efl_p2_eng_fluid_level_press_2;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.00390625;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail2press> {
    using value_type = double;
    static constexpr SignalId id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail2press;
    static constexpr MessageId message_id = MessageId::efl_p2_eng_fluid_level_press_2;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.00390625;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::et1_engine_temperature_1__engcoolanttemp> {
    using value_type = double;
    static constexpr SignalId id = SignalId::et1_engine_temperature_1__engcoolanttemp;
    static constexpr MessageId message_id = MessageId::et1_engine_temperature_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -40.0;
};
template <>
struct signal_traits<SignalId::et1_engine_temperature_1__engfueltemp1> {
    using value_type = double;
    static constexpr SignalId id = SignalId::et1_engine_temperature_1__engfueltemp1;
    static constexpr MessageId message_id = MessageId::et1_engine_temperature_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -40.0;
};
template <>
struct signal_traits<SignalId::et1_engine_temperature_1__engoiltemp1> {
    using value_type = double;
    static constexpr SignalId id = SignalId::et1_engine_temperature_1__engoiltemp1;
    static constexpr MessageId message_id = MessageId::et1_engine_temperature_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::et1_engine_temperature_1__engturbooiltemp> {
    using value_type = double;
    static constexpr SignalId id = SignalId::et1_engine_temperature_1__engturbooiltemp;
    static constexpr MessageId message_id = MessageId::et1_engine_temperature_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::et1_engine_temperature_1__engintercoolertemp> {
    using value_type = double;
    static constexpr SignalId id = SignalId::et1_engine_temperature_1__engintercoolertemp;
    static constexpr MessageId message_id = MessageId::et1_engine_temperature_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -40.0;
};
template <>
struct signal_traits<SignalId::et1_engine_temperature_1__engintercoolerthermostatopening> {
    using value_type = double;
    static constexpr SignalId id = SignalId::et1_engine_temperature_1__engintercoolerthermostatopening;
    static constexpr MessageId message_id = MessageId::et1_engine_temperature_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engfuelrate> {
    using value_type = double;
    static constexpr SignalId id = SignalId::lfe1_fuel_economy_liquid_1__engfuelrate;
    static constexpr MessageId message_id = MessageId::lfe1_fuel_economy_liquid_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.05;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::lfe1_fuel_economy_liquid_1__enginstantaneousfueleconomy> {
    using value_type = double;
    static constexpr SignalId id = SignalId::lfe1_fuel_economy_liquid_1__enginstantaneousfueleconomy;
    static constexpr MessageId message_id = MessageId::lfe1_fuel_economy_liquid_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.00195312;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engaveragefueleconomy> {
    using value_type = double;
    static constexpr SignalId id = SignalId::lfe1_fuel_economy_liquid_1__engaveragefueleconomy;
    static constexpr MessageId message_id = MessageId::lfe1_fuel_economy_liquid_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.00195312;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve1pos> {
    using value_type = double;
    static constexpr SignalId id = SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve1pos;
    static constexpr MessageId message_id = MessageId::lfe1_fuel_economy_liquid_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve2pos> {
    using value_type = double;
    static constexpr SignalId id = SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve2pos;
    static constexpr MessageId message_id = MessageId::lfe1_fuel_economy_liquid_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_header__controlbyte> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::transportprotocol_header__controlbyte;
    static constexpr MessageId message_id = MessageId::transportprotocol_header;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_header__totalmessagesizeeoma> {
    using value_type = std::uint16_t;
    static constexpr SignalId id = SignalId::transportprotocol_header__totalmessagesizeeoma;
    static constexpr MessageId message_id = MessageId::transportprotocol_header;
    static constexpr SignalType signal_type = SignalType::u16;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_header__connectionabortreason> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::transportprotocol_header__connectionabortreason;
    static constexpr MessageId message_id = MessageId::transportprotocol_header;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_header__totalmessagesize> {
    using value_type = std::uint16_t;
    static constexpr SignalId id = SignalId::transportprotocol_header__totalmessagesize;
    static constexpr MessageId message_id = MessageId::transportprotocol_header;
    static constexpr SignalType signal_type = SignalType::u16;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_header__numberofpacketsthatcanbesent> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::transportprotocol_header__numberofpacketsthatcanbesent;
    static constexpr MessageId message_id = MessageId::transportprotocol_header;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_header__totalmessagesizebam> {
    using value_type = std::uint16_t;
    static constexpr SignalId id = SignalId::transportprotocol_header__totalmessagesizebam;
    static constexpr MessageId message_id = MessageId::transportprotocol_header;
    static constexpr SignalType signal_type = SignalType::u16;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_header__nextpacketnumbertobesent> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::transportprotocol_header__nextpacketnumbertobesent;
    static constexpr MessageId message_id = MessageId::transportprotocol_header;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_header__totalnumberofpackets> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::transportprotocol_header__totalnumberofpackets;
    static constexpr MessageId message_id = MessageId::transportprotocol_header;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_header__totalnumberofpacketseoma> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::transportprotocol_header__totalnumberofpacketseoma;
    static constexpr MessageId message_id = MessageId::transportprotocol_header;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_header__totalnumberofpacketsbam> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::transportprotocol_header__totalnumberofpacketsbam;
    static constexpr MessageId message_id = MessageId::transportprotocol_header;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_header__maximumnumberofpackets> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::transportprotocol_header__maximumnumberofpackets;
    static constexpr MessageId message_id = MessageId::transportprotocol_header;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_header__pgnumber> {
    using value_type = std::uint32_t;
    static constexpr SignalId id = SignalId::transportprotocol_header__pgnumber;
    static constexpr MessageId message_id = MessageId::transportprotocol_header;
    static constexpr SignalType signal_type = SignalType::u32;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 24;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::transportprotocol_data__sequencenumber> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::transportprotocol_data__sequencenumber;
    static constexpr MessageId message_id = MessageId::transportprotocol_data;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm01_active_diagnostics__protectlampstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm01_active_diagnostics__protectlampstatus;
    static constexpr MessageId message_id = MessageId::dm01_active_diagnostics;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm01_active_diagnostics__amberwarninglampstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm01_active_diagnostics__amberwarninglampstatus;
    static constexpr MessageId message_id = MessageId::dm01_active_diagnostics;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 2;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm01_active_diagnostics__redstoplampstate> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm01_active_diagnostics__redstoplampstate;
    static constexpr MessageId message_id = MessageId::dm01_active_diagnostics;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 4;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus;
    static constexpr MessageId message_id = MessageId::dm01_active_diagnostics;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 6;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm01_active_diagnostics__flashprotectlamp> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm01_active_diagnostics__flashprotectlamp;
    static constexpr MessageId message_id = MessageId::dm01_active_diagnostics;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm01_active_diagnostics__flashamberwarninglamp> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm01_active_diagnostics__flashamberwarninglamp;
    static constexpr MessageId message_id = MessageId::dm01_active_diagnostics;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 10;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm01_active_diagnostics__flashredstoplamp> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm01_active_diagnostics__flashredstoplamp;
    static constexpr MessageId message_id = MessageId::dm01_active_diagnostics;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 12;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp;
    static constexpr MessageId message_id = MessageId::dm01_active_diagnostics;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 14;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm01_active_diagnostics__dtc1> {
    using value_type = std::uint32_t;
    static constexpr SignalId id = SignalId::dm01_active_diagnostics__dtc1;
    static constexpr MessageId message_id = MessageId::dm01_active_diagnostics;
    static constexpr SignalType signal_type = SignalType::u32;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 32;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_31__engoverridectrlmode> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_31__engoverridectrlmode;
    static constexpr MessageId message_id = MessageId::tsc1_31;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_31__engrequestedspeedctrlconditions> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_31__engrequestedspeedctrlconditions;
    static constexpr MessageId message_id = MessageId::tsc1_31;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 2;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_31__overridectrlmodepriority> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_31__overridectrlmodepriority;
    static constexpr MessageId message_id = MessageId::tsc1_31;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 4;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_31__engrequestedspeed_speedlimit> {
    using value_type = double;
    static constexpr SignalId id = SignalId::tsc1_31__engrequestedspeed_speedlimit;
    static constexpr MessageId message_id = MessageId::tsc1_31;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.125;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_31__engrequestedtorque_torquelimit> {
    using value_type = double;
    static constexpr SignalId id = SignalId::tsc1_31__engrequestedtorque_torquelimit;
    static constexpr MessageId message_id = MessageId::tsc1_31;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::tsc1_31__tsc1transrate> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_31__tsc1transrate;
    static constexpr MessageId message_id = MessageId::tsc1_31;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 3;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_31__tsc1ctrlpurpose> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_31__tsc1ctrlpurpose;
    static constexpr MessageId message_id = MessageId::tsc1_31;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 35;
    static constexpr std::uint8_t bit_length = 5;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_31__engrequestedtorquehighresolution> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_31__engrequestedtorquehighresolution;
    static constexpr MessageId message_id = MessageId::tsc1_31;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 0.125;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_31__messagecounter> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_31__messagecounter;
    static constexpr MessageId message_id = MessageId::tsc1_31;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_31__messagechecksum> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_31__messagechecksum;
    static constexpr MessageId message_id = MessageId::tsc1_31;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 60;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_intak> {
    using value_type = double;
    static constexpr SignalId id = SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_intak;
    static constexpr MessageId message_id = MessageId::cac1_charge_air_cooler_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie> {
    using value_type = double;
    static constexpr SignalId id = SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie;
    static constexpr MessageId message_id = MessageId::cac1_charge_air_cooler_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_effic> {
    using value_type = double;
    static constexpr SignalId id = SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_effic;
    static constexpr MessageId message_id = MessageId::cac1_charge_air_cooler_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::hours_engine_hours_revolutions__engine_total_hours_of_operation> {
    using value_type = double;
    static constexpr SignalId id = SignalId::hours_engine_hours_revolutions__engine_total_hours_of_operation;
    static constexpr MessageId message_id = MessageId::hours_engine_hours_revolutions;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 32;
    static constexpr double scale = 0.05;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::hours_engine_hours_revolutions__engine_total_revolutions_249> {
    using value_type = std::uint32_t;
    static constexpr SignalId id = SignalId::hours_engine_hours_revolutions__engine_total_revolutions_249;
    static constexpr MessageId message_id = MessageId::hours_engine_hours_revolutions;
    static constexpr SignalType signal_type = SignalType::u32;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 32;
    static constexpr double scale = 1000.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou> {
    using value_type = double;
    static constexpr SignalId id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou;
    static constexpr MessageId message_id = MessageId::tci5_turbocharger_information_5;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_2_turbine_ou> {
    using value_type = double;
    static constexpr SignalId id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_2_turbine_ou;
    static constexpr MessageId message_id = MessageId::tci5_turbocharger_information_5;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_3_turbine_ou> {
    using value_type = double;
    static constexpr SignalId id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_3_turbine_ou;
    static constexpr MessageId message_id = MessageId::tci5_turbocharger_information_5;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_4_turbine_ou> {
    using value_type = double;
    static constexpr SignalId id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_4_turbine_ou;
    static constexpr MessageId message_id = MessageId::tci5_turbocharger_information_5;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114> {
    using value_type = double;
    static constexpr SignalId id = SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114;
    static constexpr MessageId message_id = MessageId::vep1_vehicle_electrical_power_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::vep1_vehicle_electrical_power_1__alternator_current_115> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::vep1_vehicle_electrical_power_1__alternator_current_115;
    static constexpr MessageId message_id = MessageId::vep1_vehicle_electrical_power_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::vep1_vehicle_electrical_power_1__charging_system_potential_volta> {
    using value_type = double;
    static constexpr SignalId id = SignalId::vep1_vehicle_electrical_power_1__charging_system_potential_volta;
    static constexpr MessageId message_id = MessageId::vep1_vehicle_electrical_power_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.05;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::vep1_vehicle_electrical_power_1__battery_potential_power_input_1> {
    using value_type = double;
    static constexpr SignalId id = SignalId::vep1_vehicle_electrical_power_1__battery_potential_power_input_1;
    static constexpr MessageId message_id = MessageId::vep1_vehicle_electrical_power_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.05;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158> {
    using value_type = double;
    static constexpr SignalId id = SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158;
    static constexpr MessageId message_id = MessageId::vep1_vehicle_electrical_power_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.05;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::eec20_electronic_engine_control__absolute_engine_load> {
    using value_type = double;
    static constexpr SignalId id = SignalId::eec20_electronic_engine_control__absolute_engine_load;
    static constexpr MessageId message_id = MessageId::eec20_electronic_engine_control;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.025;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::easi_engine_air_system_info__engine_intake_maf> {
    using value_type = double;
    static constexpr SignalId id = SignalId::easi_engine_air_system_info__engine_intake_maf;
    static constexpr MessageId message_id = MessageId::easi_engine_air_system_info;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.000976562;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_03__engoverridectrlmode> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_03__engoverridectrlmode;
    static constexpr MessageId message_id = MessageId::tsc1_03;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_03__engrequestedspeedctrlconditions> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_03__engrequestedspeedctrlconditions;
    static constexpr MessageId message_id = MessageId::tsc1_03;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 2;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_03__overridectrlmodepriority> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_03__overridectrlmodepriority;
    static constexpr MessageId message_id = MessageId::tsc1_03;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 4;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_03__engrequestedspeed_speedlimit> {
    using value_type = double;
    static constexpr SignalId id = SignalId::tsc1_03__engrequestedspeed_speedlimit;
    static constexpr MessageId message_id = MessageId::tsc1_03;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.125;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_03__engrequestedtorque_torquelimit> {
    using value_type = double;
    static constexpr SignalId id = SignalId::tsc1_03__engrequestedtorque_torquelimit;
    static constexpr MessageId message_id = MessageId::tsc1_03;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::tsc1_03__tsc1transrate> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_03__tsc1transrate;
    static constexpr MessageId message_id = MessageId::tsc1_03;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 3;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_03__tsc1ctrlpurpose> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_03__tsc1ctrlpurpose;
    static constexpr MessageId message_id = MessageId::tsc1_03;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 35;
    static constexpr std::uint8_t bit_length = 5;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_03__engrequestedtorquehighresolution> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_03__engrequestedtorquehighresolution;
    static constexpr MessageId message_id = MessageId::tsc1_03;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 0.125;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_03__messagecounter> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_03__messagecounter;
    static constexpr MessageId message_id = MessageId::tsc1_03;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_03__messagechecksum> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_03__messagechecksum;
    static constexpr MessageId message_id = MessageId::tsc1_03;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 60;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_0b__engoverridectrlmode> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_0b__engoverridectrlmode;
    static constexpr MessageId message_id = MessageId::tsc1_0b;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_0b__engrequestedspeedctrlconditions> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_0b__engrequestedspeedctrlconditions;
    static constexpr MessageId message_id = MessageId::tsc1_0b;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 2;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_0b__overridectrlmodepriority> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_0b__overridectrlmodepriority;
    static constexpr MessageId message_id = MessageId::tsc1_0b;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 4;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_0b__engrequestedspeed_speedlimit> {
    using value_type = double;
    static constexpr SignalId id = SignalId::tsc1_0b__engrequestedspeed_speedlimit;
    static constexpr MessageId message_id = MessageId::tsc1_0b;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.125;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_0b__engrequestedtorque_torquelimit> {
    using value_type = double;
    static constexpr SignalId id = SignalId::tsc1_0b__engrequestedtorque_torquelimit;
    static constexpr MessageId message_id = MessageId::tsc1_0b;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::tsc1_0b__tsc1transrate> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_0b__tsc1transrate;
    static constexpr MessageId message_id = MessageId::tsc1_0b;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 3;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_0b__tsc1ctrlpurpose> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_0b__tsc1ctrlpurpose;
    static constexpr MessageId message_id = MessageId::tsc1_0b;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 35;
    static constexpr std::uint8_t bit_length = 5;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_0b__engrequestedtorquehighresolution> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_0b__engrequestedtorquehighresolution;
    static constexpr MessageId message_id = MessageId::tsc1_0b;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 0.125;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_0b__messagecounter> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_0b__messagecounter;
    static constexpr MessageId message_id = MessageId::tsc1_0b;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tsc1_0b__messagechecksum> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tsc1_0b__messagechecksum;
    static constexpr MessageId message_id = MessageId::tsc1_0b;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 60;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm07__testidentifier> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm07__testidentifier;
    static constexpr MessageId message_id = MessageId::dm07;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm07__spn1> {
    using value_type = std::uint16_t;
    static constexpr SignalId id = SignalId::dm07__spn1;
    static constexpr MessageId message_id = MessageId::dm07;
    static constexpr SignalType signal_type = SignalType::u16;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm07__failuremodeidentifier1> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm07__failuremodeidentifier1;
    static constexpr MessageId message_id = MessageId::dm07;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 5;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm07__spn1high> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm07__spn1high;
    static constexpr MessageId message_id = MessageId::dm07;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 29;
    static constexpr std::uint8_t bit_length = 3;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm08__testidentifier> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm08__testidentifier;
    static constexpr MessageId message_id = MessageId::dm08;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm08__testtype> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::dm08__testtype;
    static constexpr MessageId message_id = MessageId::dm08;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm08__testvalue> {
    using value_type = std::uint16_t;
    static constexpr SignalId id = SignalId::dm08__testvalue;
    static constexpr MessageId message_id = MessageId::dm08;
    static constexpr SignalType signal_type = SignalType::u16;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm08__testlimitmaximum> {
    using value_type = std::uint16_t;
    static constexpr SignalId id = SignalId::dm08__testlimitmaximum;
    static constexpr MessageId message_id = MessageId::dm08;
    static constexpr SignalType signal_type = SignalType::u16;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::dm08__testlimitminimum> {
    using value_type = std::uint16_t;
    static constexpr SignalId id = SignalId::dm08__testlimitminimum;
    static constexpr MessageId message_id = MessageId::dm08;
    static constexpr SignalType signal_type = SignalType::u16;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__retardertorquemode> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__retardertorquemode;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 4;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 6;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque> {
    using value_type = double;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque> {
    using value_type = double;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 26;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 28;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 30;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque> {
    using value_type = double;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderselectionnonengine> {
    using value_type = double;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__retarderselectionnonengine;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque> {
    using value_type = double;
    static constexpr SignalId id = SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque;
    static constexpr MessageId message_id = MessageId::erc1_electronic_retarder_cntrl;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged;
    static constexpr MessageId message_id = MessageId::etc1_electronic_trans_cntrl_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged;
    static constexpr MessageId message_id = MessageId::etc1_electronic_trans_cntrl_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 2;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess;
    static constexpr MessageId message_id = MessageId::etc1_electronic_trans_cntrl_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 4;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess;
    static constexpr MessageId message_id = MessageId::etc1_electronic_trans_cntrl_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 6;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transoutputshaftspeed> {
    using value_type = double;
    static constexpr SignalId id = SignalId::etc1_electronic_trans_cntrl_1__transoutputshaftspeed;
    static constexpr MessageId message_id = MessageId::etc1_electronic_trans_cntrl_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.125;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc1_electronic_trans_cntrl_1__percentclutchslip> {
    using value_type = double;
    static constexpr SignalId id = SignalId::etc1_electronic_trans_cntrl_1__percentclutchslip;
    static constexpr MessageId message_id = MessageId::etc1_electronic_trans_cntrl_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable;
    static constexpr MessageId message_id = MessageId::etc1_electronic_trans_cntrl_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable;
    static constexpr MessageId message_id = MessageId::etc1_electronic_trans_cntrl_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 34;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable;
    static constexpr MessageId message_id = MessageId::etc1_electronic_trans_cntrl_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 36;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transinputshaftspeed> {
    using value_type = double;
    static constexpr SignalId id = SignalId::etc1_electronic_trans_cntrl_1__transinputshaftspeed;
    static constexpr MessageId message_id = MessageId::etc1_electronic_trans_cntrl_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.125;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl;
    static constexpr MessageId message_id = MessageId::etc1_electronic_trans_cntrl_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transselectedgear> {
    using value_type = double;
    static constexpr SignalId id = SignalId::etc2_electronic_trans_cntrl_2__transselectedgear;
    static constexpr MessageId message_id = MessageId::etc2_electronic_trans_cntrl_2;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transactualgearratio> {
    using value_type = double;
    static constexpr SignalId id = SignalId::etc2_electronic_trans_cntrl_2__transactualgearratio;
    static constexpr MessageId message_id = MessageId::etc2_electronic_trans_cntrl_2;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.001;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear> {
    using value_type = double;
    static constexpr SignalId id = SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear;
    static constexpr MessageId message_id = MessageId::etc2_electronic_trans_cntrl_2;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = -125.0;
};
template <>
struct signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange> {
    using value_type = std::uint16_t;
    static constexpr SignalId id = SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange;
    static constexpr MessageId message_id = MessageId::etc2_electronic_trans_cntrl_2;
    static constexpr SignalType signal_type = SignalType::u16;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::big_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 39;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange> {
    using value_type = std::uint16_t;
    static constexpr SignalId id = SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange;
    static constexpr MessageId message_id = MessageId::etc2_electronic_trans_cntrl_2;
    static constexpr SignalType signal_type = SignalType::u16;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::big_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 55;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::rqst_00_5e__parametergroupnumber> {
    using value_type = std::uint32_t;
    static constexpr SignalId id = SignalId::rqst_00_5e__parametergroupnumber;
    static constexpr MessageId message_id = MessageId::rqst_00_5e;
    static constexpr SignalType signal_type = SignalType::u32;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 24;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::rqst_00_21__parametergroupnumber> {
    using value_type = std::uint32_t;
    static constexpr SignalId id = SignalId::rqst_00_21__parametergroupnumber;
    static constexpr MessageId message_id = MessageId::rqst_00_21;
    static constexpr SignalType signal_type = SignalType::u32;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 24;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::rqst_global_5e__parametergroupnumber> {
    using value_type = std::uint32_t;
    static constexpr SignalId id = SignalId::rqst_global_5e__parametergroupnumber;
    static constexpr MessageId message_id = MessageId::rqst_global_5e;
    static constexpr SignalType signal_type = SignalType::u32;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 24;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::rqst_global_03__parametergroupnumber> {
    using value_type = std::uint32_t;
    static constexpr SignalId id = SignalId::rqst_global_03__parametergroupnumber;
    static constexpr MessageId message_id = MessageId::rqst_global_03;
    static constexpr SignalType signal_type = SignalType::u32;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 24;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tci_transfer_case_information__transfercasestatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tci_transfer_case_information__transfercasestatus;
    static constexpr MessageId message_id = MessageId::tci_transfer_case_information;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 3;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tci_transfer_case_information__dirstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tci_transfer_case_information__dirstatus;
    static constexpr MessageId message_id = MessageId::tci_transfer_case_information;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 3;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tci_transfer_case_information__actualgearratio> {
    using value_type = double;
    static constexpr SignalId id = SignalId::tci_transfer_case_information__actualgearratio;
    static constexpr MessageId message_id = MessageId::tci_transfer_case_information;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.01;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tci_transfer_case_information__messagecounter> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tci_transfer_case_information__messagecounter;
    static constexpr MessageId message_id = MessageId::tci_transfer_case_information;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::tci_transfer_case_information__messagechecksum> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::tci_transfer_case_information__messagechecksum;
    static constexpr MessageId message_id = MessageId::tci_transfer_case_information;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 60;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::trf1_transmission_fluids_1__clutchpress> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::trf1_transmission_fluids_1__clutchpress;
    static constexpr MessageId message_id = MessageId::trf1_transmission_fluids_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 16.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1> {
    using value_type = double;
    static constexpr SignalId id = SignalId::trf1_transmission_fluids_1__transoillevel1;
    static constexpr MessageId message_id = MessageId::trf1_transmission_fluids_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::trf1_transmission_fluids_1__transfilterdiffpress> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::trf1_transmission_fluids_1__transfilterdiffpress;
    static constexpr MessageId message_id = MessageId::trf1_transmission_fluids_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 2.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::trf1_transmission_fluids_1__transoilpress> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::trf1_transmission_fluids_1__transoilpress;
    static constexpr MessageId message_id = MessageId::trf1_transmission_fluids_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 16.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::trf1_transmission_fluids_1__transoiltemp1> {
    using value_type = double;
    static constexpr SignalId id = SignalId::trf1_transmission_fluids_1__transoiltemp1;
    static constexpr MessageId message_id = MessageId::trf1_transmission_fluids_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.03125;
    static constexpr double offset = -273.0;
};
template <>
struct signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1high_low> {
    using value_type = double;
    static constexpr SignalId id = SignalId::trf1_transmission_fluids_1__transoillevel1high_low;
    static constexpr MessageId message_id = MessageId::trf1_transmission_fluids_1;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.5;
    static constexpr double offset = -62.5;
};
template <>
struct signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer;
    static constexpr MessageId message_id = MessageId::trf1_transmission_fluids_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus;
    static constexpr MessageId message_id = MessageId::trf1_transmission_fluids_1;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 60;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit;
    static constexpr MessageId message_id = MessageId::ccss_cruise_control_vehicle_spd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed;
    static constexpr MessageId message_id = MessageId::ccss_cruise_control_vehicle_spd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed;
    static constexpr MessageId message_id = MessageId::ccss_cruise_control_vehicle_spd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit6808> {
    using value_type = double;
    static constexpr SignalId id = SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit6808;
    static constexpr MessageId message_id = MessageId::ccss_cruise_control_vehicle_spd;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.00390625;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd;
    static constexpr MessageId message_id = MessageId::ccss_cruise_control_vehicle_spd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport;
    static constexpr MessageId message_id = MessageId::ccss_cruise_control_vehicle_spd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport;
    static constexpr MessageId message_id = MessageId::ccss_cruise_control_vehicle_spd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 50;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport;
    static constexpr MessageId message_id = MessageId::ccss_cruise_control_vehicle_spd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 52;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport;
    static constexpr MessageId message_id = MessageId::ccss_cruise_control_vehicle_spd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 54;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype;
    static constexpr MessageId message_id = MessageId::ccss_cruise_control_vehicle_spd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 4;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 2;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 4;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 6;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__wheelbasedvehiclespeed> {
    using value_type = double;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__wheelbasedvehiclespeed;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 16;
    static constexpr double scale = 0.00390625;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 26;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__brakeswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__brakeswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 28;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__clutchswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__clutchswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 30;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 34;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 36;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 38;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 5;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 53;
    static constexpr std::uint8_t bit_length = 3;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 58;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 60;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch;
    static constexpr MessageId message_id = MessageId::ccvs1_cruise_control_vehspd;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 62;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 2;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 4;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 6;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__brakepedalpos> {
    using value_type = double;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__brakepedalpos;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 8;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 18;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 20;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 22;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__engderateswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__engderateswitch;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 26;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 28;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 30;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__engretarderselection> {
    using value_type = double;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__engretarderselection;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::f64;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 0.4;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__absfullyoperational> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__absfullyoperational;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 40;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 42;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 44;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 46;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = false;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 8;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__railroadmodesw> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__railroadmodesw;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 58;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 60;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal;
    static constexpr MessageId message_id = MessageId::ebc1_electronic_brake_cntrl;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 62;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engidleshutdownhasshutdowneng> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engidleshutdownhasshutdowneng;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 0;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engidleshutdowndriveralertmode> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engidleshutdowndriveralertmode;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 2;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engidleshutdowntimeroverride> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engidleshutdowntimeroverride;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 4;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engidleshutdowntimerstate> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engidleshutdowntimerstate;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 6;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engidleshutdowntimerfunction> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engidleshutdowntimerfunction;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 14;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__a_chighpressfanswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__a_chighpressfanswitch;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 16;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__refrigerantlowpressswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__refrigerantlowpressswitch;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 18;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__refrigeranthighpressswitch> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__refrigeranthighpressswitch;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 20;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engwaittostartlamp> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engwaittostartlamp;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 24;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engprtectionsystemhasshutdowneng> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engprtectionsystemhasshutdowneng;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 32;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engprtctnsystmapprachingshutdown> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engprtctnsystmapprachingshutdown;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 34;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engprotectionsystemtimeroverride> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engprotectionsystemtimeroverride;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 36;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engprotectionsystemtimerstate> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engprotectionsystemtimerstate;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 38;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engprotectionsystemconfig> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engprotectionsystemconfig;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 46;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engalarmacknowledge> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engalarmacknowledge;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 48;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engalarmoutputcmdstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engalarmoutputcmdstatus;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 50;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engairshutoffcmdstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engairshutoffcmdstatus;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 52;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engoverspeedtest> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engoverspeedtest;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 54;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engairshutoffstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engairshutoffstatus;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 56;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__ptoshutdownhasshutdowneng> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__ptoshutdownhasshutdowneng;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 58;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__clntlvlengprtctionshutdownstatus> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__clntlvlengprtctionshutdownstatus;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 60;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};
template <>
struct signal_traits<SignalId::shutdn__engoilpresssw> {
    using value_type = std::uint8_t;
    static constexpr SignalId id = SignalId::shutdn__engoilpresssw;
    static constexpr MessageId message_id = MessageId::shutdn;
    static constexpr SignalType signal_type = SignalType::u8;
    static constexpr bool has_choices = true;
    static constexpr ByteOrder byte_order = ByteOrder::little_endian;
    static constexpr bool is_signed = false;
    static constexpr std::uint16_t start_bit = 62;
    static constexpr std::uint8_t bit_length = 2;
    static constexpr double scale = 1.0;
    static constexpr double offset = 0.0;
};

template <SignalId Id>
using signal_value_t = typename signal_traits<Id>::value_type;

} // namespace duramax