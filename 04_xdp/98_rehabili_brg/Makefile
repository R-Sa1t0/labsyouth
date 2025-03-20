all: detach clean brg.o attach

env-up:
	sudo ip netns add C1
	sudo ip netns add C2
	sudo ip netns add N1
	sudo ip -n C1 link set lo up
	sudo ip -n C2 link set lo up
	sudo ip -n N1 link set lo up
	sudo ip link add C1-N1 netns C1 type veth peer N1-C1 netns N1
	sudo ip link add C2-N1 netns C2 type veth peer N1-C2 netns N1
	sudo ip -n C1 addr add dev C1-N1 10.0.0.1/24
	sudo ip -n C2 addr add dev C2-N1 10.0.0.2/24
	sudo ip -n C1 link set C1-N1 up
	sudo ip -n N1 link set N1-C1 up
	sudo ip -n N1 link set N1-C2 up
	sudo ip -n C2 link set C2-N1 up

env-down:
	sudo ip netns del C1
	sudo ip netns del C2
	sudo ip netns del N1



brg.o:  brg.c
	clang -O2 -g -target bpf -c brg.c -o brg.o

clean:
	rm -f *.o *.ll

attach:
	sudo bpftool prog load ./brg.o /sys/fs/bpf/xdp_brg type xdp
	sudo bpftool map update pinned /sys/fs/bpf/brg_ports key hex 00 00 00 00 value hex 00 00 00 02
	sudo bpftool map update pinned /sys/fs/bpf/brg_ports key hex 01 00 00 00 value hex 00 00 00 03

detach:
	sudo rm -f /sys/fs/bpf/xdp_brg
	sudo rm -f /sys/fs/bpf/brg_ports

check:
	sudo bpftool prog list	
