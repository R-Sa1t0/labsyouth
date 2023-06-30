package main

import (
	"fmt"
	"log"
	"net"
	"syscall"

	"golang.org/x/net/ipv6"
)

func main() {
	var err error
	fd, _ := syscall.Socket(syscall.AF_INET, syscall.SOCK_RAW, syscall.IPPROTO_RAW)
	addr := syscall.SockaddrInet6{
		Port: 0,
		Addr: [16]byte{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	}
	p := pkt()
	err = syscall.Sendto(fd, p, 0, &addr)
	if err != nil {
		log.Fatal("Sendto:", err)
	}
	fmt.Println(pkt())
}

func pkt() []byte {
	h6 := ipv6.Header{
		Version:      6,
		TrafficClass: 0,
		FlowLabel:    0,
		PayloadLen:   60, // 40 bytes for Header, 20 for padding
		NextHeader:   59,
		HopLimit:     20,
		Src:          net.IPv6loopback,
		Dst:          net.IPv6loopback,
	}
	fmt.Println(h6)

	out, err := h6.ParseHeader()
	out = ipv6.ParseHeader()
	if err != nil {
		log.Fatal(err)
	}

	var pkt []byte = append(out)
	//fmt.Println(pkt)
	return pkt
}
