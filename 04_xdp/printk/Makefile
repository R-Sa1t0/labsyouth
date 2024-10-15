all: build dettach attach

debug: format sanitize build dettach attach

include ../Makefile
MAIN = -c main.c
CC = clang-18
CFLAGS = -target bpf -g -Wall -Wextra  -O2 -o main.o

build:
	$(CC) $(CFLAGS) $(MAIN) $(LIBS)

watch:
	sudo cat /sys/kernel/debug/tracing/trace_pipe

attach:
	sudo ip -n N2 link set dev N2-N1 xdp obj main.o sec main

test:
	sudo ip netns exec N1 ping fc00::2

detach:
	sudo ip -n N2 link set dev N2-N1 xdp off