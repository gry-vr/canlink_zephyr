


// holy fuck i kinda don't know what do right here..

#pragma once

#include <zephyr/sys/printk.h>

#include <zephyr/kernel.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/disk.h>

#include <zephyr/usb/usb_device.h>

#include <zephyr/storage/disk_access.h>

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <span>
#include <type_traits>

#include "can_endpoint.hpp"


// this thing is going to need to be able to read
// the published last message to the zbus channel that has the latest snapshot
// so the questions are how can I get this data into here so that I can write it to the 
// emmc.

// I also obviously wanna make this friendly to native_sim so how can I test this and
// write the same code ? 



template<typename T>
concept BlockDevice = requires(T& d, std::uint32_t lba, std::uint32_t n,
                                void *dst, const void* src){
    { d.read(dst, lba, n)   }   -> std::same_as<int>;
    { d.write(src, lba, n)  }   -> std::same_as<int>;
    { d.sync()              }   -> std::same_as<int>;
    { T::kSectorSize        }   -> std::convertible_to<std::uint32_t>; 
};



// VERIFIED against hardware. KINGSTON eMMC returns 512 sector size.
class DiskDevice {
    public:
    static constexpr std::uint32_t kSectorSize = 512;
    explicit constexpr DiskDevice(const char* name) : name_{name} {}

    int read (void* dst, std::uint32_t lba, std::uint32_t n){
       return disk_access_read(name_, static_cast<std::uint8_t*>(dst), lba, n);
    }

    int write (const void* src, std::uint32_t lba, std::uint32_t n){
        return disk_access_write(name_, static_cast<const std::uint8_t*>(src), lba, n);
    }

    int sync() {return disk_access_ioctl(name_, DISK_IOCTL_CTRL_SYNC, nullptr);}

    private:
    const char* name_;
};


class LogStore{
    public:

    struct Block {
        std::uint32_t seq;
        std::uint32_t stamp_ms;
        std::uint16_t count;
        std::uint16_t crc;
        std::byte payload[496];
    };
    static_assert(sizeof(Block) == 512);

    auto recover(BlockDevice&) -> std::expected<void, StoreError>;

    auto append_block(BlockDevice&, const Block&) -> std::expected<void, StoreError>

    [[nodiscard]] std::uint32_t next_sector() const;
    [[nodiscard]] std::uint32_t next_seq() const;


    private:
    std::uint32_t first_sector_{}, sector_count_{};
    std::uint32_t write_index_{}, seq_{};

};



};