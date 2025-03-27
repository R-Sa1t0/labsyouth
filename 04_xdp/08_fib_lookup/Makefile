.PHONY: all
all: clean gen build run

include ../Makefile

.PHONY: gen
gen:
	go generate

.PHONY: build
build:
	go build -o ./a.out

.PHONY: run
run:
	sudo ./a.out

.PHONY: clean
clean:
	rm -f ./a.out

.PHONY: test
test:
	sudo bpftool prog
