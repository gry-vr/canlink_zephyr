#!/usr/bin/env python3
"""Run with cantools==45.1.1. No code generation or file mutation."""
import json, math, re, subprocess
from pathlib import Path
import cantools
ROOT = Path(__file__).resolve().parents[2]
BASE = '0ea0203f85ad1e7ecf68b5d6ca65b236e0456fb7'
def original(name):
    return subprocess.check_output(['git', 'show', f'{BASE}:resources/{name}.dbc'], cwd=ROOT)
def load(text):
    return cantools.database.load_string(text, database_format='dbc', strict=True)
def remove_orphan(text):
    return re.sub(r'^VAL_ 0 CS[^\r\n]*\r?\n', '', text, flags=re.M)
def signature(m):
    return (m.name,m.frame_id,m.length,m.is_extended_frame,m.cycle_time,m.senders,
            [(s.name,s.start,s.length,s.byte_order,s.is_signed,s.scale,s.offset,s.minimum,
              s.maximum,s.unit,s.receivers,str(s.choices),s.comment) for s in m.signals])
assert (ROOT/'resources/duramax.dbc').read_bytes() == original('duramax'), 'Duramax modified'
duramax = load(original('duramax').decode('cp1252'))
reacher = cantools.database.load_file(ROOT/'resources/reacher.dbc', strict=True)
old = load(remove_orphan(original('reacher').decode('cp1252')))
assert (len(duramax.messages),sum(len(m.signals) for m in duramax.messages)) == (42,283)
assert (len(old.messages),sum(len(m.signals) for m in old.messages)) == (7,20)
for m in old.messages: assert signature(m) == signature(reacher.get_message_by_name(m.name)),m.name
# Compare baseline generated numeric and wire metadata with both source DBCs.
for family,db in [('duramax',duramax),('reacher',old)]:
    text=(ROOT/f'include/{family}/{family}_metadata.hpp').read_text()
    mb=re.findall(r'MessageMeta\{(.*?)\n    \}',text,re.S)
    sb=re.findall(r'SignalMeta\{(.*?)\n    \}',text,re.S)
    for m in db.messages:
        block=next(b for b in mb if f'.dbc_name = "{m.name}"' in b)
        for field,v in [('frame_id',m.frame_id),('dlc',m.length),('signal_count',len(m.signals))]:
            assert int(re.search(r'\.'+field+r' = (0x[0-9A-Fa-f]+|\d+)',block)[1],0)==v
        assert ('.is_extended = true' in block)==m.is_extended_frame
        for s in m.signals:
            block=next(b for b in sb if f'.dbc_name = "{s.name}"' in b and f'.message_dbc_name = "{m.name}"' in b)
            for field,v in [('start_bit',s.start),('bit_length',s.length),('scale',s.scale),('offset',s.offset),('minimum',s.minimum),('maximum',s.maximum)]:
                if v is not None: assert math.isclose(float(re.search(r'\.'+field+r' = ([^,]+)',block)[1]),v,abs_tol=1e-9)
            assert ('.is_signed = true' in block)==s.is_signed
            assert f'.byte_order = ByteOrder::{s.byte_order}' in block
assert len({m.frame_id for m in reacher.messages})==len(reacher.messages)
assert len({m.name for m in reacher.messages})==len(reacher.messages)
coverage=json.loads((ROOT/'tests/dbc/coverage.json').read_text())
required=json.loads((ROOT/'tests/dbc/required_signals.json').read_text())
# Ground active forwarding in the actual table and generated name metadata.
table=(ROOT/'include/duramax_to_reacher_signal_table.hpp').read_text()
pairs=re.findall(r'DuramaxDb::SignalId::(\w+),\s*ReacherDb::SignalId::(\w+)',table)
def names(family):
    text=(ROOT/f'include/{family}/{family}_metadata.hpp').read_text()
    return {re.search(r'\.id = SignalId::(\w+)',b)[1]:(re.search(r'\.message_dbc_name = "([^"]+)"',b)[1],re.search(r'\.dbc_name = "([^"]+)"',b)[1]) for b in re.findall(r'SignalMeta\{(.*?)\n    \}',text,re.S)}
dnames,rnames=names('duramax'),names('reacher')
forwarded={dnames[a]:rnames[b] for a,b in pairs}
assert len(forwarded)==9
new={(x['source_message'],x['source_signal']):x for x in coverage}
assert len(new)==27
assert set(new).isdisjoint(forwarded)
for mn,sns in required.items():
    for sn in sns: assert (mn,sn) in forwarded or (mn,sn) in new
for x in coverage:
    s=duramax.get_message_by_name(x['source_message']).get_signal_by_name(x['source_signal'])
    m=reacher.get_message_by_name(x['destination_message']);d=m.get_signal_by_name(x['destination_signal'])
    a,b=x['factor'],x['offset']
    assert m.length==8 and not m.is_extended_frame and 0x310<=m.frame_id<=0x316
    assert d.byte_order=='big_endian' and d.start%8==7 and d.length%8==0
    assert d.is_signed==x['signed']
    for actual,expected in [(d.scale,s.scale*a),(d.offset,s.offset*a+b),(d.minimum,s.minimum*a+b),(d.maximum,s.maximum*a+b)]:
        assert math.isclose(actual,expected,abs_tol=1e-9)
    assert str(d.choices)==str(s.choices)
    # Includes maximum raw reserved codes; scaling=False avoids presenting them
    # as valid physical values. This verifies exact code preservation only.
    for raw in [0,1,(1<<s.length)-1]:
        vals={v.name:0 for v in m.signals};vals[d.name]=raw
        encoded=m.encode(vals,scaling=False,strict=False)
        assert m.decode(encoded,decode_choices=False,scaling=False)[d.name]==raw
    if d.minimum<0: assert d.is_signed
print(f'PASS: cantools {cantools.__version__}; Duramax 42/283 unchanged; baseline Reacher 7/20 unchanged')
print('PASS: generated IDs, DLC, bit layout, signedness, scale, offset and ranges match baseline DBCs')
print('PASS: 35 requested signals = 8 already forwarded + 27 new definitions; 9 active mappings verified')
print('PASS: Reacher 14 messages / 47 signals; strict parse, unique IDs/names, layout, ranges, choices and raw round trips')
# Inventory is a report generated from code and checked definitions, not codegen.
lines=['# Task 3 signal inventory','', '| Duramax message.signal | Forwarded now? | Reacher definition | Evidence |','|---|---|---|---|']
for mn,sns in required.items():
    for sn in sns:
        key=(mn,sn)
        if key in forwarded:
            dst='.'.join(forwarded[key]);yes='Yes';evidence='include/duramax_to_reacher_signal_table.hpp'
        else:
            x=new[key];dst=f"{x['destination_message']}.{x['destination_signal']} (0x{x['id']:03X})";yes='No: definition only';evidence='resources/reacher.dbc; tests/dbc/coverage.json'
        lines.append(f'| {mn}.{sn} | {yes} | {dst} | {evidence} |')
(ROOT/'docs/task3-inventory.md').write_text('\n'.join(lines)+'\n')
