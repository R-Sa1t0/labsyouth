import scapy.all as scapy

def recv_packet():
    ex_pkt=(
        scapy.Ether(dst="a6:00:00:00:00:11", src="a2:00:00:00:00:22") /
        scapy.IPv6(src="fc00:1::2", dst="fc00:11::1") /
        scapy.IPv6ExtHdrSegmentRouting(addresses=['fc00:11::1'], nh=143) /
        scapy.Ether(dst="ff:ff:ff:ff:ff:ff", src="a2:00:00:00:00:11") /
        scapy.IP(src="10.0.0.1", dst="10.0.0.2") /
        scapy.UDP(sport=1000, dport=2000) /
        scapy.Raw("HELLO")
    )
    
    ex_pkt2=(
        scapy.Ether(dst="a6:00:00:00:00:11", src="a2:00:00:00:00:22") /
        scapy.IPv6(src="fc00:1::2", dst="fc00:11::1") /
        scapy.IPv6ExtHdrSegmentRouting(addresses=['fc00:11::1'], nh=143) /
        scapy.Ether(dst="a2:00:00:00:00:22", src="a2:00:00:00:00:11") /
        scapy.IP(src="10.0.0.1", dst="10.0.0.2") /
        scapy.ICMP(type=8, code=0)
    )

    def packet_filter(pkt):
        parsed_pkt = scapy.Ether(bytes(pkt))
        return parsed_pkt == ex_pkt or parsed_pkt == ex_pkt2

    
    while True:
        sniffed = scapy.sniff(iface="host-t1-2", timeout=10, count=1, lfilter=packet_filter)
        for pkt in sniffed:
            print(pkt)
            if packet_filter(pkt):
                print("Received specified packet, exiting.")
                return

recv_packet()
