#!/usr/bin/env python3
import argparse
import struct
import socket
import subprocess

def mac_to_bytes(mac_str):
    return bytes(int(x, 16) for x in mac_str.split(':'))

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--map", required=True)
    parser.add_argument("--ifidx-wan", type=int, required=True)
    parser.add_argument("--ifidx-lan", type=int, required=True)
    parser.add_argument("--smac", required=True)
    parser.add_argument("--dmac", required=True)
    parser.add_argument("--saddr", required=True)
    parser.add_argument("--daddr", required=True)
    parser.add_argument("--sid", required=True)
    parser.add_argument("--decapsid", required=True)
    args = parser.parse_args()

    smac_bytes = mac_to_bytes(args.smac)
    dmac_bytes = mac_to_bytes(args.dmac)
    saddr_bytes = socket.inet_pton(socket.AF_INET6, args.saddr)
    daddr_bytes = socket.inet_pton(socket.AF_INET6, args.daddr)
    sid_bytes = socket.inet_pton(socket.AF_INET6, args.sid)
    decapsid_bytes = socket.inet_pton(socket.AF_INET6, args.decapsid)
    packed_value = struct.pack("<II6s6s16s16s16s16s",
                               args.ifidx_wan,
                               args.ifidx_lan,
                               smac_bytes,
                               dmac_bytes,
                               saddr_bytes,
                               daddr_bytes,
                               sid_bytes,
                               decapsid_bytes)
    packed_key = struct.pack("B", 0)
    key_hex = packed_key.hex()
    value_hex = " ".join(f"{b:02x}" for b in packed_value)

    cmd = f"bpftool map update pinned {args.map} key hex {key_hex} value hex {value_hex}"
    print(cmd)

    subprocess.run(cmd, shell=True, check=True)

