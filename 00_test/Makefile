.PHONY: all

all: up

up:
	sudo ip netns add t1
	sudo ip -n t1 link set lo up
	sudo ip link add t1-host-1 netns t1 type veth peer host-t1-1
	sudo ip link add t1-host-2 netns t1 type veth peer host-t1-2
	sudo ip -n t1 link set dev t1-host-1 addr a2:00:00:00:00:22
	sudo ip -n t1 link set dev t1-host-1 up
	sudo ip -n t1 link set dev t1-host-2 addr a6:00:00:00:00:22
	sudo ip -n t1 link set dev t1-host-2 up
	sudo ip link set dev host-t1-1 addr a2:00:00:00:00:11
	sudo ip link set dev host-t1-1 up
	sudo ip link set dev host-t1-2 addr a6:00:00:00:00:11
	sudo ip link set dev host-t1-2 up

test:
	sudo ip netns exec t1 ./a.out fc00:1::2 fc00:11::1 t1-host-1 t1-host-2 a6:00:00:00:00:11 > /dev/null

down:
	sudo ip netns del t1

clean:
	sudo python3 recv.py
#	sudo python3 send.py
