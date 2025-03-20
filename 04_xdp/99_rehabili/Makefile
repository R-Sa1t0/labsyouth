.PHONY: all
all: clean gen build run

include ../Makefile

gen:
	go generate

build:
	go build -o ./a.out

run:
	sudo ./a.out

clean:
	rm -f ./a.out
