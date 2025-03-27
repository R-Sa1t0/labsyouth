all: detach clean encap.o attach

env-up:
	sudo ip netns add C1
	sudo ip netns add C2
	sudo ip netns add N1
	sudo ip netns add N2
	sudo ip netns add R1
	sudo ip netns exec R1 sysctl -w net.ipv6.conf.all.forwarding=1
	sudo ip -n C1 link set lo up
	sudo ip -n C2 link set lo up
	sudo ip -n N1 link set lo up
	sudo ip -n N2 link set lo up
	sudo ip -n R1 link set lo up
	sudo ip link add C1-N1 netns C1 mtu 1426 type veth \
		peer N1-C1 netns N1 mtu 1426
	sudo ip link add N1-R1 netns N1 addr 12:a6:e0:4b:94:4a type veth \
		peer R1-N1 netns R1 addr 66:aa:4b:a6:d6:ba
	sudo ip link add R1-N2 netns R1 addr 12:a6:e0:4b:94:4a type veth \
		peer N2-R1 netns N2 addr 66:aa:4b:a6:d6:ba
	sudo ip link add C2-N2 netns C2 mtu 1426 type veth \
		peer N2-C2 netns N2 mtu 1426
	sudo ip -n N1 link set N1-R1 up
	sudo ip -n R1 link set R1-N1 up
	sudo ip -n R1 link set R1-N2 up
	sudo ip -n N2 link set N2-R1 up
	sudo ip -n C1 link set C1-N1 up
	sudo ip -n N1 link set N1-C1 up
	sudo ip -n N2 link set N2-C2 up
	sudo ip -n C2 link set C2-N2 up
	sudo ip -n C1 addr add dev C1-N1 10.0.0.1/24
	sudo ip -n C2 addr add dev C2-N2 10.0.0.2/24
	sudo ip -n N1 -6 addr add dev N1-R1 fc00:1::2/64
	sudo ip -n R1 -6 addr add dev R1-N1 fc00:1::1/64
	sudo ip -n R1 -6 addr add dev R1-N2 fc00:2::1/64
	sudo ip -n N2 -6 addr add dev N2-R1 fc00:2::2/64
	sudo ip -n R1 -6 route add fd00:2::/64 via fc00:2::2
	sudo ip -n R1 -6 route add fd00:1::/64 via fc00:1::2
	sudo ip -n N1 -6 route add default via fc00:1::1
	sudo ip -n N2 -6 route add default via fc00:2::1
	sudo ip -n N1 -6 route add fd00:1::1/128 encap seg6local action End.DX2 oif N1-C1 dev N1-C1
	sudo ip -n N2 -6 route add fd00:2::1/128 encap seg6local action End.DX2 oif N2-C2 dev N2-C2	

env-down:
	sudo ip netns del C1
	sudo ip netns del C2
	sudo ip netns del N1
	sudo ip netns del N2
	sudo ip netns del R1

env-test:
	sudo ip netns exec N1 ping fc00:1::1 -c 5
	sudo ip netns exec N1 ping fc00:2::2 -c 5
	sudo ip netns exec N2 ping fc00:2::1 -c 5
	sudo ip netns exec N2 ping fc00:1::2 -c 5

encap.o:  encap.c
	clang -O2 -g -target bpf -c encap.c -o encap.o -Wall -Wextra -I/usr/include/aarch64-linux-gnu

clean:
	rm -f *.o *.ll

attach:
	sudo bpftool prog load ./encap.o /sys/fs/bpf/encap_n1 type xdp pinmaps /sys/fs/bpf/encap_n1_cfg
	sudo ./set_map.py --map /sys/fs/bpf/encap_n1_cfg/encap_cfg_map --ifidx-wan 3 --ifidx-lan 2 \
		--smac 12:a6:e0:4b:94:4a --dmac 66:aa:4b:a6:d6:ba \
		--saddr fc00:1::2 --daddr fd00:2::1 --sid fd00:2::1
	sudo ip netns exec N1 bpftool net attach xdpgeneric id \
		$$(sudo bpftool prog show pinned /sys/fs/bpf/encap_n1 | grep -o '^[0-9]\+') dev N1-C1
	sudo ip netns exec N1 bpftool net attach xdpgeneric id \
		$$(sudo bpftool prog show pinned /sys/fs/bpf/encap_n1 | grep -o '^[0-9]\+') dev N1-R1
	sudo bpftool prog load ./encap.o /sys/fs/bpf/encap_n2 type xdp pinmaps /sys/fs/bpf/encap_n2_cfg	
	sudo ./set_map.py --map /sys/fs/bpf/encap_n2_cfg/encap_cfg_map --ifidx-wan 2 --ifidx-lan 3 \
		--dmac 12:a6:e0:4b:94:4a --smac 66:aa:4b:a6:d6:ba \
		--saddr fc00:2::2 --daddr fd00:1::1 --sid fd00:1::1
	sudo ip netns exec N2 bpftool net attach xdpgeneric id \
		$$(sudo bpftool prog show pinned /sys/fs/bpf/encap_n2 | grep -o '^[0-9]\+') dev N2-R1
	sudo ip netns exec N2 bpftool net attach xdpgeneric id \
		$$(sudo bpftool prog show pinned /sys/fs/bpf/encap_n2 | grep -o '^[0-9]\+') dev N2-C2
	
detach:
	sudo ip -n N1 link set N1-C1 xdpgeneric off
	sudo ip -n N1 link set N1-R1 xdpgeneric off
	sudo ip -n N2 link set N2-R1 xdpgeneric off
	sudo ip -n N2 link set N2-C2 xdpgeneric off
	sudo rm -rf /sys/fs/bpf/encap_n1 /sys/fs/bpf/encap_n1_cfg
	sudo rm -rf /sys/fs/bpf/encap_n2 /sys/fs/bpf/encap_n2_cfg

test: 
	sudo ip netns exec N1 ping 10.0.0.2 -c 5
	sudo ip netns exec N2 ping 10.0.0.1 -c 5

check:
	sudo ls -lah /sys/fs/bpf
	sudo bpftool prog list name xdp_vpn
	sudo bpftool map dump name vpn_cfg_map
	sudo ip netns exec N2 tcpdump -vvvnnli N2-N1 | grep RT6

log:
	sudo cat /sys/kernel/debug/tracing/trace_pipe

