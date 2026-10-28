# Task 3 — Reacher definitions (no runtime changes)

Base: `0ea0203f85ad1e7ecf68b5d6ca65b236e0456fb7`. The intervening commit adds both DBCs and changes two main startup delays from 3 ms to 2 ms. Baseline native_sim build, scheduler test and all seven existing integration tests passed before edits.

## Inventory and gap

See [task3-inventory.md](task3-inventory.md) for all 35 requested source signals and evidence from the active translation table. Eight are already forwarded; **27** require definitions. The ninth active mapping (remote accelerator pedal position → EXPORT_0.actual_throttle) is outside the requested list. Existing misleading destination names remain unchanged.

Both original DBCs match the generated metadata: Duramax **42 messages / 283 signals**, Reacher **7 / 20**, including IDs, DLC, standard/extended flag, bit order, positions, widths, signedness, factors, offsets and physical bounds. The original Reacher file contains an orphan `VAL_ 0 CS` referencing no defined message/signal. Cantools 45.1.1 rejects it even with `strict=False`; this blocking defect was removed. No defined message or signal was removed or changed. Known existing ranges (such as EXPORT_B.oil_temp maximum 65536 in 16 bits) were left unchanged.

## Added layout

| ID / message | Group | Used bits |
|---|---|---|
| 0x310 EXPORT_10 | Ambient temperature, barometric pressure, intake-air temperature | 48 |
| 0x311 EXPORT_11 | Two distinct CAC temperature sources and manifold temperature | 64 |
| 0x312 EXPORT_12 | Engine elapsed time, intake mass flow, fuel rate | 48 |
| 0x313 EXPORT_13 | Actual/desired boost and injector metering rail pressure | 32 |
| 0x314 EXPORT_14 | Actual/driver/engine-demand/friction torque, torque mode, controlling source address | 64 |
| 0x315 EXPORT_15 | Available torque, load, actual/commanded VGT and wait-to-start lamp | 48 |
| 0x316 EXPORT_16 | Post-policy transmitted speed, TSC1 counter/checksum and transport sequence diagnostics | 40 |

All are standard 11-bit, eight-byte frames, Motorola/big-endian to follow existing EXPORT messages. Signals start at byte boundaries, occupy whole bytes, and never overlap. Unused bits have no new meaning. No existing message was repacked.

**ID assumption:** only the repository's allocation can be verified. Existing IDs are 0x200, 0x202, 0x300, 0x303, 0x308, 0x30B and 0x501. The locally free legacy-block IDs are 0x301, 0x302, 0x304–0x307, 0x309, 0x30A and 0x30C–0x30D, but these were not reused without your permission. 0x310–0x316 are provisionally allocated outside that block. Confirm against the complete deployed network before enabling any producer. No frames with these IDs are transmitted by this change.

## Scaling, signedness and unavailable values

Each new field retains its source raw code. Factors, offsets and valid physical bounds are transformed together, preserving source quantization:

- Temperatures: `F = C * 1.8 + 32`, following EXPORT_B. A 0.03125 C source becomes factor 0.05625 F and offset -459.4 F; a 1 C source becomes factor 1.8 F and offset -40 F.
- Pressures: `mBar = kPa * 10`, following EXPORT_0. Barometric factor becomes 5; boost factors become 20.
- Rail pressure: `Bar = MPa * 10`, following EXPORT_3; factor 0.00390625 MPa becomes 0.0390625 Bar.
- Time, mass flow, fuel rate, percent torque/load/VGT, enums, source address, counters and RPM retain their source units/factors/offsets/ranges. EASI's factor **0.000976562** is preserved exactly rather than silently changing it to 1/1024; its original maximum is preserved too.

All new signals with a negative physical minimum use signed fields. Those source fields are unsigned raw values with negative offsets. Widening them by one byte (8→16 or 16→24) preserves every original nonnegative raw code while providing signed storage, without shifting the offset or reducing the physical range. This also avoids the existing unsigned physical-temperature type problem. Generator support for signed 24-bit DBC fields must be confirmed during regeneration; ordinary cantools supports them. Existing signals are untouched.

Source `VAL_` tables are copied unchanged: wait-to-start 0 Off / 1 On / 2 Error / 3 Not available. Other requested signals do not declare value tables in this Duramax DBC. Source reserved raw codes remain representable even in widened fields (zero-extend their source raw pattern); they are **not** new valid physical measurements. Comments explicitly distinguish raw-code preservation from numeric validity. Future forwarding must recognize source unavailable/error encodings before numeric translation; this task does not implement J1939 decoding or invent a numeric failsafe. Where the source DBC admits the entire raw range without distinguishing special values, that ambiguity remains. Do not interpret a reserved raw value merely by applying factor and offset.

## Diagnostic judgment calls

Definitions for all explicitly requested signals are included, but none is wired. Recommended follow-up: publish TSC1 requested speed **as actually transmitted after policy**; do not mirror the RX store's similarly named TSC1 value. Counter/checksum are frame-integrity diagnostics, not engine telemetry, and should normally stay in the post-mortem log. Transport sequence alone is not useful telemetry without reassembly; normally leave it unwired. Their names and comments make these distinctions explicit. Including definitions preserves complete requested coverage without deciding to transmit them.

No cycle-time attributes existed in the original Reacher DBC. No period is invented here: message comments say definition-only/no assigned period. The existing runtime periods remain unchanged.

## Validation and scope

Command, from a Python environment with `cantools==45.1.1`:

```sh
python tests/dbc/validate.py
git diff 0ea0203 -- resources/duramax.dbc
```

Results: strict parsing PASS; 14 Reacher messages / 47 signals; unique IDs/names and no overlaps; all old message/signal semantics unchanged; all 35 requested signals covered; factors/offsets/ranges/choices verified against source; raw encode/decode round trips include all-ones source patterns; signed types checked for every negative range. **Duramax diff is empty.** The validator emits the inventory report. Added runtime RAM: **0 bytes**.

No DBC-to-project generator is committed. Generated C++ was not hand-edited. Regeneration needs the actual generator/templates, pinned cantools/Jinja versions, identifier/type-selection options, namespace/output layout and signed-24-bit support. It must update Reacher IDs, types, metadata, choices, codecs, store/build/validate implementations, Db aliases and compile-time counts as one reproducible operation.

Runtime wiring is a separate task: update `include/duramax_to_reacher_signal_table.hpp`, generated Reacher files through the generator, and `src/main.cpp` schedule/default setup; add codec/golden-vector and native gateway tests. Transmitted-TSC1 diagnostics require an owner-thread post-send observation path; the regular source RX translation table is not sufficient. Do not wire transport sequence until a diagnostic purpose or reassembly policy is selected.
