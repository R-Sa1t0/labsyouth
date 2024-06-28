import os
import scapy.all as scapy
import pyroute2.netns as netns

def run_in_netns(ns_name, func, *args, **kwargs):
    pid = os.getpid()
    with netns(ns_name) as ns:
        ns.fork()
        result = func(*args, **kwargs)
        return result

def send_packet():
    pkt = (
        scapy.IP(src="10.0.0.1", dst="10.0.0.2")/
        scapy.UDP(sport=1000, dport=2000)/
        scapy.Raw("HELLO")
    )
    print(scapy.conf.ifaces)
    scapy.send(pkt, iface="T1-N1", verbose=False)
    exit(0)

def recv_packet():
    ex_pkt=(
        scapy.Ether(dst="a6:00:00:00:00:11", src="a6:00:00:00:00:22") /
        scapy.IPv6(src="fc00:1::2", dst="fc00:11::1") /
        scapy.IPv6ExtHdrSegmentRouting(addresses=['fc00:11::1'], nh=143) /
        scapy.Ether(src="a2:00:00:00:00:22", dst="a2:00:00:00:00:11") /
        scapy.IP(src="10.0.0.1", dst="10.0.0.2")/
        scapy.UDP(sport=1000, dport=2000)/
        scapy.Raw("HELLO")
    )
    print(scapy.conf.ifaces)
    sniffed = scapy.sniff(iface="T2-N1", timeout=10, count=1)
    for pkt in sniffed:
        parsed_pkt = scapy.Ether(bytes(pkt))
        if parsed_pkt == ex_pkt:
            print("Received specified packet, exiting.")
            exit(0)

run_in_netns("T2", recv_packet)
run_in_netns("T1", send_packet)