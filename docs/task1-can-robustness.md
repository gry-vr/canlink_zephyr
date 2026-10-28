# Task 1 — CAN events, recovery and retained diagnostics

Base application: `0ea0203f85ad1e7ecf68b5d6ca65b236e0456fb7`. Verified Zephyr source: **4.4.2**, `dccb09599635bdff17633fa7e9dab014b91dce90`; host GCC **13.3.0**, Python **3.12.14**, west **1.5.0**. Task 3 is a separate preceding commit; this task changes no DBC or generated source. Task 2 is not implemented.

## Baseline and final verification

The original review kit was present and reused before any production edits. `git log 61f0935..HEAD --stat` showed one commit: both DBC additions plus two main startup delays changing from 3 ms to 2 ms. No AGENTS.md was found.

Exact baseline commands from `/workspace/scratch/308c3d8edb06`:

```sh
CANLINK_SOURCE_DIR=$PWD/canlink_work bash native_sim_kit/run.sh "$PWD/zephyr-env" socketcan-build
CANLINK_SOURCE_DIR=$PWD/canlink_work bash native_sim_kit/run.sh "$PWD/zephyr-env" unit
CANLINK_SOURCE_DIR=$PWD/canlink_work bash native_sim_kit/run.sh "$PWD/zephyr-env" integration
```

The production build expanded to:

```sh
export ZEPHYR_BASE=/workspace/scratch/308c3d8edb06/zephyr-env/zephyr
export ZEPHYR_TOOLCHAIN_VARIANT=host
west build -b native_sim/native/64 -d build-socketcan /workspace/scratch/308c3d8edb06/canlink_work -- \
  -DZEPHYR_BASE="$ZEPHYR_BASE" \
  -DEXTRA_CONF_FILE=/workspace/scratch/308c3d8edb06/canlink_work/boards/native_sim.conf \
  -DDTC_OVERLAY_FILE=/workspace/scratch/308c3d8edb06/canlink_work/boards/native_sim.overlay
```

Baseline: application build PASS; scheduler compile-time checks and runtime checks PASS (60,001 light-jitter sends, 44,119 heavy-jitter sends over ten simulated minutes); **7/7** native loopback gateway tests PASS. There are pre-existing unused-variable warnings in DuramaxHooks. No characterization expectations were changed.

Final repeatable command (activate the same environment first):

```sh
export PATH=/workspace/scratch/308c3d8edb06/zephyr-env/.venv/bin:$PATH
export ZEPHYR_BASE=/workspace/scratch/308c3d8edb06/zephyr-env/zephyr
bash canlink_work/tests/run_native.sh /workspace/scratch/308c3d8edb06/task-work/final-verification
```

The runner builds the production application with explicit fragments, runs the scheduler suite, runs pure diagnostic tests under AddressSanitizer/UBSan, then builds/runs both native suites. It requires `PROJECT EXECUTION SUCCESSFUL`; reaching `-stop_at` alone is not a pass. LeakSanitizer is disabled because the host denies its `/proc` inspection; ASan and UBSan remain enabled. The pure diagnostic code has no heap allocations.

Final results: production build PASS; scheduler PASS; pure diagnostic tests PASS; original gateway **7/7 PASS**; fault-injection scenario **1/1 PASS**, containing the assertions below. Native logs and commands are provided with the delivery. Live SocketCAN exchange is not verified: this host cannot create vcan interfaces. The built SocketCAN program therefore does not replace the loopback/fake-driver tests.

## Verified controller and driver behavior

The custom board's `can0` alias resolves to **CAN1 at 0x40006400**, and `can1` resolves to **CAN3 at 0x40003400**. Both are `st,stm32-bxcan`, requested 500,000 bit/s and sample-point 875. CAN1's compatible comes from the STM32F7 include; CAN3 is explicitly defined in `boards/ffw/canlink/canlink_stm32f767xx.dts`. `CONFIG_CAN=y` and the driver's `default y`/`DT_HAS_ST_STM32_BXCAN_ENABLED` condition select **CONFIG_CAN_STM32_BXCAN**. This is confirmed from the DTS/Kconfig chain; an ARM target image was not built in this environment. Native targets use different drivers.

All links below refer to the exact verified Zephyr revision:

- [bxCAN driver](https://github.com/zephyrproject-rtos/zephyr/blob/dccb09599635bdff17633fa7e9dab014b91dce90/drivers/can/can_stm32_bxcan.c), especially get_state 155–185, error ISR 187–235, start/stop 390–475, mode handling 487–533, recover 712–759, send 761–863, and filter functions 870–1068.
- [bxCAN Kconfig](https://github.com/zephyrproject-rtos/zephyr/blob/dccb09599635bdff17633fa7e9dab014b91dce90/drivers/can/Kconfig.stm32).
- [STM32F7 base DTS](https://github.com/zephyrproject-rtos/zephyr/blob/dccb09599635bdff17633fa7e9dab014b91dce90/dts/arm/st/f7/stm32f7.dtsi).

| Facility | Verified behavior |
|---|---|
| State callback | Supported; callback runs from error ISR. Hardware state transitions are compared with the driver's previous state. Starting/stopping does not guarantee a callback. |
| get_state | Reports ACTIVE/WARNING/PASSIVE/BUS_OFF/STOPPED and reads 8-bit TEC/REC from ESR. It does not take a mutex. Bus-off state is needed to interpret the TEC saturation limit. |
| Statistics | With STATS + CAN_STATS, bxCAN updates **bit0, bit1, stuff, CRC, form, ACK and RX-overrun** counters. LEC interrupts are enabled. The ISR interprets ESR.LEC and then writes LEC=7 to clear its report; it is not an unlimited error history. Statistics reset in can_start(). |
| Default recovery | Initialization enables automatic bus-off management (MCR.ABOM). |
| Manual recovery | CAN_MANUAL_RECOVERY_MODE exposes CAN_MODE_MANUAL_RECOVERY and recover(). Setting this mode before start clears ABOM. Normal operation is preserved (no listen-only/one-shot added); loopback is preserved in tests. |
| recover(K_NO_WAIT) | **Not nonblocking internally.** It takes inst_mutex with K_FOREVER, enters and leaves initialization mode (each polling helper has a nominal 10 ms bound), then checks BOFF against the supplied timeout. The timeout does not bound the mutex or initialization work. The leave-init return is ignored. Also, ret is overwritten by successful enter-init, so the timeout exit can return 0 while BOFF remains set. A 0 return is not accepted as proof of recovery. |
| start() | Also takes inst_mutex and waits for init acknowledgment; unsuitable for the existing worker. |
| send(K_NO_WAIT) | Mailbox-space wait is nonblocking, but **inst_mutex uses K_FOREVER**. The new recovery executor must finish before the owner calls send, even if ACTIVE has already been observed. |
| Filters | start/recover do not remove the driver's callback arrays or reconfigure filter banks. They are retained; repeated add-filter would leak slots. Startup failure now removes the installed filter and unregisters the callback before returning the existing error. |

Manual recovery was chosen for bxCAN to make attempts/backoff explicit and observable. Drivers without this capability use an automatic-recovery observation path; this cannot make a driver recover if its hardware/driver does not implement automatic recovery. The native loopback/native-linux drivers do not model physical bus-off; the controllable fake driver exercises manual recovery. Native-linux get_state currently reports active whenever started and zero error counters; it does not provide physical error telemetry through this API.

## Architecture and ownership

`CanActiveObject` still owns and exclusively mutates its RX/TX stores. The two existing workers retain priority 5 and 8 KiB stacks. Translators remain in main. No timer was added: the worker's poll timeout is the minimum of its next TX deadline, recovery deadline and diagnostic reconciliation deadline.

Each worker has a `CanDiagnostics` member, a fixed event queue added as the third k_poll event, a fixed TX-context pool, and a **priority-6 recovery executor with a 2 KiB stack**. The executor is the only new context allowed to call potentially blocking recover/start. It never touches stores, log records, recovery policy or counters. It receives a small action through a one-slot queue, publishes the result through atomics and wakes the owner through the event queue. A full event queue cannot lose the result: the atomic result mailbox is reconciled on the next diagnostic poll.

State callbacks record uptime, cycles, old/new state and TEC/REC, then put the 40-byte record with K_NO_WAIT. The previous published state/counters and overflow counters are lock-free 32-bit atomics. TX callbacks use an immutable, reserved context containing CAN ID/DLC; an error queues a record and increments a separate atomic completion-error total. Successful completion increments its own total. The context is released with release/acquire ordering; no allocation or lookup by a possibly reused CAN ID is needed.

TX completion snapshots call get_state to capture current TEC/REC, since bxCAN calls TX completions **before** its state callback in the error ISR. The verified bxCAN/native-linux/loopback implementations only read fields/registers and do not block. A future controller driver must be audited before using this ISR path. No log, CRC, recovery decision or print occurs in a callback.

The default eight TX contexts exceed bxCAN's three mailboxes. If contexts are exhausted, the attempt is rejected locally with ENOBUFS and counted separately as context exhaustion as well as an immediate rejection. Immediate driver rejection releases its context; an accepted frame keeps it until completion. The combined `tx_send_failures()` remains available as immediate rejections plus asynchronous completion errors.

The application now installs its own RX callback. Zephyr's [can_add_rx_filter_msgq wrapper](https://github.com/zephyrproject-rtos/zephyr/blob/dccb09599635bdff17633fa7e9dab014b91dce90/drivers/can/can_common.c#L102) only logs a failed k_msgq_put and exposes no application overflow counter. The replacement still performs K_NO_WAIT copying into the same RX queue, and increments an atomic drop counter on failure. It records last driver-delivered RX time, including frames subsequently dropped or unknown to the DBC. Separately, last decoded time and last processed RX ID/DLC distinguish bus traffic from accepted application data.

RX, command and event drains are bounded to one queue capacity per pass. This is necessary for recovery/TX progress under continuously replenished input. No unrelated queue protocol was changed.

## Recovery and suppression policy

Pure `diag::RecoveryPolicy` receives states, time and operation results. On BUS_OFF or STOPPED it schedules an immediate action; subsequent unconfirmed/failed attempts wait **100, 200, 400, 800, 1600, 3200, 5000, 5000… ms** by default. There is no attempt limit or terminal failure state. All deadline comparisons handle 32-bit uptime wrap within the configured (<2^31 ms) horizon. Returned success does not end an episode: only observing ACTIVE/WARNING/PASSIVE does. STOPPED schedules start(), not recover().

A recovery that returns success but remains off is recorded as unconfirmed before retrying; return errors and state-query errors are recorded. The worker samples state every 50 ms to reconcile STOPPED, absent callbacks and queue-overflow loss. Bus-off entries record time/TEC/REC; completion records duration, attempts and entry/exit counters. Running totals retain last/longest duration. An interrupted episode remains marked open in the previous-boot image rather than being falsely labeled recovered.

**Stated default assumption:** during BUS_OFF/STOPPED, suppress before build/pre-send hook/send, count suppressed attempts and still advance the schedule. This preserves the TSC1 counter for frames never built. Additionally, TX is always deferred while a recovery/start operation is in flight, avoiding the bxCAN send-mutex problem. This extra deferral remains even if unhealthy-state suppression is disabled. An immediate rejection after building still consumes the existing TSC1 counter; Task 1 does not change that behavior. Healthy-bus payloads and periods are unchanged.

The executor removes blocking calls from the CAN worker, but cannot promise completion if the driver itself permanently deadlocks inside its K_FOREVER mutex. The policy never voluntarily gives up; proving recovery from a permanently hung driver would require a driver change or a separately approved controller/system reset policy. No such reset policy is invented here.

## Record format, snapshots and retention

`diag::Record` is packed, trivially copyable and statically asserted to **40 bytes**. Both supported targets are little-endian; the format asserts this. Layout v1:

| Offset | Bytes | Meaning |
|---|---|---|
| 0 | 8 | 64-bit uptime in ms |
| 8 | 4 | Cycle counter (wraps independently) |
| 12 | 4 | CAN ID when applicable |
| 16 | 4 | Signed error code |
| 20/24/28 | 4 each | Event-specific arg0 / arg1 / aux |
| 32–39 | 1 each | Event type, old state, new state, TEC, REC, DLC, flags, reserved |

Flags: 0 = state callback arguments; 1 = polled/reconciled transition; 2 = executor wake-only token (not logged); 4 = explicit get_state snapshot; 8 = last published fallback if no fresh snapshot was available. Recovery attempt carries episode attempt and action; result carries action and errno; completion carries duration (low 32 bits), attempt count, and packed entry TEC/REC. Full last/longest durations are 64-bit counters. Queue-overflow records carry the number lost since the previous reconciliation. The event ring overwrites oldest and counts overwrites. Counters are separate from the ring, so overwriting records does not reset totals.

The snapshot also contains all seven current driver statistics, initial configured bitrate/sample-point request, core clock, capabilities, current mode, reset cause and API error status. On bxCAN it takes **read-only** snapshots of MCR, MSR, TSR, RF0R, RF1R, IER, ESR and BTR from the verified devicetree base addresses. No register is written or read from an RX FIFO. ESR exposes BOFF/EPVF/EWGF/TEC/REC/LEC; BTR captures actual timing configuration. LEC can already have been cleared by the driver's statistics ISR, and register/statistic samples are sequential, not an atomic hardware snapshot. The stored statistics are driver counters since the latest start; they may reset on restart and are not claimed as lifetime error totals.

Optional raw history (`CANLINK_RAW_FRAME_DEPTH`, default 0) stores 24-byte records of processed RX or accepted TX, including direction, ID, flags, DLC and up to eight bytes. It is an application observation history, not proof that an accepted TX was ACKed on the physical bus.

The [STM32F767 memory map](https://www.st.com/resource/en/datasheet/stm32f767bg.pdf) provides 128 KiB DTCM and 384 KiB normal SRAM, plus 4 KiB backup SRAM. The [Zephyr F765/F767 DTS chain](https://github.com/zephyrproject-rtos/zephyr/blob/dccb09599635bdff17633fa7e9dab014b91dce90/dts/arm/st/f7/stm32f765.dtsi) and board choose DTCM and SRAM0. Backup SRAM is disabled; the board declares no retained_mem/retention region. VBAT wiring is not established by the repository. The selected log exceeds 4 KiB, so backup SRAM is not used.

The two physical channels' regions are non-template globals in `src/can_diagnostics.cpp`: **DTCM noinit** on STM32F7, ordinary noinit in native tests. DTCM avoids losing dirty D-cache lines on reset. The [ARM linker script](https://github.com/zephyrproject-rtos/zephyr/blob/dccb09599635bdff17633fa7e9dab014b91dce90/include/zephyr/arch/arm/cortex_m/scripts/linker.ld#L352) separates DTCM bss/data/noinit; no DT edit is required. ELF inspection verifies native placement in `.noinit...can_diagnostics.cpp`, NOBITS. A template-local implementation was rejected during development because GCC placed it in bss despite its annotation; that implementation is not retained.

Each region has three bank images with magic, version, exact size, boot generation, checkpoint sequence and CRC32 (IEEE polynomial). CRC covers header/payload except magic/CRC. Boot chooses the newest valid image and preserves it as previous-boot, then alternates current checkpoints between the other two banks. A partially written current bank leaves the preceding valid checkpoint available. Invalid/incompatible banks are rejected. The current working image is owner-thread RAM; only the owner commits or clears banks. Clear removes current/previous event history while retaining this boot's running counters, controller state and policy.

| Event | Preservation |
|---|---|
| Software/warm reset, watchdog reset | Expected to preserve committed DTCM banks if startup/bootloader does not clear them and supply remains valid. Hardware reset testing is still required. |
| Hard fault | Last completed checkpoint remains in RAM. No new fatal handler is installed; the board has FAULT_DUMP=2 and no configured persistent coredump backend. A fault does not necessarily reboot. Fault-time PC/LR/register capture is not added. |
| Power loss/brownout/standby losing DTCM | Not guaranteed; CRC rejects corrupt contents. This is not battery-backed retention. |
| Reflash, debugger RAM initialization, changed layout/depth | May erase or invalidate the log. Size/version/CRC protect against interpreting incompatible bytes. |
| Native process restart | Native noinit does not preserve memory across a new Linux process. Tests reinitialize journals over the same memory buffer; they do not claim physical reset retention. |

Callbacks not yet drained and updates after the last completed checkpoint may be lost on reset. Finite event queues cannot record every arbitrarily fast transition: overflow is counted and state reconciled, but lost intermediate transitions cannot be reconstructed. The test explicitly verifies this loss is visible; no lossless claim is made.

## Retrieval API

The hardware board does not enable CONFIG_SHELL; native_sim.conf does. This change supplies an API/print path without enabling a new hardware shell or adding worker-side UART printing. Use a **static**, single-reader `DiagnosticClient` from main or another non-worker context:

```cpp
static canfw::DiagnosticClient client;
// ep is either existing bus endpoint. false=current; true=previous boot.
if (ep.request_diagnostics(client.reply_queue(), true) == 0 &&
    client.receive(K_MSEC(100)) == 0) {
    client.print();
}
// Clear both histories (running counters/policy remain intact):
if (ep.request_diagnostics(client.reply_queue(), false, true) == 0 &&
    client.receive(K_MSEC(100)) == 0) {
    client.print();
}
```

The worker copies a complete CRC-valid image into the caller's reply queue; the caller never reads retained memory directly. `print()` displays named events/states, times, counters, driver configuration/statistics/registers and optional raw frames. One outstanding request per client; do not destroy its queue or reuse it after timeout until the outstanding reply has been drained. The existing unrelated snapshot correlation issue is not changed. The fake-driver test exercises retrieval/clear through real queues and invokes the printer.

## Configuration, RAM and files

New symbols: CANLINK_DIAGNOSTICS (internal default-on selection of STATS/CAN_STATS/CAN_MANUAL_RECOVERY_MODE and STM32 HWINFO), CANLINK_EVENT_QUEUE_DEPTH=32, CANLINK_LOG_DEPTH=64, CANLINK_TX_CONTEXTS=8, CANLINK_RECOVERY_INITIAL_MS=100, CANLINK_RECOVERY_MAX_MS=5000, CANLINK_RECOVERY_CONFIRM_MS=100, CANLINK_DIAGNOSTIC_POLL_MS=50, CANLINK_RECOVERY_STACK_SIZE=2048, CANLINK_RAW_FRAME_DEPTH=0, CANLINK_SUPPRESS_UNHEALTHY_TX=y, and CANLINK_RETAIN_DTCM=y on supported STM32F7 DTCM targets. The clock remains the existing Zephyr clock; no k_timer is introduced.

Measured on native/64, defaults and raw history off:

| Allocation | Added bytes |
|---|---:|
| Both actor objects, including working images, event queues, callback contexts, executor stacks/thread objects | 13,824 |
| Two retained three-bank regions | 17,136 |
| Additional data accounting in final native binary | 200 |
| Total GNU size data+BSS increase versus baseline | **31,160 (~30.4 KiB)** |

One bank is 2,856 bytes; one retained channel is 8,568 bytes. A caller-instantiated default DiagnosticClient adds 5,816 bytes on native/64 and is not instantiated by production main. A raw-history depth of four adds 112 bytes per bank/working image, or 448 bytes per channel; the raw-enabled fault test measures a 2,968-byte image and 8,904-byte retained region per channel. Each extra event-depth slot adds 160 bytes per channel across its three banks and working image. Pointer/thread-object sizes and final linker accounting differ on ARM; these numbers are **not** a target RAM or stack-watermark measurement. The CRC lookup table is const data. No runtime-path heap allocation is added.

Files changed: CMakeLists.txt (adds one translation unit, now 10), Kconfig, can_active_object.hpp, can_commands.hpp, can_endpoint.hpp; new can_diagnostics.hpp (pure policy/journal), can_diagnostics_runtime.hpp (Zephyr glue/client), src/can_diagnostics.cpp (physical retained storage), tests/host/diagnostics_test.cpp, tests/native_gateway (original seven tests promoted from the separate kit), tests/native_robustness (fake backend), tests/run_native.sh, and this report. No production main, translation table, Duramax hooks, generated codec/store/validator, eMMC or zbus draft changed.

## Test coverage and remaining limits

Pure tests cover record layout, known CRC vector, overwrite ordering/count, bounded exponential backoff, 32-bit wrap, indefinite repeated failures, active/warning/passive/stopped decisions, valid reboot, corrupt reboot, interrupted commits, clearing, and single-bit corruption across every byte of an image.

The native fake-driver scenario uses the real CanActiveObject, real k_msgq/k_poll and ISR-offloaded callbacks. It asserts: filter-add failure; start-failure cleanup and successful retry; both channel isolation; warning/passive/off/active transitions and TEC/REC; repeated failed recoveries; false success with bus still off; eventual recovery/duration; nonblocking executor separation; ACTIVE before executor return with no TX/hook calls in that window; repeated STOPPED start failures; completion errno ENETUNREACH/EIO/ETIMEDOUT/ENETDOWN/EAGAIN with correct IDs (including two message IDs); immediate rejection; callback-context exhaustion and reverse-order completion; RX overflow; last-good RX time; raw history overwrite; event overflow and state reconciliation; copied diagnostic images and clear. Fake statistics/configuration are also captured and checked. The original seven loopback tests remain unchanged and passing.

Untested: ARM compilation/link placement, Cortex-M interrupt latency, actual bxCAN arbitration/ACK loss/bus-off/recovery, unplug/replug, transceiver behavior, warm-reset/watchdog/fault DTCM retention, hardware driver-call duration, CRC/checkpoint timing at full bus load, and target stack high-water marks. No recovery reset escalation is added. A first-ever create failure still returns to the existing main error path; queued startup diagnostics become retrievable only if factory creation is retried successfully. No autonomous boot retry policy is invented.

Out of scope and unchanged: old snapshot correlation, last_validation_issue data race, RX physical-range validation and J1939 error/unavailable semantics, TX-store-before-validation behavior, general OverflowPolicy/narrowing, eMMC/zbus drafts, CI, west manifest and Zephyr pinning.
