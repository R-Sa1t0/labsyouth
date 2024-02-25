package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"net"
	"syscall"

	"golang.org/x/net/ipv6"
)

func main() {
	var err error
	fd, _ := syscall.Socket(syscall.AF_INET6, syscall.SOCK_RAW, syscall.IPPROTO_RAW)
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

type ip6header struct {
	Version      int    // protocol version
	TrafficClass int    // traffic class
	FlowLabel    int    // flow label
	PayloadLen   int    // payload length
	NextHeader   int    // next header
	HopLimit     int    // hop limit
	Src          net.IP // source address
	Dst          net.IP // destination address
}

func (h *ip6header) Marshal() ([]byte, error) {
	if h == nil {
		return nil, nil
	}
	if h.Version != 6 {
		return nil, fmt.Errorf("bad version: %d", h.Version)
	}
	hdrlen := ipv6.HeaderLen //+ len(h.ExtensionHeaders)
	b := make([]byte, hdrlen)
	b[0] = byte(h.Version << 4)
	b[0] |= byte(h.TrafficClass >> 4)
	b[1] = byte(h.TrafficClass<<4) | byte(h.FlowLabel>>16)
	b[2] = byte(h.FlowLabel >> 8)
	b[3] = byte(h.FlowLabel)
	binary.BigEndian.PutUint16(b[4:6], uint16(h.PayloadLen))
	b[6] = byte(h.NextHeader)
	b[7] = byte(h.HopLimit)
	copy(b[8:24], h.Src)
	copy(b[24:40], h.Dst)
	//if len(h.ExtensionHeaders) > 0 {
	//	copy(b[ipv6.HeaderLen:], h.ExtensionHeaders)
	//}
	return b, nil
}

func pkt() []byte {
	h6 := ip6header{
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

	out, err := h6.Marshal()
	if err != nil {
		log.Fatal(err)
	}

	var pkt []byte = append(out)
	//fmt.Println(pkt)
	return pkt
}
