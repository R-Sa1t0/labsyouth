import logging
import sys
from pyroute2 import IPRoute, netlink
import pytest
import subprocess
import scapy.all as scapy
import threading
import time


logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)
logger = logging.getLogger(__name__)


def make_tap(ifi):
    ip=IPRoute()
    try:
        ip.link('add', ifname=ifi['name'], kind='tuntap', mode='tap')
        if_idx=ip.link_lookup(ifname=ifi['name'])[0]
#        ip.link('set', index=if_idx, state='up')
        ip.link('set', index=if_idx, address=ifi['address'])
    except netlink.NetlinkError as e:
        logger.error(f"Error '{ifi['name']}': {e}")
        pass
    finally:
        ip.close()

def activete_tap(ifi):
    ip=IPRoute()
    name=ifi["name"]
    try:
        if_idx=ip.link_lookup(ifname=name)[0]
        ip.link('set', index=if_idx, state='up')
    except netlink.NetlinkError as e:
        logger.error(f"Error '{name}': {e}")
        pass
    finally:
        ip.close()

def del_tap(ifi):
    name=ifi["name"]
    ipr=IPRoute()
    try:
        idx = ipr.link_lookup(ifname=name)
        if not idx:
            raise ValueError(f"{name} not found")
        ipr.link('del', index=idx[0])
    except netlink.NetlinkError as e:
        logger.error(f"Error '{name}': {e}")
        pass
    finally:
        ipr.close()



ifinfo = [
    {"name":'tap-lan', 'address':'a2:00:00:00:00:22'},
    {"name":'tap-wan', 'address':'a6:00:00:00:00:22'}
]

@pytest.fixture
def init_env():
    def del_env():
        for ifi in ifinfo:
            del_tap(ifi)
    # make tap
    for ifi in ifinfo:
        make_tap(ifi)
    # run program
    process = subprocess.Popen(['./a.out', 'fc00:1::2', 'fc00:11::1', 'tap-lan', 'tap-wan', 'a6:00:00:00:00:11'])
    yield
    process.kill()
    del_env()



expkt = (
    scapy.Ether(dst="a2:00:00:00:00:22", src="a2:00:00:00:00:11")/
    scapy.IP(src="10.0.0.1", dst="10.0.0.2")/
    scapy.UDP(sport=1000, dport=2000)/
    scapy.Raw("HELLO")
)
encaped_pkt=(
    scapy.Ether(dst="a6:00:00:00:00:11", src="a2:00:00:00:00:22") /
    scapy.IPv6(src="fc00:1::2", dst="fc00:11::1") /
    scapy.IPv6ExtHdrSegmentRouting(addresses=['fc00:11::1'], nh=143) /
    scapy.Ether(dst="ff:ff:ff:ff:ff:ff", src="a2:00:00:00:00:11") /
    scapy.IP(src="10.0.0.1", dst="10.0.0.2") /
    scapy.UDP(sport=1000, dport=2000) /
    scapy.Raw("HELLO")
)
found_encaped_pkt=False

def test_seg6encap(init_env):
    def sniff_callback(pkt):
        global found_encaped_pkt
        scapy.wrpcap("pkt.pcapng", pkt, append=True)
        if encaped_pkt in pkt:
            found_encaped_pkt = True
    
    sniffer = threading.Thread(target=scapy.sniff, kwargs={
        "iface": ifinfo[1]['name'], 
        "prn": sniff_callback,
        "timeout": 20
    })
    sniffer.start()

    time.sleep(2)
    scapy.sendp(expkt, iface=ifinfo[0]['name'])

    sniffer.join()
    assert found_encaped_pkt, "Expected packet not found in captured packets within the timeout period"


if __name__ == "__main__":
    x = int(input('mode : '))
    match x:
        case 1:            
            for ifi in ifinfo:
                make_tap(ifi)
                activete_tap(ifi)
        case 2:
            for ifi in ifinfo:
                del_tap(ifi)
        case _ :
            print("1: make tap, 2: del tap")