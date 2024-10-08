all: build dettach attach

debug: format sanitize build dettach attach

include ../Makefile
MAIN = -c main.c
CC = clang-18
CFLAGS = -target bpf -g -Wall -Wextra  -O2 -o main.o
DEBUGFLAGS_1 = -target bpf -g -Wall -Wextra -fsanitize=memory -o main.o
DEBUGFLAGS_2 = -target bpf -g -Wall -Wextra -fsanitize=address -o main.o

build:
	$(CC) $(CFLAGS) $(MAIN) $(LIBS)

sanitize: 
	$(CC) $(DEBUGFLAGS_1) -c $(MAIN) $(LIBS)
	$(CC) $(DEBUGFLAGS_2) -c $(MAIN) $(LIBS)

attach:
	sudo ip -n N2 link set dev N2-N1 xdp obj main.o sec main

detach:
	sudo ip -n N2 link set dev N2-N1 xdp off