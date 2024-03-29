package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"net"
	"syscall"
)

const (
	ip4version   = 4  // protocol version
	ip4headerlen = 20 // header length without extension headers
)

type headerflags int
type hdr4 struct {
	Version  int         // protocol version
	Len      int         // header length
	TOS      int         // type-of-service
	TotalLen int         // packet total length
	ID       int         // identification
	Flags    headerflags // flags
	FragOff  int         // fragment offset
	TTL      int         // time-to-live
	Protocol int         // next protocol
	Checksum int         // checksum
	Src      net.IP      // source address
	Dst      net.IP      // destination address
	Options  []byte      // options, extension headers
}

func (h *hdr4) Marshal() ([]byte, error) {
	if h == nil {
		return nil, nil
	}
	if h.Len < ip4headerlen {
		return nil, fmt.Errorf("header length too small: %d", h.Len)
	}
	if h.Version != ip4version {
		return nil, fmt.Errorf("bad version: %d", h.Version)
	}
	hdrlen := ip4headerlen + len(h.Options)
	b := make([]byte, hdrlen)
	// 1. 左に4ビットシフト
	// 2. 右に2ビットシフト > AND演算で下位4ビットを取得
	// 3. OR演算で結合
	b[0] = byte(ip4version<<4 | (hdrlen >> 2 & 0x0f))
	// 最下位ビットは輻輳制御用のフラグ
	b[1] = byte(h.TOS)
	// 1. FragOffの下位13ビットを取得
	// 2. Flagsを13ビット左にシフト(<-?)して、intにする
	// 3. OR演算で結合
	flagsAndFragOff := (h.FragOff & 0x1fff) | int(h.Flags<<13)
	// パケット長を格納 (intの長さは環境依存らしい)
	binary.BigEndian.PutUint16(b[2:4], uint16(h.TotalLen))
	// フラグとフラグメントオフセットを格納
	binary.BigEndian.PutUint16(b[6:8], uint16(flagsAndFragOff))
	// フラグメンテーションが起きた時用
	binary.BigEndian.PutUint16(b[4:6], uint16(h.ID))
	// TTL
	b[8] = byte(h.TTL)
	// Protocol
	b[9] = byte(h.Protocol)
	// チェックサム
	binary.BigEndian.PutUint16(b[10:12], uint16(h.Checksum))
	if ip := h.Src.To4(); ip != nil {
		copy(b[12:16], ip[:net.IPv4len])
	}
	if ip := h.Dst.To4(); ip != nil {
		copy(b[16:20], ip[:net.IPv4len])
	} else {
		return nil, nil
	}
	if len(h.Options) > 0 {
		copy(b[ip4headerlen:], h.Options)
	}
	return b, nil
}

func main() {
	var err error
	fd, _ := syscall.Socket(syscall.AF_INET, syscall.SOCK_RAW, syscall.IPPROTO_RAW)
	addr := syscall.SockaddrInet4{
		Port: 0,
		Addr: [4]byte{127, 0, 0, 1},
	}
	p := pkt()
	err = syscall.Sendto(fd, p, 0, &addr)
	if err != nil {
		log.Fatal("Sendto:", err)
	}
	fmt.Println(pkt())
}

func pkt() []byte {
	h := hdr4{
		Version:  4,
		Len:      20,
		TotalLen: 20 + 10, // 20 bytes for IP, 10 for ICMP
		TTL:      64,
		Protocol: 1, // ICMP
		Dst:      net.IPv4(127, 0, 0, 1),
	}
	icmp := []byte{
		8, // type: echo request
		0, // code: not used by echo request
		0, // checksum (16 bit), we fill in below
		0,
		0, // identifier (16 bit). zero allowed.
		0,
		0, // sequence number (16 bit). zero allowed.
		0,
		0xC0, // Optional data. ping puts time packet sent here
		0xDE,
	}

	cs := csum(icmp)
	icmp[2] = byte(cs)
	icmp[3] = byte(cs >> 8)

	out, err := h.Marshal()
	if err != nil {
		log.Fatal(err)
	}

	var pkt []byte = append(out, icmp...)
	//fmt.Println(pkt)
	return pkt
}

func csum(b []byte) uint16 {
	var s uint32
	for i := 0; i < len(b); i += 2 {
		s += uint32(b[i+1])<<8 | uint32(b[i])
	}
	// add back the carry
	s = s>>16 + s&0xffff
	s = s + s>>16
	return uint16(^s)
}
