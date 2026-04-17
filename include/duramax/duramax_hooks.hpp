#pragma once

#include <cstdint>

#include <zephyr/sys/printk.h>

#include "duramax_db.hpp"

enum class ByteOrder : unsigned char; // harmless forward if project defines another one elsewhere

struct DuramaxHooks {
    template <typename Msg>
    void on_rx_message(const Msg&, duramax::DuramaxDb::ValueStore&, std::uint32_t) {
        // default no-op
    }

    void on_rx_message(const duramax::Eec1ElectronicEngineControl1&,
                       duramax::DuramaxDb::ValueStore& rx_store,
                       std::uint32_t now_ms)
    {
        constexpr auto rpm_sid =
            duramax::SignalId::eec1_electronic_engine_control_1__engine_speed;

        if (auto rpm = rx_store.template get<rpm_sid>(); rpm) {
            printk("RPM = %d @ %u ms\n", static_cast<int>(*rpm), now_ms);
        }
    }

    void on_rx_message(const duramax::Et1EngineTemperature1&,
                       duramax::DuramaxDb::ValueStore& rx_store,
                       std::uint32_t now_ms)
    {
        constexpr auto coolant_sid =
            duramax::SignalId::et1_engine_temperature_1__engcoolanttemp;

        if (auto temp_c = rx_store.template get<coolant_sid>(); temp_c) {
            printk("Coolant = %d C @ %u ms\n", static_cast<int>(*temp_c), now_ms);
        }
    }

    template <typename Msg, typename Store>
    void on_before_send(Msg&, Store&, std::uint32_t) {}

    void on_before_send(duramax::Tsc131& msg,
                        duramax::DuramaxDb::ValueStore& tx_store,
                        std::uint32_t now_ms){
        static uint8_t msg_counter = 0;
        std::array<uint8_t, 8> encoded_msg{};
        auto could_be = duramax::Codec::encode(msg, encoded_msg.data(), 8);
        if(!could_be){
            return;
        }
        
        auto calc_checksum = [&](uint32_t id, const uint8_t* data, uint8_t arc) -> uint8_t {
              uint32_t VeGMDR_y_Sum = 0x00;
              uint8_t VeGMDR_y_ChkSm = 0x00;
              
              // Sum up the first 7 bytes of the message
              for (int i = 0; i < 7; i++) {
                  VeGMDR_y_Sum += data[i];
              }

              // Add ARC (lower 4 bits), and each byte of the ID
              VeGMDR_y_Sum += (arc & 0x0F);
              VeGMDR_y_Sum += (uint8_t)(id);
              VeGMDR_y_Sum += (uint8_t)(id >> 8);
              VeGMDR_y_Sum += (uint8_t)(id >> 16);
              VeGMDR_y_Sum += (uint8_t)(id >> 24);

              // Compute checksum (3 bits)
              VeGMDR_y_ChkSm = (((VeGMDR_y_Sum >> 6) & 0x03) + (VeGMDR_y_Sum >> 3) + VeGMDR_y_Sum) & 0x07;

              return VeGMDR_y_ChkSm;
        };
        uint32_t tsc1_31_frame_id = duramax::message_meta(msg.id).frame_id;
        uint8_t msg_checksum = calc_checksum(tsc1_31_frame_id,
                                    encoded_msg.data(),
                                    msg_counter);
        msg.messagecounter = msg_counter;
        msg.messagechecksum = msg_checksum;



        msg_counter = (msg_counter + 1) % 16;

    }
};
