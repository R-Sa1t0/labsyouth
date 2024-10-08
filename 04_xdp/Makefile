setup:
	sudo ip netns add C1
	sudo ip netns add N1
	sudo ip netns add N2
	sudo ip netns add C2
	sudo ip link add C1-N1 netns C1 type veth peer N1-C1 netns N1
	sudo ip link add N1-N2 netns N1 type veth peer N2-N1 netns N2
	sudo ip link add N2-C2 netns N2 type veth peer C2-N2 netns C2
	sudo ip -n C1 link set C1-N1 up
	sudo ip -n C2 link set C2-N2 up
	sudo ip -n C1 addr add 192.168.0.1/24 dev C1-N1
	sudo ip -n C2 addr add 192.168.0.2/24 dev C2-N2
	sudo ip -n N1 link set N1-C1 up
	sudo ip -n N2 link set N2-C2 up
	sudo ip -n N1 link set N1-N2 up
	sudo ip -n N2 link set N2-N1 up
	sudo ip -n N1 -6 addr add fc00::1/64 dev N1-N2
	sudo ip -n N2 -6 addr add fc00::2/64 dev N2-N1

clean:
	sudo ip netns del N1
	sudo ip netns del N2
	sudo ip netns del C1
	sudo ip netns del C2	

format:
	@for file in *.c *.h *.cpp *.hpp; do \
		if [ -f "$$file" ]; then \
			clang-format -i "$$file"; \
		fi; \
	done