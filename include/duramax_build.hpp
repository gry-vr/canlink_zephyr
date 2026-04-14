#pragma once

#include "duramax_metadata.hpp"
#include "duramax_store.hpp"
#include "duramax_types.hpp"

#include <expected>

namespace duramax {

enum class BuildError : std::uint8_t {
    missing_signal,
    type_mismatch,
    unsupported_message
};

auto build_eec5_electronic_engine_control_5_from_store(const ValueStore& store)
    -> std::expected<Eec5ElectronicEngineControl5, BuildError>;
auto build_eec9_electronic_engine_control_9_from_store(const ValueStore& store)
    -> std::expected<Eec9ElectronicEngineControl9, BuildError>;
auto build_ebcc_engine_exhaust_brake_cont_from_store(const ValueStore& store)
    -> std::expected<EbccEngineExhaustBrakeCont, BuildError>;
auto build_et3_engine_temperature_3_from_store(const ValueStore& store)
    -> std::expected<Et3EngineTemperature3, BuildError>;
auto build_dm21_diagnostic_readiness_2_from_store(const ValueStore& store)
    -> std::expected<Dm21DiagnosticReadiness2, BuildError>;
auto build_dm26_diagnostic_readiness_3_from_store(const ValueStore& store)
    -> std::expected<Dm26DiagnosticReadiness3, BuildError>;
auto build_ic1_intake_exhaust_cond_1_from_store(const ValueStore& store)
    -> std::expected<Ic1IntakeExhaustCond1, BuildError>;
auto build_amb_ambient_conditions_from_store(const ValueStore& store)
    -> std::expected<AmbAmbientConditions, BuildError>;
auto build_eec1_electronic_engine_control_1_from_store(const ValueStore& store)
    -> std::expected<Eec1ElectronicEngineControl1, BuildError>;
auto build_eec2_electronic_engine_control_2_from_store(const ValueStore& store)
    -> std::expected<Eec2ElectronicEngineControl2, BuildError>;
auto build_eec3_electronic_engine_control_3_from_store(const ValueStore& store)
    -> std::expected<Eec3ElectronicEngineControl3, BuildError>;
auto build_efl_p1_eng_fluid_level_press_1_from_store(const ValueStore& store)
    -> std::expected<EflP1EngFluidLevelPress1, BuildError>;
auto build_efl_p2_eng_fluid_level_press_2_from_store(const ValueStore& store)
    -> std::expected<EflP2EngFluidLevelPress2, BuildError>;
auto build_et1_engine_temperature_1_from_store(const ValueStore& store)
    -> std::expected<Et1EngineTemperature1, BuildError>;
auto build_lfe1_fuel_economy_liquid_1_from_store(const ValueStore& store)
    -> std::expected<Lfe1FuelEconomyLiquid1, BuildError>;
auto build_transportprotocol_header_from_store(const ValueStore& store)
    -> std::expected<TransportprotocolHeader, BuildError>;
auto build_transportprotocol_data_from_store(const ValueStore& store)
    -> std::expected<TransportprotocolData, BuildError>;
auto build_dm01_active_diagnostics_from_store(const ValueStore& store)
    -> std::expected<Dm01ActiveDiagnostics, BuildError>;
auto build_tsc1_31_from_store(const ValueStore& store)
    -> std::expected<Tsc131, BuildError>;
auto build_cac1_charge_air_cooler_1_from_store(const ValueStore& store)
    -> std::expected<Cac1ChargeAirCooler1, BuildError>;
auto build_hours_engine_hours_revolutions_from_store(const ValueStore& store)
    -> std::expected<HoursEngineHoursRevolutions, BuildError>;
auto build_tci5_turbocharger_information_5_from_store(const ValueStore& store)
    -> std::expected<Tci5TurbochargerInformation5, BuildError>;
auto build_vep1_vehicle_electrical_power_1_from_store(const ValueStore& store)
    -> std::expected<Vep1VehicleElectricalPower1, BuildError>;
auto build_eec20_electronic_engine_control_from_store(const ValueStore& store)
    -> std::expected<Eec20ElectronicEngineControl, BuildError>;
auto build_easi_engine_air_system_info_from_store(const ValueStore& store)
    -> std::expected<EasiEngineAirSystemInfo, BuildError>;
auto build_tsc1_03_from_store(const ValueStore& store)
    -> std::expected<Tsc103, BuildError>;
auto build_tsc1_0b_from_store(const ValueStore& store)
    -> std::expected<Tsc10b, BuildError>;
auto build_dm07_from_store(const ValueStore& store)
    -> std::expected<Dm07, BuildError>;
auto build_dm08_from_store(const ValueStore& store)
    -> std::expected<Dm08, BuildError>;
auto build_erc1_electronic_retarder_cntrl_from_store(const ValueStore& store)
    -> std::expected<Erc1ElectronicRetarderCntrl, BuildError>;
auto build_etc1_electronic_trans_cntrl_1_from_store(const ValueStore& store)
    -> std::expected<Etc1ElectronicTransCntrl1, BuildError>;
auto build_etc2_electronic_trans_cntrl_2_from_store(const ValueStore& store)
    -> std::expected<Etc2ElectronicTransCntrl2, BuildError>;
auto build_rqst_00_5e_from_store(const ValueStore& store)
    -> std::expected<Rqst005e, BuildError>;
auto build_rqst_00_21_from_store(const ValueStore& store)
    -> std::expected<Rqst0021, BuildError>;
auto build_rqst_global_5e_from_store(const ValueStore& store)
    -> std::expected<RqstGlobal5e, BuildError>;
auto build_rqst_global_03_from_store(const ValueStore& store)
    -> std::expected<RqstGlobal03, BuildError>;
auto build_tci_transfer_case_information_from_store(const ValueStore& store)
    -> std::expected<TciTransferCaseInformation, BuildError>;
auto build_trf1_transmission_fluids_1_from_store(const ValueStore& store)
    -> std::expected<Trf1TransmissionFluids1, BuildError>;
auto build_ccss_cruise_control_vehicle_spd_from_store(const ValueStore& store)
    -> std::expected<CcssCruiseControlVehicleSpd, BuildError>;
auto build_ccvs1_cruise_control_vehspd_from_store(const ValueStore& store)
    -> std::expected<Ccvs1CruiseControlVehspd, BuildError>;
auto build_ebc1_electronic_brake_cntrl_from_store(const ValueStore& store)
    -> std::expected<Ebc1ElectronicBrakeCntrl, BuildError>;
auto build_shutdn_from_store(const ValueStore& store)
    -> std::expected<Shutdn, BuildError>;

auto build_message_from_store(MessageId id, const ValueStore& store)
    -> std::expected<MessageVariant, BuildError>;

} // namespace duramax