all: build dettach attach

include ../Makefile
MAIN = -c main.c
CC = clang-18
CFLAGS = -target bpf -g -Wall -Wextra  -O2 -o xdp.o

build:
	$(CC) $(CFLAGS) $(MAIN) $(LIBS)

attach:
	sudo ip -n N1 link set dev N1-N2 xdp obj xdp.o sec xdp
	sudo ip -n N1 link set dev N1-C1 xdp obj xdp.o sec xdp

detach:
	sudo ip -n N1 link set dev N1-N2 xdp off
	sudo ip -n N1 link set dev N1-C1 xdp off