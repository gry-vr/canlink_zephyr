#pragma once

#include <zephyr/kernel.h>

#include <array>
#include <cstdint>
#include <optional>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

#include "can_endpoint.hpp"
#include "signal_table.hpp"

template <
    typename SrcDb,
    typename DstDb,
    typename TranslationTable
>
class Translator {
public:
    using SrcEndpoint = canfw::CanEndpoint<SrcDb>;
    using DstEndpoint = canfw::CanEndpoint<DstDb>;
    using SrcSnapshot = canfw::SnapshotReply<SrcDb>;
    using Table = typename TranslationTable::type;

    Translator(SrcEndpoint src_in,
               DstEndpoint dst_out)
        : src_in_{src_in},
          dst_out_{dst_out}
    {
        k_msgq_init(&src_reply_q_,
                    reinterpret_cast<char*>(src_reply_storage_.data()),
                    sizeof(SrcSnapshot),
                    1);
    }

    [[nodiscard]] bool valid() const {
        return src_in_.valid() && dst_out_.valid();
    }

    void step_once() {
        auto maybe = src_in_.request_snapshot_blocking(src_reply_q_);
        if (!maybe || !maybe->valid) {
            ++snapshot_failures_;
            return;
        }

        apply_all(*maybe);
    }

    [[nodiscard]] std::uint32_t snapshot_failures() const {
        return snapshot_failures_;
    }

    [[nodiscard]] std::uint32_t source_missing_count() const {
        return source_missing_count_;
    }

    [[nodiscard]] std::uint32_t validation_failures() const {
        return validation_failures_;
    }

    [[nodiscard]] std::uint32_t update_failures() const {
        return update_failures_;
    }

    [[nodiscard]] std::uint32_t updates_posted() const {
        return updates_posted_;
    }

private:
    template <typename Rule>
    void apply_one(const SrcSnapshot& snap) {
        auto source_value = snap.store.template get<Rule::src_signal>();
        if (!source_value) {
            ++source_missing_count_;
            return;
        }

        const auto translated_value = Rule::apply(*source_value);

        auto validated =
            DstDb::template validate_signal_value<Rule::dst_signal>(translated_value);
        if (!validated) {
            ++validation_failures_;
            return;
        }

        typename DstDb::SignalPhysicalValue physical_value{translated_value};

        const int rc = dst_out_.update_signal(
            Rule::dst_signal,
            std::move(physical_value),
            Rule::trigger_parent_send);

        if (rc != 0) {
            ++update_failures_;
            return;
        }

        ++updates_posted_;
    }

    template <typename... Rules>
    void apply_all_impl(const SrcSnapshot& snap, std::tuple<Rules...>) {
        (apply_one<Rules>(snap), ...);
    }

    void apply_all(const SrcSnapshot& snap) {
        apply_all_impl(snap, typename TranslationTable::type{});
    }

    SrcEndpoint src_in_{};
    DstEndpoint dst_out_{};

    k_msgq src_reply_q_{};
    alignas(SrcSnapshot) std::array<SrcSnapshot, 1> src_reply_storage_{};

    std::uint32_t snapshot_failures_{0};
    std::uint32_t source_missing_count_{0};
    std::uint32_t validation_failures_{0};
    std::uint32_t update_failures_{0};
    std::uint32_t updates_posted_{0};
};