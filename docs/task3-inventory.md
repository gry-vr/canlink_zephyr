# Task 3 signal inventory

| Duramax message.signal | Forwarded now? | Reacher definition | Evidence |
|---|---|---|---|
| AMB_Ambient_Conditions.Ambient_Air_Temperature | No: definition only | EXPORT_10.ambient_air_temp (0x310) | resources/reacher.dbc; tests/dbc/coverage.json |
| AMB_Ambient_Conditions.Barometric_PressureBarometric_Pr | No: definition only | EXPORT_10.barometric_pressure (0x310) | resources/reacher.dbc; tests/dbc/coverage.json |
| AMB_Ambient_Conditions.Engine_Air_Intake_Temperature | No: definition only | EXPORT_10.engine_air_intake_temp (0x310) | resources/reacher.dbc; tests/dbc/coverage.json |
| CAC1_Charge_Air_Cooler_1.Engine_Charge_Air_Cooler_1_Intak | No: definition only | EXPORT_11.charge_air_cooler_outlet_temp (0x311) | resources/reacher.dbc; tests/dbc/coverage.json |
| DM26_Diagnostic_Readiness_3.Time_Since_Engine_Start | No: definition only | EXPORT_12.time_since_engine_start (0x312) | resources/reacher.dbc; tests/dbc/coverage.json |
| EASI_Engine_Air_System_Info.Engine_Intake_MAF | No: definition only | EXPORT_12.engine_intake_mass_air_flow (0x312) | resources/reacher.dbc; tests/dbc/coverage.json |
| EBCC_Engine_Exhaust_Brake_Cont.Actual_Boost_Pressure | No: definition only | EXPORT_13.actual_boost_pressure (0x313) | resources/reacher.dbc; tests/dbc/coverage.json |
| EBCC_Engine_Exhaust_Brake_Cont.Desired_Boost_Pressure | No: definition only | EXPORT_13.desired_boost_pressure (0x313) | resources/reacher.dbc; tests/dbc/coverage.json |
| EEC1_Electronic_Engine_Control_1.Actual_Engine_Percent_Torque | No: definition only | EXPORT_14.actual_engine_percent_torque (0x314) | resources/reacher.dbc; tests/dbc/coverage.json |
| EEC1_Electronic_Engine_Control_1.Drivers_Demand_Engine_Prcnt_Torq | No: definition only | EXPORT_14.driver_demand_engine_torque (0x314) | resources/reacher.dbc; tests/dbc/coverage.json |
| EEC1_Electronic_Engine_Control_1.Engine_Demand_Percent_Torque | No: definition only | EXPORT_14.engine_demand_percent_torque (0x314) | resources/reacher.dbc; tests/dbc/coverage.json |
| EEC1_Electronic_Engine_Control_1.Engine_Speed | Yes | EXPORT_0.eng_speed | include/duramax_to_reacher_signal_table.hpp |
| EEC1_Electronic_Engine_Control_1.Engine_Torque_Mode | No: definition only | EXPORT_14.engine_torque_mode (0x314) | resources/reacher.dbc; tests/dbc/coverage.json |
| EEC1_Electronic_Engine_Control_1.SrcAddrssOfCntrllngDvcForEngCtrl | No: definition only | EXPORT_14.engine_control_source_address (0x314) | resources/reacher.dbc; tests/dbc/coverage.json |
| EEC2_Electronic_Engine_Control_2.ActlMaxAvailableEngPercentTorque | No: definition only | EXPORT_15.max_available_engine_torque (0x315) | resources/reacher.dbc; tests/dbc/coverage.json |
| EEC2_Electronic_Engine_Control_2.EngPercentLoadAtCurrentSpeed | No: definition only | EXPORT_15.engine_load_at_current_speed (0x315) | resources/reacher.dbc; tests/dbc/coverage.json |
| EEC3_Electronic_Engine_Control_3.NominalFrictionPercentTorque | No: definition only | EXPORT_14.nominal_friction_percent_torque (0x314) | resources/reacher.dbc; tests/dbc/coverage.json |
| EEC5_Electronic_Engine_Control_5.Actual_VGT_Position | No: definition only | EXPORT_15.actual_vgt_position (0x315) | resources/reacher.dbc; tests/dbc/coverage.json |
| EEC5_Electronic_Engine_Control_5.Commanded_VGT_Position | No: definition only | EXPORT_15.commanded_vgt_position (0x315) | resources/reacher.dbc; tests/dbc/coverage.json |
| EEC9_Electronic_Engine_Control_9.Commanded_Fuel_Rail_Pressure | Yes | EXPORT_3.fuel_rail_pressure | include/duramax_to_reacher_signal_table.hpp |
| EFL_P1_Eng_Fluid_Level_Press_1.EngOilPress | Yes | EXPORT_B.oil_pressure | include/duramax_to_reacher_signal_table.hpp |
| EFL_P2_Eng_Fluid_Level_Press_2.EngInjectorMeteringRail1Press | No: definition only | EXPORT_13.injector_metering_rail_pressure (0x313) | resources/reacher.dbc; tests/dbc/coverage.json |
| ET1_Engine_Temperature_1.EngCoolantTemp | Yes | EXPORT_B.coolant_temp | include/duramax_to_reacher_signal_table.hpp |
| ET1_Engine_Temperature_1.EngOilTemp1 | Yes | EXPORT_B.oil_temp | include/duramax_to_reacher_signal_table.hpp |
| ET3_Engine_Temperature_3.Engine_CAC_Outlet_Temperature | No: definition only | EXPORT_11.engine_cac_outlet_temp (0x311) | resources/reacher.dbc; tests/dbc/coverage.json |
| IC1_Intake_Exhaust_Cond_1.EngIntakeManifold1Press | Yes | EXPORT_0.manifold_press | include/duramax_to_reacher_signal_table.hpp |
| IC1_Intake_Exhaust_Cond_1.EngIntakeManifold1Temp | No: definition only | EXPORT_11.intake_manifold_temp (0x311) | resources/reacher.dbc; tests/dbc/coverage.json |
| LFE1_Fuel_Economy_Liquid_1.EngFuelRate | No: definition only | EXPORT_12.engine_fuel_rate (0x312) | resources/reacher.dbc; tests/dbc/coverage.json |
| SHUTDN.EngWaitToStartLamp | No: definition only | EXPORT_15.engine_wait_to_start_lamp (0x315) | resources/reacher.dbc; tests/dbc/coverage.json |
| TCI5_Turbocharger_Information_5.Engine_Turbocharger_1_Turbine_Ou | Yes | EXPORT_B.exhaust_gas_temp | include/duramax_to_reacher_signal_table.hpp |
| TSC1_31.EngRequestedSpeed_SpeedLimit | No: definition only | EXPORT_16.transmitted_requested_speed (0x316) | resources/reacher.dbc; tests/dbc/coverage.json |
| TSC1_31.MessageChecksum | No: definition only | EXPORT_16.transmitted_message_checksum (0x316) | resources/reacher.dbc; tests/dbc/coverage.json |
| TSC1_31.MessageCounter | No: definition only | EXPORT_16.transmitted_message_counter (0x316) | resources/reacher.dbc; tests/dbc/coverage.json |
| TransportProtocol_Data.SequenceNumber | No: definition only | EXPORT_16.transport_sequence_number (0x316) | resources/reacher.dbc; tests/dbc/coverage.json |
| VEP1_Vehicle_Electrical_Power_1.Keyswitch_Battery_Potential__158 | Yes | EXPORT_8.battery_bus_voltage | include/duramax_to_reacher_signal_table.hpp |
