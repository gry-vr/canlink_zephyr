# Task 2 — approved legacy throttle TX policy

Implemented on top of local Task 3 `097d035` and Task 1 `788e2f9`. This report supersedes the earlier decision proposal: timeout is now **enabled, 500 ms**, with override-disabled/zero-speed fallback, as explicitly approved. Production defaults enable the legacy bands. No DBC or generated code changed in this task.

## Source and oracle

The actual public legacy source was retrieved and inspected, not just the supplied extract:

- [src/main.cpp lines 633–730](https://github.com/gry-vr/CanLink/blob/ed5db800eadf6f393b04790129295725b0847563/src/main.cpp#L633-L730), blob `4f26d88e5e0dccdee0915aef3ae9b7a7080bca87`.
- [throttle_subs lines 208–280](https://github.com/gry-vr/CanLink/blob/ed5db800eadf6f393b04790129295725b0847563/src/main.cpp#L208-L280).
- [resources/j1939_FFW_v3.dbc](https://github.com/gry-vr/CanLink/blob/ed5db800eadf6f393b04790129295725b0847563/resources/j1939_FFW_v3.dbc), blob `2ec4ac2c4e70fcaa44c829174bee67e7805f19f3`.

The pinned commit is `ed5db800eadf6f393b04790129295725b0847563`. File blobs at this commit match those retrieved from main. The legacy subscription positions are correctly low=1, high=2; a comment records that low was previously at 2. Input unpacking is low=5, high=6. `tests/oracle/legacy_throttle.hpp` independently transcribes the actual source's clamp, control-byte branch and checksum expression. It does not call the production mapping/checksum functions. Legacy's init lambda assigns its local pointer instead of initializing the object; this implementation initializes all state explicitly.

## Behavior and switches

- Before any valid Reacher 0x200 command: byte 0=00, speed=0; bytes 3–6=FF.
- Valid input is finite, nonnegative and no greater than 8031.875 RPM (raw 64255/0xFAFF). Convert with round-to-nearest raw 0.125-RPM units, positive half ties upward, only after validation.
- Mapping on: raw <=10400 ->10000; 10400<raw<=16008 ->16000; above 16008 passes through. Named constants and RPM comments are together in the pure header.
- Mapping off: the validated raw request passes through unchanged. **A valid zero request enables F1 at 0 RPM**. Disabling mapping does not disable startup gating, staleness, validation, or the literal F1/FF wire format. The old unreachable high-byte/5% branch is not ported.
- A rejected command retains the last accepted value and its original age. Invalid commands cannot clear startup/stale gating.
- At age >=500 ms, disable override and request zero. Only a fresh valid source sequence can re-enable. Stale fallback is the one approved Kconfig choice; no other fallback is invented.
- Keep the 10-ms scheduler; translator remains in main at roughly 10 Hz. ARC advances once per actual `can_send` offer, including an immediate driver rejection. Suppression, build/validation/encode failure and local context exhaustion do not consume ARC.

Exact locations in this commit (1-based lines):

| Purpose | File:line |
|---|---|
| Band switch, default y | `Kconfig:57` |
| Custom STM32 target explicitly enables bands | `boards/canlink_stm32f767xx.conf:52` |
| Production native_sim explicitly enables bands | `boards/native_sim.conf:30` |
| Native integration explicitly enables bands | `tests/native_gateway/prj.conf:29` |
| Hook reads band switch | `include/duramax/duramax_hooks.hpp:78` |
| Four named thresholds | `include/throttle_policy.hpp:7` |
| Pure `map_throttle_raw` | `include/throttle_policy.hpp:18` |
| On/off selector `requested_raw` | `include/throttle_policy.hpp:22` |
| Timeout enable, default y | `Kconfig:63` |
| Timeout ms, default 500 | `Kconfig:66` |
| Named stale fallback choice | `Kconfig:70` |
| Selected fallback bool | `Kconfig:73` |
| Timeout/age decision | `include/throttle_policy.hpp:51` |
| Literal-byte override and checksum | `include/throttle_policy.hpp:67` |
| Post-encode hook, ARC increment | `include/duramax/duramax_hooks.hpp:89` |

`prj.conf` itself does not set these symbols; the two target config fragments above do. Set `CONFIG_CANLINK_THROTTLE_BAND_MAPPING=n` in the relevant fragment, or override with `west build ... -- -DCONFIG_CANLINK_THROTTLE_BAND_MAPPING=n`. The test runner builds the latter configuration separately and checks its wire frames. A named Kconfig **choice** is selected through its option symbol, `CONFIG_CANLINK_THROTTLE_STALE_OVERRIDE_DISABLED=y`; the choice name is not an integer/string `.conf` value.

## Hook integration, ownership and time

Reacher's existing RX hook validates throttle immediately after generated store application. It retains one accepted `SignalSlot`. On invalid input it restores that slot (including timestamp/validity); other decoded Reacher signals keep their existing behavior. This prevents an invalid sample between main-loop snapshots from destroying the last good throttle command. Each valid frame increments a sequence, including identical values and two valid frames processed in the same millisecond. Each invalid throttle value increments the Reacher rejection counter.

A fixed 20-byte `throttle::Source` carries source processing timestamp, sequence, rejection count, frame ID and validity. The compile-time detected `on_snapshot` hook copies this into `SnapshotReply`; Translator passes it with `UpdateSignal`. The detected `on_signal_updated` hook validates/accepts it in the Duramax owner worker before the generated TX-store update. Duplicate snapshot sequences never refresh the policy. A missing provenance record cannot enable throttle. Numeric variant type is checked before policy mutation, matching the generated store's f64 contract.

The timestamp comes from Reacher AO's `wake_ms = k_uptime_get_32()`, passed through `drain_rx`, the generated store and RX hook. It is **software batch-processing time, not CAN hardware/ISR arrival time**, and is an unsigned 32-bit millisecond count. Native config uses 1000 ticks/second, so its resolution is 1 ms. Target API timestamps have millisecond units; physical timing resolution depends on the final STM32 kernel clock configuration, which was not built here. Multiple frames drained in one batch can share a timestamp but have different valid-command sequences.

500 ms spans approximately five normal 100-ms translator iterations, so translator cadence alone is not marginal. It is not a guarantee about an unknown Reacher transmitter period or worst-case main-thread delays: the sender must deliver valid traffic more frequently than 500 ms with margin. A command first reaches Duramax on the next successful main translation; stale disable is evaluated independently at each 10-ms TSC1 build using the original source timestamp. Thus snapshot replay cannot keep an old command alive. Recovery normally takes up to one translator period plus the next TX slot. Native tests bound the observed loss transition to 500–520 ms from injection; pure tests check ages 499, 500 and 501 exactly. Hardware jitter is not certified by these tests.

`SnapshotReply::rejected_throttle_inputs` is exposed through the existing queued snapshot API: on Reacher it counts rejected network throttle values; on Duramax it counts invalid/type-mismatched queued throttle updates. `SnapshotReply::stale_timeout_events` on Duramax counts entry into stale state once, not every repeated disabled frame. All counters and hook state are written only by their owning worker and copied to readers through queues. These policy counters are running RAM diagnostics, not new retained-log record types. No shared mutable stores, heap allocation, blocking CAN-worker calls or extra threads were introduced.

Pre-send selects the raw output and builds a valid typed intermediate. The detected post-encode hook applies exact literal bytes and calculates ARC/checksum over the final image, with CAN ID **0x0C000031, no EFF flag**. TX callback context reservation precedes this hook; `can_send(K_NO_WAIT)` follows immediately. Existing bus-off/stopped/recovery suppression precedes both hooks. Generic framework code does not contain TSC1-specific branches.

## Decode F1 and FF against both DBCs

The legacy DBC and current read-only Duramax DBC agree on all TSC1_31 starts, lengths, endian order, factors, offsets and ranges. Speed is bits 8–23, little-endian: byte1 low, byte2 high. Reacher throttle is bits40–55, little-endian, factor0.125, valid0..8031.875RPM: byte5 low, byte6 high. No mapping mismatch was found.

| Byte/field | Raw value | DBC meaning |
|---|---:|---|
| Byte0 bits1:0, EngOverrideCtrlMode | 1 | Speed control |
| Byte0 bits3:2, EngRequestedSpeedCtrlConditions | 0 | Transient optimized for driveline disengaged and non-lockup conditions |
| Byte0 bits5:4, OverrideCtrlModePriority | 3 | Low priority |
| Byte0 bits7:6 | 3 | No declared signal; both reserved/undefined bits are set by literal F1 |
| Byte3, EngRequestedTorque_TorqueLimit | 255 | Numeric decode **130%**, outside declared -125..125%; no DBC value-table label for 255 |
| Byte4 bits2:0, TSC1TransRate | 7 | Use standard TSC1 transmission rates of 10 ms to engine |
| Byte4 bits7:3, TSC1CtrlPurpose | 31 | **P32 = Temporary Powertrain Control** |
| Byte5 bits3:0, EngRequestedTorqueHighResolution | 15 | Numeric decode **1.875%**, outside declared 0..0.875%; no DBC value-table label for 15 |
| Byte5 bits7:4 | 15 | No declared signal; all set |
| Byte6 | 255 | No declared signal; all set |

FF is the legacy all-ones filler/unavailable wire convention, **not a valid physical torque value according to these DBC ranges**. The DBC itself does not label these particular all-ones values as NA. Byte4 is fully representable by typed values; bytes0 reserved bits,3 invalid physical value,5 invalid low nibble/reserved high nibble and6 undefined bits require post-encode handling to reproduce the requested image without editing generated codecs or weakening validation. The checksum is 3-bit even though the DBC allocates a 4-bit nibble. There is no discrepancy in the checksum algorithm.

## Legacy versus new full-byte vectors

ARC=0 throughout this table. Each valid row means a fresh accepted command; startup and stale behavior are addressed separately below. Legacy column comes from the actual-source oracle; on/off columns use the pure production policy. The unit test compares all eight ARC values for every valid boundary vector, with independent golden full frames for the 2000-RPM band.

| Input raw | RPM | Legacy frame | New, bands on | New, bands off |
|---:|---:|---|---|---|
| 0 | 0.000 | `F1 10 27 FF FF FF FF 60` | `F1 10 27 FF FF FF FF 60` | `F1 00 00 FF FF FF FF 70` |
| 10399 | 1299.875 | `F1 10 27 FF FF FF FF 60` | `F1 10 27 FF FF FF FF 60` | `F1 9F 28 FF FF FF FF 20` |
| 10400 | 1300.000 | `F1 10 27 FF FF FF FF 60` | `F1 10 27 FF FF FF FF 60` | `F1 A0 28 FF FF FF FF 30` |
| 10401 | 1300.125 | `F1 80 3E FF FF FF FF 00` | `F1 80 3E FF FF FF FF 00` | `F1 A1 28 FF FF FF FF 40` |
| 16007 | 2000.875 | `F1 80 3E FF FF FF FF 00` | `F1 80 3E FF FF FF FF 00` | `F1 87 3E FF FF FF FF 70` |
| 16008 | 2001.000 | `F1 80 3E FF FF FF FF 00` | `F1 80 3E FF FF FF FF 00` | `F1 88 3E FF FF FF FF 10` |
| 16009 | 2001.125 | `F1 89 3E FF FF FF FF 20` | `F1 89 3E FF FF FF FF 20` | `F1 89 3E FF FF FF FF 20` |
| 16010 | 2001.250 | `F1 8A 3E FF FF FF FF 30` | `F1 8A 3E FF FF FF FF 30` | `F1 8A 3E FF FF FF FF 30` |
| 32767 | 4095.875 | `F1 FF 7F FF FF FF FF 70` | `F1 FF 7F FF FF FF FF 70` | `F1 FF 7F FF FF FF FF 70` |
| 65535 | 8191.875 | `F1 FF FF FF FF FF FF 50` | Rejected; retains prior accepted request* | Rejected; retains prior accepted request* |
| 12001 | 1500.125 | `F1 80 3E FF FF FF FF 00` | `F1 80 3E FF FF FF FF 00` | `F1 E1 2E FF FF FF FF 00` |

*For rejected input, prior state determines the wire image. If the prior accepted request is raw 16009 and remains fresh, both modes retain `F1 89 3E FF FF FF FF 20` at ARC0. If none was accepted or the retained request is stale, transmit `00 00 00 FF FF FF FF 00` at ARC0. Invalid input never extends the deadline. Legacy passes raw 65535 through; rejecting it is an approved intentional difference.*

Other intentional differences:

- No input yet: new firmware sends disabled/zero; legacy's no-op init does not establish reliable initial throttle state. We do not claim a deterministic pre-input legacy frame.
- Stale at/after500ms: new firmware disables/zeros; legacy retained the last command without this timeout.
- Mapping off: new optional mode passes raw values through. Legacy always applies bands. Above16008 both match (for valid inputs).
- Negative/NaN/infinity/above8031.875 direct physical inputs are rejected before narrowing in both modes. Legacy's wire input is uint16, so negative/nonfinite physical values have no corresponding legacy CAN input.
- A direct 2001.1875-RPM value rounds to raw 16010 (2001.25RPM); input0x200's 0.125-RPM resolution cannot encode such a half-step. Ordinary fractional values like1500.125 are exact raw integers before the mapping.
- New transmission trigger remains a10-ms schedule; the old receive-driven trigger is not copied.
- ARC is not consumed by a locally suppressed/unoffered frame. An immediate driver rejection still consumes one because the frame was offered.
- Initialized per-owner policy state replaces the legacy local pointer-init error and static callback counter.

For raw 12001 (1500.125RPM) with bands on, all eight golden frames are:

```text
F1 80 3E FF FF FF FF 00
F1 80 3E FF FF FF FF 11
F1 80 3E FF FF FF FF 22
F1 80 3E FF FF FF FF 33
F1 80 3E FF FF FF FF 44
F1 80 3E FF FF FF FF 55
F1 80 3E FF FF FF FF 66
F1 80 3E FF FF FF FF 77
```

## Changed existing expectations — complete list

The original seven gateway tests remain present. Changes were listed before editing and implement the approved decisions:

1. `test_reverse_rpm_and_disabled_override`: input 1500 -> output 2000 with bands on,1500 off; override is now1 after valid input instead of0. Historical test name retained.
2. `test_fractional_rpm_characterization`:1500.125 ->2000 with bands on,1500.125 off (previously1500 in both). Added16009 ->2001.125 to verify precision above the bands.
3. `test_stale_command_characterization`: after 600 ms gap, expect **override 0 / speed 0**, replacing persisted2000. Added fresh-command recovery to enabled2001.125.
4. `test_bad_dlc_and_unknown_id_preserve_value`: the prior valid1500 setup yields2000 with bands on,1500 off; malformed/unknown input preserves that output. Rejection behavior is unchanged.
5. `test_tsc_counter_checksum_and_timing`: the 10-ms grid, modulo8 ARC and checksum-formula assertions are unchanged; final payload bytes/checksums now reflect the approved wire image. New full-byte golden/vector tests cover those differences.
6. `test_all_nine_engine_exports`: unchanged assertions.
7. `test_export_periods`: unchanged assertions.

The robustness suite's existing expectations are unchanged; a new assertion verifies post-encode calls equal driver-send calls after suppression, rejection and TX-context exhaustion. New gateway tests cover boundary wire frames, timeout boundary/recovery, valid-then-invalid source preservation and invalid queued API updates. Suite setup additionally checks boot and invalid-first-command behavior. Pure tests cover all requested vectors in both modes, NaN/±infinity, negatives, range/rounding limits, timeout disable, wraparound, stale event counting and duplicate snapshot provenance.

## Files and RAM

Production changes: `Kconfig`; both target `.conf` fragments; new `include/throttle_policy.hpp`; `include/duramax/duramax_hooks.hpp`; `include/reacher/reacher_hooks.hpp`; generic hook/provenance plumbing in `can_active_object.hpp`, `can_commands.hpp`, `can_endpoint.hpp`, `translator_active_object.hpp`; remove uint16 intermediate in `reacher_to_duramax_signal_table.hpp`.

Tests/report: `tests/host/throttle_test.cpp`, `tests/oracle/legacy_throttle.hpp`, gateway config/source, robustness source, `tests/run_native.sh`, this report. No devicetree edits, no new translation unit, no generated-file edits, no new forwarding definitions, and `git diff 788e2f9 -- resources` is empty.

Native production ELF, compared with verified Task1/3 build:

| Section | Before Task2 | After Task2 | Added |
|---|---:|---:|---:|
| data | 57500 | 57836 |336 bytes|
| BSS |107826|108098|272 bytes|
| data+BSS |165326|165934|**608 bytes**|

Production AO symbol sizes increase144bytes total (Duramax+64,Reacher+80); enlarged snapshots and translator buffers account for additional storage. The 20-byte source metadata fits within existing command variant storage sizes. Native gateway configuration reports DuramaxAO40080,ReacherAO19312,DuramaxSnapshot7168,ReacherSnapshot576bytes; different kernel configs change AO layout, so these test-target sizes are not the production sizes. No extra stack, retained bank or runtime heap allocation. ARM alignment, linker sections and actual SRAM cost remain unmeasured.

## Verification commands and results

Environment: Zephyr 4.4.2 at `dccb09599635bdff17633fa7e9dab014b91dce90`, GCC 13.3.0, west 1.5.0, Python 3.12.14. The pre-Task2 baseline was recorded in Task1's report: production native build, scheduler, diagnostics host tests,7/7 gateway and1/1 robustness passed. After policy implementation but before approved expectation updates, the four corresponding old gateway tests failed as expected; no unapproved expectation was changed. An intermediate reused build directory had an invalid-object archive/link error; a fresh build directory resolved it, and final builds below passed.

From `/workspace/scratch/308c3d8edb06`:

```bash
export PATH="$PWD/zephyr-env/.venv/bin:$PATH"
export ZEPHYR_BASE="$PWD/zephyr-env/zephyr"
bash canlink_work/tests/run_native.sh "$PWD/task-work/task2-final"
zephyr-env/.venv/bin/python canlink_work/tests/dbc/validate.py
git -C canlink_work diff --check
git -C canlink_work diff 788e2f9 -- resources
```

The runner contains the exact compilation/execution commands, explicitly builds production with `boards/native_sim.conf` and `boards/native_sim.overlay`, and sets `ZEPHYR_TOOLCHAIN_VARIANT=host`. Results:

- Production `native_sim/native/64`: build PASS.
- Standalone scheduler: PASS; light60001/heavy44119 over600000ms.
- Pure diagnostics ASan/UBSan: PASS.
- Pure throttle ASan/UBSan: PASS, both band modes and all listed vectors/ARC values. LeakSanitizer is disabled because this host cannot inspect `/proc`; tested code allocates no heap.
- Real gateway loopback, bands ON: **11/11 PASS**,6.830s simulated test bodies.
- Real gateway loopback, bands OFF: **11/11 PASS**,6.830s simulated test bodies. Generated config confirms `# CONFIG_CANLINK_THROTTLE_BAND_MAPPING is not set`.
- Real-kernel fake-driver robustness: **1/1 PASS**,0.698s, including new driver-offer/post-hook assertion.
- Strict DBC inventory/round-trip validation: PASS; Duramax unchanged; Reacher 14 messages / 47 signals with existing numeric/wire definitions preserved.
- Diff whitespace check: PASS. Resource diff: empty.

Native tests use real `k_msgq`/`k_poll`, production main/translators/hooks/codecs and controllable CAN backends. They do not emulate Cortex-M interrupt timing, STM32 bxCAN arbitration/ACK behavior, electrical faults, unplug/replug, or real reset retention. No ARM toolchain/build or board run was available. No claims about those hardware properties are made.

## Publication status

User approval to publish the existing Task1/3 commits was received. Direct `git push` failed because no shell GitHub credential is available. The authenticated GitHub connector then returned 403 `Resource not accessible by integration` when attempting to create a tree. No remote branch/commit was created or updated. A Git bundle preserves the original local commits and Task2 commit without rewriting their identities. Restoring repository write permission or pushing that bundle from an authenticated checkout is required; this is an access blocker, not a request for renewed approval.
