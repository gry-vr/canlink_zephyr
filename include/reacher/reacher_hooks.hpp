#pragma once

#include <cstdint>

#include <zephyr/sys/printk.h>

#include "reacher_db.hpp"

enum class ByteOrder : unsigned char;


struct ReacherHooks{
    template <typename Msg>
    void on_rx_message(const Msg&, reacher::ReacherDb::ValueStore&, std::uint32_t){
       printk("hi"); 
    }

    void on_rx_message(const reacher::ReacherCtrl&, reacher::ReacherDb::ValueStore& rx_store, std::uint32_t now_ms){

        constexpr auto rpm_sid = reacher::SignalId::reacher_ctrl__throttle_rpm;

        if(auto rpm = rx_store.template get<rpm_sid>(); rpm){
            printk("RPM %d", static_cast<double>(*rpm));

        }
    }

};