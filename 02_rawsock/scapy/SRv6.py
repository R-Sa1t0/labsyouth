from scapy.all import *

def send_ipv6_packet():
    packet = (
        Ether(dst="5e:93:21:63:f5:cd") /
        IPv6(src="fc00:2::2", dst="fc00:11::1") /
        IPv6ExtHdrSegmentRouting(addresses=['fc00:11::1'], nh=143) /
        Ether(src="52:54:00:22:22:22", dst="52:54:00:11:11:11") /
        IP(src="10.0.1.2", dst="10.0.1.1") /
        UDP(sport=8080, dport=46550) /
        Raw("HALLO")
    )
    sendp(packet, iface="N2-R1")

if __name__ == "__main__":
    send_ipv6_packet()
