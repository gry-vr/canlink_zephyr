#pragma once

#include "duramax_ids.hpp"

#include <cstdint>
#include <variant>

namespace duramax {

struct Eec5ElectronicEngineControl5 {
    static constexpr MessageId id = MessageId::eec5_electronic_engine_control_5;

    double engine_turbocharger_1_calculated{};
    double commanded_vgt_position{};
    std::uint8_t engine_variable_geometry_turboch{};
    std::uint8_t engine_fuel_control_control_mode{};
    std::uint8_t engine_vgt_control_mode{};
    double actual_vgt_position{};
};

struct Eec9ElectronicEngineControl9 {
    static constexpr MessageId id = MessageId::eec9_electronic_engine_control_9;

    double engine_exhaust_gas_recirculation{};
    double commanded_fuel_rail_pressure{};
    double commanded_engine_fuel_injection{};
};

struct EbccEngineExhaustBrakeCont {
    static constexpr MessageId id = MessageId::ebcc_engine_exhaust_brake_cont;

    std::uint8_t actual_boost_pressure{};
    std::uint8_t desired_boost_pressure{};
    double engine_exhaust_brake_actuator_co{};
    std::uint8_t engine_turbocharger_2_turbine_ou{};
    std::uint8_t desired_engine_turbocharger_2_tu{};
};

struct Et3EngineTemperature3 {
    static constexpr MessageId id = MessageId::et3_engine_temperature_3;

    double engine_intake_manifold_1_air_tem{};
    double engine_coolant_temperature_high{};
    double engine_intake_valve_actuation_sy{};
    double engine_cac_outlet_temperature{};
};

struct Dm21DiagnosticReadiness2 {
    static constexpr MessageId id = MessageId::dm21_diagnostic_readiness_2;

    std::uint16_t engine_run_time_with_mil_on{};
};

struct Dm26DiagnosticReadiness3 {
    static constexpr MessageId id = MessageId::dm26_diagnostic_readiness_3;

    std::uint16_t time_since_engine_start{};
};

struct Ic1IntakeExhaustCond1 {
    static constexpr MessageId id = MessageId::ic1_intake_exhaust_cond_1;

    double aft1dpfinpress{};
    std::uint8_t engintakemanifold1press{};
    double engintakemanifold1temp{};
    std::uint8_t engairintakepress{};
    double engairfilter1diffpress{};
    double engexhaustgastemp{};
    double engcoolantfilterdiffpress{};
};

struct AmbAmbientConditions {
    static constexpr MessageId id = MessageId::amb_ambient_conditions;

    double barometric_pressurebarometric_pr{};
    double cabinteriortemp{};
    double ambient_air_temperature{};
    double engine_air_intake_temperature{};
    double roadsurfacetemp{};
};

struct Eec1ElectronicEngineControl1 {
    static constexpr MessageId id = MessageId::eec1_electronic_engine_control_1;

    std::uint8_t engine_torque_mode{};
    std::uint8_t actlengprcnttorquehighresolution{};
    double drivers_demand_engine_prcnt_torq{};
    double actual_engine_percent_torque{};
    double engine_speed{};
    std::uint8_t srcaddrssofcntrllngdvcforengctrl{};
    std::uint8_t engstartermode{};
    double engine_demand_percent_torque{};
};

struct Eec2ElectronicEngineControl2 {
    static constexpr MessageId id = MessageId::eec2_electronic_engine_control_2;

    std::uint8_t accelpedal1lowidleswitch{};
    std::uint8_t accelpedalkickdownswitch{};
    std::uint8_t roadspeedlimitstatus{};
    std::uint8_t accelpedal2lowidleswitch{};
    double accelpedalpos1{};
    std::uint8_t engpercentloadatcurrentspeed{};
    double remoteaccelpedalpos{};
    double accelpedalpos2{};
    std::uint8_t vhcleaccelerationratelimitstatus{};
    std::uint8_t mmntaryengmaxpowerenablefeedback{};
    std::uint8_t dpfthermalmanagementactive{};
    std::uint8_t scrthermalmanagementactive{};
    double actlmaxavailableengpercenttorque{};
    double estpumpingpercenttorque{};
};

struct Eec3ElectronicEngineControl3 {
    static constexpr MessageId id = MessageId::eec3_electronic_engine_control_3;

    double nominalfrictionpercenttorque{};
    double enginesdesiredoperatingspeed{};
    std::uint8_t engnsdsrdoprtngspdasymmtryadjstm{};
    double estengprsiticlossespercenttorque{};
    double aft1exhgasmfr{};
    std::uint8_t aft1indewpoint{};
    std::uint8_t aft1exhdewpoint{};
    std::uint8_t aft2indewpoint{};
    std::uint8_t aft2exhdewpoint{};
};

struct EflP1EngFluidLevelPress1 {
    static constexpr MessageId id = MessageId::efl_p1_eng_fluid_level_press_1;

    std::uint8_t engfueldeliverypress{};
    double engexcrankcaseblowbypress{};
    double engoillevel{};
    std::uint8_t engoilpress{};
    double engcrankcasepress{};
    std::uint8_t engcoolantpress{};
    double engcoolantlevel{};
};

struct EflP2EngFluidLevelPress2 {
    static constexpr MessageId id = MessageId::efl_p2_eng_fluid_level_press_2;

    double enginjectionctrlpress{};
    double enginjectormeteringrail1press{};
    double enginjectortimingrail1press{};
    double enginjectormeteringrail2press{};
};

struct Et1EngineTemperature1 {
    static constexpr MessageId id = MessageId::et1_engine_temperature_1;

    double engcoolanttemp{};
    double engfueltemp1{};
    double engoiltemp1{};
    double engturbooiltemp{};
    double engintercoolertemp{};
    double engintercoolerthermostatopening{};
};

struct Lfe1FuelEconomyLiquid1 {
    static constexpr MessageId id = MessageId::lfe1_fuel_economy_liquid_1;

    double engfuelrate{};
    double enginstantaneousfueleconomy{};
    double engaveragefueleconomy{};
    double engthrottlevalve1pos{};
    double engthrottlevalve2pos{};
};

struct TransportprotocolHeader {
    static constexpr MessageId id = MessageId::transportprotocol_header;

    std::uint8_t controlbyte{};
    std::uint16_t totalmessagesizeeoma{};
    std::uint8_t connectionabortreason{};
    std::uint16_t totalmessagesize{};
    std::uint8_t numberofpacketsthatcanbesent{};
    std::uint16_t totalmessagesizebam{};
    std::uint8_t nextpacketnumbertobesent{};
    std::uint8_t totalnumberofpackets{};
    std::uint8_t totalnumberofpacketseoma{};
    std::uint8_t totalnumberofpacketsbam{};
    std::uint8_t maximumnumberofpackets{};
    std::uint32_t pgnumber{};
};

struct TransportprotocolData {
    static constexpr MessageId id = MessageId::transportprotocol_data;

    std::uint8_t sequencenumber{};
};

struct Dm01ActiveDiagnostics {
    static constexpr MessageId id = MessageId::dm01_active_diagnostics;

    std::uint8_t protectlampstatus{};
    std::uint8_t amberwarninglampstatus{};
    std::uint8_t redstoplampstate{};
    std::uint8_t malfunctionindicatorlampstatus{};
    std::uint8_t flashprotectlamp{};
    std::uint8_t flashamberwarninglamp{};
    std::uint8_t flashredstoplamp{};
    std::uint8_t flashmalfuncindicatorlamp{};
    std::uint32_t dtc1{};
};

struct Tsc131 {
    static constexpr MessageId id = MessageId::tsc1_31;

    std::uint8_t engoverridectrlmode{};
    std::uint8_t engrequestedspeedctrlconditions{};
    std::uint8_t overridectrlmodepriority{};
    double engrequestedspeed_speedlimit{};
    double engrequestedtorque_torquelimit{};
    std::uint8_t tsc1transrate{};
    std::uint8_t tsc1ctrlpurpose{};
    std::uint8_t engrequestedtorquehighresolution{};
    std::uint8_t messagecounter{};
    std::uint8_t messagechecksum{};
};

struct Cac1ChargeAirCooler1 {
    static constexpr MessageId id = MessageId::cac1_charge_air_cooler_1;

    double engine_charge_air_cooler_1_intak{};
    double engine_charge_air_cooler_1_ambie{};
    double engine_charge_air_cooler_1_effic{};
};

struct HoursEngineHoursRevolutions {
    static constexpr MessageId id = MessageId::hours_engine_hours_revolutions;

    double engine_total_hours_of_operation{};
    std::uint32_t engine_total_revolutions_249{};
};

struct Tci5TurbochargerInformation5 {
    static constexpr MessageId id = MessageId::tci5_turbocharger_information_5;

    double engine_turbocharger_1_turbine_ou{};
    double engine_turbocharger_2_turbine_ou{};
    double engine_turbocharger_3_turbine_ou{};
    double engine_turbocharger_4_turbine_ou{};
};

struct Vep1VehicleElectricalPower1 {
    static constexpr MessageId id = MessageId::vep1_vehicle_electrical_power_1;

    double net_battery_current_114{};
    std::uint8_t alternator_current_115{};
    double charging_system_potential_volta{};
    double battery_potential_power_input_1{};
    double keyswitch_battery_potential_158{};
};

struct Eec20ElectronicEngineControl {
    static constexpr MessageId id = MessageId::eec20_electronic_engine_control;

    double absolute_engine_load{};
};

struct EasiEngineAirSystemInfo {
    static constexpr MessageId id = MessageId::easi_engine_air_system_info;

    double engine_intake_maf{};
};

struct Tsc103 {
    static constexpr MessageId id = MessageId::tsc1_03;

    std::uint8_t engoverridectrlmode{};
    std::uint8_t engrequestedspeedctrlconditions{};
    std::uint8_t overridectrlmodepriority{};
    double engrequestedspeed_speedlimit{};
    double engrequestedtorque_torquelimit{};
    std::uint8_t tsc1transrate{};
    std::uint8_t tsc1ctrlpurpose{};
    std::uint8_t engrequestedtorquehighresolution{};
    std::uint8_t messagecounter{};
    std::uint8_t messagechecksum{};
};

struct Tsc10b {
    static constexpr MessageId id = MessageId::tsc1_0b;

    std::uint8_t engoverridectrlmode{};
    std::uint8_t engrequestedspeedctrlconditions{};
    std::uint8_t overridectrlmodepriority{};
    double engrequestedspeed_speedlimit{};
    double engrequestedtorque_torquelimit{};
    std::uint8_t tsc1transrate{};
    std::uint8_t tsc1ctrlpurpose{};
    std::uint8_t engrequestedtorquehighresolution{};
    std::uint8_t messagecounter{};
    std::uint8_t messagechecksum{};
};

struct Dm07 {
    static constexpr MessageId id = MessageId::dm07;

    std::uint8_t testidentifier{};
    std::uint16_t spn1{};
    std::uint8_t failuremodeidentifier1{};
    std::uint8_t spn1high{};
};

struct Dm08 {
    static constexpr MessageId id = MessageId::dm08;

    std::uint8_t testidentifier{};
    std::uint8_t testtype{};
    std::uint16_t testvalue{};
    std::uint16_t testlimitmaximum{};
    std::uint16_t testlimitminimum{};
};

struct Erc1ElectronicRetarderCntrl {
    static constexpr MessageId id = MessageId::erc1_electronic_retarder_cntrl;

    std::uint8_t retardertorquemode{};
    std::uint8_t retarderenablebrakeassistswitch{};
    std::uint8_t retarderenableshiftassistswitch{};
    double actualretarderpercenttorque{};
    double intendedretarderpercenttorque{};
    std::uint8_t engcoolantloadincrease{};
    std::uint8_t retarderrequestingbrakelight{};
    std::uint8_t retarderroadspeedlimitswitch{};
    std::uint8_t retarderroadspeedexceededstatus{};
    std::uint8_t srcaddrssofcntrllngdvcfrrtrdrctr{};
    double drvrsdemandretarderpercenttorque{};
    double retarderselectionnonengine{};
    double actlmxavlblretarderpercenttorque{};
};

struct Etc1ElectronicTransCntrl1 {
    static constexpr MessageId id = MessageId::etc1_electronic_trans_cntrl_1;

    std::uint8_t transdrivelineengaged{};
    std::uint8_t trnstorqueconverterlockupengaged{};
    std::uint8_t transshiftinprocess{};
    std::uint8_t trnstrqcnvrtrlckptrnstninprocess{};
    double transoutputshaftspeed{};
    double percentclutchslip{};
    std::uint8_t engmomentaryoverspeedenable{};
    std::uint8_t progressiveshiftdisable{};
    std::uint8_t momentaryengmaxpowerenable{};
    double transinputshaftspeed{};
    std::uint8_t srcaddrssofcntrllngdvcfrtrnsctrl{};
};

struct Etc2ElectronicTransCntrl2 {
    static constexpr MessageId id = MessageId::etc2_electronic_trans_cntrl_2;

    double transselectedgear{};
    double transactualgearratio{};
    double transcurrentgear{};
    std::uint16_t transrequestedrange{};
    std::uint16_t transcurrentrange{};
};

struct Rqst005e {
    static constexpr MessageId id = MessageId::rqst_00_5e;

    std::uint32_t parametergroupnumber{};
};

struct Rqst0021 {
    static constexpr MessageId id = MessageId::rqst_00_21;

    std::uint32_t parametergroupnumber{};
};

struct RqstGlobal5e {
    static constexpr MessageId id = MessageId::rqst_global_5e;

    std::uint32_t parametergroupnumber{};
};

struct RqstGlobal03 {
    static constexpr MessageId id = MessageId::rqst_global_03;

    std::uint32_t parametergroupnumber{};
};

struct TciTransferCaseInformation {
    static constexpr MessageId id = MessageId::tci_transfer_case_information;

    std::uint8_t transfercasestatus{};
    std::uint8_t dirstatus{};
    double actualgearratio{};
    std::uint8_t messagecounter{};
    std::uint8_t messagechecksum{};
};

struct Trf1TransmissionFluids1 {
    static constexpr MessageId id = MessageId::trf1_transmission_fluids_1;

    std::uint8_t clutchpress{};
    double transoillevel1{};
    std::uint8_t transfilterdiffpress{};
    std::uint8_t transoilpress{};
    double transoiltemp1{};
    double transoillevel1high_low{};
    std::uint8_t transoillevel1countdowntimer{};
    std::uint8_t transoillevel1measurementstatus{};
};

struct CcssCruiseControlVehicleSpd {
    static constexpr MessageId id = MessageId::ccss_cruise_control_vehicle_spd;

    std::uint8_t maxvehiclespeedlimit{};
    std::uint8_t cruisectrlhighsetlimitspeed{};
    std::uint8_t cruisectrllowsetlimitspeed{};
    double maxvehiclespeedlimit6808{};
    std::uint8_t ctrlsyslowsetlmtspd{};
    std::uint8_t ctrldiscmdsupport{};
    std::uint8_t ctrlresumecmdsupport{};
    std::uint8_t ctrlpausecmdsupport{};
    std::uint8_t ctrlsetcmdsupport{};
    std::uint8_t powertrainadaptivecctype{};
};

struct Ccvs1CruiseControlVehspd {
    static constexpr MessageId id = MessageId::ccvs1_cruise_control_vehspd;

    std::uint8_t twospeedaxleswitch{};
    std::uint8_t parkingbrakeswitch{};
    std::uint8_t cruisectrlpauseswitch{};
    std::uint8_t parkbrakereleaseinhibitrq{};
    double wheelbasedvehiclespeed{};
    std::uint8_t cruisectrlactive{};
    std::uint8_t cruisectrlenableswitch{};
    std::uint8_t brakeswitch{};
    std::uint8_t clutchswitch{};
    std::uint8_t cruisectrlsetswitch{};
    std::uint8_t cruisectrlcoastswitch{};
    std::uint8_t cruisectrlresumeswitch{};
    std::uint8_t cruisectrlaccelerateswitch{};
    std::uint8_t cruisectrlsetspeed{};
    std::uint8_t ptogovernorstate{};
    std::uint8_t cruisectrlstates{};
    std::uint8_t engidleincrementswitch{};
    std::uint8_t engidledecrementswitch{};
    std::uint8_t engtestmodeswitch{};
    std::uint8_t engshutdownoverrideswitch{};
};

struct Ebc1ElectronicBrakeCntrl {
    static constexpr MessageId id = MessageId::ebc1_electronic_brake_cntrl;

    std::uint8_t asrengctrlactive{};
    std::uint8_t asrbrakectrlactive{};
    std::uint8_t antilockbrakingactive{};
    std::uint8_t ebsbrakeswitch{};
    double brakepedalpos{};
    std::uint8_t absoffroadswitch{};
    std::uint8_t asroffroadswitch{};
    std::uint8_t asrhillholderswitch{};
    std::uint8_t tractionctrloverrideswitch{};
    std::uint8_t accelinterlockswitch{};
    std::uint8_t engderateswitch{};
    std::uint8_t engauxshutdownswitch{};
    std::uint8_t remoteaccelenableswitch{};
    double engretarderselection{};
    std::uint8_t absfullyoperational{};
    std::uint8_t ebsredwarningsignal{};
    std::uint8_t abs_ebsamberwarningsignal{};
    std::uint8_t atc_asrinformationsignal{};
    std::uint8_t srcaddrssofcntrllngdvcfrbrkectrl{};
    std::uint8_t railroadmodesw{};
    std::uint8_t haltbrakeswitch{};
    std::uint8_t trailerabsstatus{};
    std::uint8_t trctrmntdtrailerabswarningsignal{};
};

struct Shutdn {
    static constexpr MessageId id = MessageId::shutdn;

    std::uint8_t engidleshutdownhasshutdowneng{};
    std::uint8_t engidleshutdowndriveralertmode{};
    std::uint8_t engidleshutdowntimeroverride{};
    std::uint8_t engidleshutdowntimerstate{};
    std::uint8_t engidleshutdowntimerfunction{};
    std::uint8_t a_chighpressfanswitch{};
    std::uint8_t refrigerantlowpressswitch{};
    std::uint8_t refrigeranthighpressswitch{};
    std::uint8_t engwaittostartlamp{};
    std::uint8_t engprtectionsystemhasshutdowneng{};
    std::uint8_t engprtctnsystmapprachingshutdown{};
    std::uint8_t engprotectionsystemtimeroverride{};
    std::uint8_t engprotectionsystemtimerstate{};
    std::uint8_t engprotectionsystemconfig{};
    std::uint8_t engalarmacknowledge{};
    std::uint8_t engalarmoutputcmdstatus{};
    std::uint8_t engairshutoffcmdstatus{};
    std::uint8_t engoverspeedtest{};
    std::uint8_t engairshutoffstatus{};
    std::uint8_t ptoshutdownhasshutdowneng{};
    std::uint8_t clntlvlengprtctionshutdownstatus{};
    std::uint8_t engoilpresssw{};
};

using MessageVariant = std::variant<
    Eec5ElectronicEngineControl5,
    Eec9ElectronicEngineControl9,
    EbccEngineExhaustBrakeCont,
    Et3EngineTemperature3,
    Dm21DiagnosticReadiness2,
    Dm26DiagnosticReadiness3,
    Ic1IntakeExhaustCond1,
    AmbAmbientConditions,
    Eec1ElectronicEngineControl1,
    Eec2ElectronicEngineControl2,
    Eec3ElectronicEngineControl3,
    EflP1EngFluidLevelPress1,
    EflP2EngFluidLevelPress2,
    Et1EngineTemperature1,
    Lfe1FuelEconomyLiquid1,
    TransportprotocolHeader,
    TransportprotocolData,
    Dm01ActiveDiagnostics,
    Tsc131,
    Cac1ChargeAirCooler1,
    HoursEngineHoursRevolutions,
    Tci5TurbochargerInformation5,
    Vep1VehicleElectricalPower1,
    Eec20ElectronicEngineControl,
    EasiEngineAirSystemInfo,
    Tsc103,
    Tsc10b,
    Dm07,
    Dm08,
    Erc1ElectronicRetarderCntrl,
    Etc1ElectronicTransCntrl1,
    Etc2ElectronicTransCntrl2,
    Rqst005e,
    Rqst0021,
    RqstGlobal5e,
    RqstGlobal03,
    TciTransferCaseInformation,
    Trf1TransmissionFluids1,
    CcssCruiseControlVehicleSpd,
    Ccvs1CruiseControlVehspd,
    Ebc1ElectronicBrakeCntrl,
    Shutdn
>;

} // namespace duramax