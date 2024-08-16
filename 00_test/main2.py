import scapy.all as scapy

def packet_to_scapy_code(packet):
    layers = []
    while packet:
        layer = packet.__class__.__name__
        fields = []
        for field, value in packet.fields.items():
            if isinstance(value, scapy.Packet):
                break
            fields.append(f"{field}={repr(value)}")
        layer_str = f"scapy.{layer}({', '.join(fields)})"
        layers.append(layer_str)
        packet = packet.payload
    
    return " / ".join(layers)

def raw_payload_to_scapy_code(raw_payload):
    try:
        inner_packet = scapy.Ether(raw_payload)
        return packet_to_scapy_code(inner_packet)
    except:
        return f"scapy.Raw(load={repr(raw_payload)})"

def process_packet(packet):
    scapy_code = packet_to_scapy_code(packet)
    if scapy.Raw in packet:
        raw_payload_code = raw_payload_to_scapy_code(packet[scapy.Raw].load)
        scapy_code += f" / {raw_payload_code}"
    print(packet)
    return scapy_code


def packet_callback(packet):
    scapy_code = process_packet(packet)
    with open('captured_packets_as_scapy_code.py', 'a') as f:
        f.write(f"{scapy_code}\n\n")
        print(scapy_code)


iface = 'host-t1-2'
print(f'Starting packet capture on interface {iface}')
scapy.sniff(iface=iface, prn=packet_callback)
