all: detach clean encap.o attach

env-up:
	sudo ip netns add C1
	sudo ip netns add N1
	sudo ip netns add N2
	sudo ip -n C1 link set lo up
	sudo ip -n N1 link set lo up
	sudo ip -n N2 link set lo up
	sudo ip link add C1-N1 netns C1 type veth peer N1-C1 netns N1
	sudo ip link add N2-N1 netns N2 type veth peer N1-N2 netns N1
	sudo ip -n C1 link set C1-N1 up
	sudo ip -n N1 link set N1-C1 up
	sudo ip -n N1 link set N1-N2 up
	sudo ip -n N2 link set N2-N1 up
	sudo ip -n N1 link set N1-N2 addr 12:a6:e0:4b:94:4a
	sudo ip -n N2 link set N2-N1 addr 66:aa:4b:a6:d6:ba
	sudo ip -n C1 addr add dev C1-N1 10.0.0.1/24
	sudo ip -n N1 -6 addr add fc00::1/64 dev N1-N2
	sudo ip -n N2 -6 addr add fc00::2/64 dev N2-N1
	sudo ip -n N1 -6 route add fd00::/64 via fc00::2

env-down:
	sudo ip netns del C1
	sudo ip netns del N1
	sudo ip netns del N2

encap.o:  encap.c
	clang -O2 -g -target bpf -c encap.c -o encap.o -Wall -Wextra -I/usr/include/aarch64-linux-gnu

clean:
	rm -f *.o *.ll

attach:
	sudo ip -n N1 link set N1-C1 xdpgeneric obj ./encap.o sec xdp	
	sudo ip -n N1 link set N1-N2 xdpgeneric obj ./encap.o sec xdp

detach:
	sudo ip -n N1 link set N1-C1 xdpgeneric off
	sudo ip -n N1 link set N1-N2 xdpgeneric off


check:
	sudo ls -lah /sys/fs/bpf
	sudo bpftool prog list

log:
	sudo cat /sys/kernel/debug/tracing/trace_pipe

