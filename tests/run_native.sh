#!/usr/bin/env bash
set -euo pipefail
repo_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
: "${ZEPHYR_BASE:?Set ZEPHYR_BASE to your Zephyr 4.4.2 checkout and activate its Python environment}"
export ZEPHYR_TOOLCHAIN_VARIANT=host
build_root="${1:?Usage: tests/run_native.sh /absolute/build-directory}"
mkdir -p "$build_root"
build_root="$(cd "$build_root" && pwd)"
g++ -std=c++23 -Wall -Wextra -Werror -I"$repo_dir/include" \
    "$repo_dir/src/tx_schedule_test.cpp" -o "$build_root/scheduler"
"$build_root/scheduler" | tee "$build_root/scheduler.log"
g++ -std=c++23 -Wall -Wextra -Werror -fsanitize=undefined,address \
    -I"$repo_dir/include" "$repo_dir/tests/host/diagnostics_test.cpp" -o "$build_root/diagnostics"
# LeakSanitizer cannot inspect /proc in some hosts; these tests allocate no heap.
ASAN_OPTIONS=detect_leaks=0 "$build_root/diagnostics" | tee "$build_root/diagnostics.log"
g++ -std=c++23 -Wall -Wextra -Werror -fsanitize=undefined,address \
    -I"$repo_dir/include" "$repo_dir/tests/host/throttle_test.cpp" -o "$build_root/throttle"
ASAN_OPTIONS=detect_leaks=0 "$build_root/throttle" | tee "$build_root/throttle.log"
west build -b native_sim/native/64 -d "$build_root/production" "$repo_dir" -- \
    -DZEPHYR_BASE="$ZEPHYR_BASE" \
    -DEXTRA_CONF_FILE="$repo_dir/boards/native_sim.conf" \
    -DDTC_OVERLAY_FILE="$repo_dir/boards/native_sim.overlay" \
    2>&1 | tee "$build_root/build-production.log"
for test in native_gateway native_robustness; do
    west build -b native_sim/native/64 -d "$build_root/$test" "$repo_dir/tests/$test" \
        2>&1 | tee "$build_root/build-$test.log"
    chmod u+x "$build_root/$test/zephyr/zephyr.exe"
    "$build_root/$test/zephyr/zephyr.exe" -no-rt -stop_at=30 \
        2>&1 | tee "$build_root/$test.log"
    grep -q 'PROJECT EXECUTION SUCCESSFUL' "$build_root/$test.log"
done

west build -b native_sim/native/64 -d "$build_root/native_gateway_bands_off" "$repo_dir/tests/native_gateway" -- \
    -DCONFIG_CANLINK_THROTTLE_BAND_MAPPING=n 2>&1 | tee "$build_root/build-native_gateway_bands_off.log"
chmod u+x "$build_root/native_gateway_bands_off/zephyr/zephyr.exe"
"$build_root/native_gateway_bands_off/zephyr/zephyr.exe" -no-rt -stop_at=30 \
    2>&1 | tee "$build_root/native_gateway_bands_off.log"
grep -q 'PROJECT EXECUTION SUCCESSFUL' "$build_root/native_gateway_bands_off.log"
