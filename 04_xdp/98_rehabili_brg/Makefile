all: brg.o

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



KERNEL_HEADERS := /usr/include
xdp_bridge.o:  brg.c
	clang -S \
	    -target bpf \
	    -D __BPF_TRACING__ \
	    -I$(KERNEL_HEADERS) \
	    -Wall \
	    -Wno-unused-value \
	    -Wno-pointer-sign \
	    -Wno-compare-distinct-pointer-types \
	    -Werror \
	    -O2 -emit-llvm -c -g $< -o ${@:.o=.ll}
	llc -march=bpf -filetype=obj -o $@ ${@:.o=.ll}

clean:
	rm -f *.o *.ll

attach:
	sudo bpftool prog load ./brg.o /sys/fs/bpf/xdp_brg type xdp

