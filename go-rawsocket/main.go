package main

import (
	"fmt"
	"net"

	"golang.org/x/net/ipv4"
)

func main() {
	// Create a UDP connection
	conn, err := net.DialUDP("udp4", nil, &net.UDPAddr{
		IP:   net.IPv4(127, 0, 0, 1),
		Port: 1234,
	})
	if err != nil {
		panic(err)
	}

	// Create an instance of ipv4.PacketConn
	p := ipv4.NewPacketConn(conn)

	// Create an IP header
	h := ipv4.Header{
		Version:  4,
		Len:      20,
		TotalLen: 20,
		TTL:      64,
		Protocol: 17,
		Dst:      net.IPv4(127, 0, 0, 1),
	}

	// Write the packet to the network
	if _, err := p.WriteTo([]byte("Hello, world!"), &h, nil); err != nil {
		panic(err)
	}

	fmt.Println("Packet sent successfully!")
}
