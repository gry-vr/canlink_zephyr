#include "can_diagnostics_runtime.hpp"

namespace canfw {
namespace {
// POD, no initializer and no constructor. Startup must not zero these banks.
#if defined(CONFIG_CANLINK_RETAIN_DTCM)
alignas(8) __dtcm_noinit_section DiagnosticJournal::Region retained_regions[2];
#else
alignas(8) __noinit DiagnosticJournal::Region retained_regions[2];
#endif
static_assert(std::is_trivially_default_constructible_v<decltype(retained_regions)>);
} // namespace

DiagnosticJournal::Region *retained_diagnostics(const device *bus) {
    if (bus == DEVICE_DT_GET(DT_ALIAS(can0)))
        return &retained_regions[0];
    if (bus == DEVICE_DT_GET(DT_ALIAS(can1)))
        return &retained_regions[1];
    return nullptr;
}
} // namespace canfw
