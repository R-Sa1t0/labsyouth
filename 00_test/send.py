import scapy.all as scapy
import time

time.sleep(1)

def send_packet():
    pkt = (
        scapy.Ether(dst="a2:00:00:00:00:22", src="a2:00:00:00:00:11")/
        scapy.IP(src="10.0.0.1", dst="10.0.0.2")/
        scapy.UDP(sport=1000, dport=2000)/
        scapy.Raw("HELLO")
    )
    scapy.sendp(pkt, iface="host-t1-1", verbose=False)
    print("Packet sended.")
    exit(0)

send_packet()