package main

import (
	"fmt"
	"log"
	"net"
	"os"

	"github.com/cilium/ebpf/link"
)

//go:generate go run github.com/cilium/ebpf/cmd/bpf2go xdp main.c

func main() {
	var objs xdpObjects
	if err := loadXdpObjects(&objs, nil); err != nil {
		log.Fatal("Loading eBPF objects:", err)
	}
	defer objs.Close()

	ifname := "ens33"
	fmt.Println(ifname)
	iface, err := net.InterfaceByName(ifname)
	if err != nil {
		log.Fatalf("Getting interface %s: %s", ifname, err)
	}

	link, err := link.AttachXDP(link.XDPOptions{
		Program:   objs.XdpMain,
		Interface: iface.Index,
	})
	if err != nil {
		log.Fatal("Attaching XDP:", err)
	}
	defer link.Close()

	stop := make(chan os.Signal, 5)
	<-stop
	log.Print("Received signal, exiting..")
}
