.PHONY: all

all: up

up:
	cd test-topo/P2P && tinet upconf | sudo bash -x

test:
	sudo python3 main.py

down:
	cd test-topo/P2P && tinet down | sudo bash -x

clean:
	rm -r tmp