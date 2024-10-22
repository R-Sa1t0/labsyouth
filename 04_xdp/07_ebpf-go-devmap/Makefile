.PHONY: all
all: clean gen build run

include ../Makefile

.PHONY: gen
gen:
	go generate

.PHONY: build
build:
	go build -o ./a.out

.PHONY: writemap
writemap:
	sudo bpftool map update name devmap key 0 0 0 0 value 1 0 0 0
	sudo bpftool map update name devmap key 0 0 0 0 value 2 0 0 0
	sudo bpftool map update name devmap key 0 0 0 0 value 3 0 0 0
	sudo bpftool map update name devmap key 0 0 0 0 value 4 0 0 0

.PHONY: run
run:
	sudo ip netns exec N1 ./a.out

.PHONY: clean
clean:
	rm -f ./a.out

.PHONY: test
test:
	sudo ip netns exec N2 bpftool prog
