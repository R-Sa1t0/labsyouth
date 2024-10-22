package main

import (
	"fmt"
	"log"
	"net"
	"os"

	"github.com/cilium/ebpf/link"
)

//go:generate go run github.com/cilium/ebpf/cmd/bpf2go xdp_l2brg main.c

func main() {
	var objs xdp_l2brgObjects
	if err := loadXdp_l2brgObjects(&objs, nil); err != nil {
		log.Fatal("Loading eBPF objects:", err)
	}
	defer objs.Close()

	iflist := []string{"N1-C1", "N1-N2"}
	for _, ifname := range iflist {
		//	ifname := "N1-C1"
		fmt.Println(ifname)
		iface, err := net.InterfaceByName(ifname)
		if err != nil {
			log.Fatalf("Getting interface %s: %s", ifname, err)
		}

		link, err := link.AttachXDP(link.XDPOptions{
			Program:   objs.XdpL2brg,
			Interface: iface.Index,
		})
		if err != nil {
			log.Fatal("Attaching XDP:", err)
		}
		defer link.Close()
	}

	stop := make(chan os.Signal, 5)
	<-stop
	log.Print("Received signal, exiting..")
}
