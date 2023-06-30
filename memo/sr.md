## 各実装の資料
 - SREXT
     - https://github.com/netgroup/SRv6-net-prog/
     - https://netgroup.github.io/SRv6-net-prog/
 - Linux
     - https://github.com/torvalds/linux/tree/master/net/ipv6
 - Cisco/Juniper
## 関連RFC
 - RFC 7045 “Transmission and Processing of IPv6 Extension Headers”
     - https://datatracker.ietf.org/doc/rfc7045/
 - RFC 8200 “Internet Protocol, Version 6 (IPv6) Specification”
     - https://datatracker.ietf.org/doc/html/rfc8200
 - RFC 8754 “IPv6 Segment Routing Header (SRH)”
     - https://datatracker.ietf.org/doc/html/rfc8754
 - RFC 8986 “Segment Routing over IPv6 (SRv6) Network Programming”
     - https://datatracker.ietf.org/doc/html/rfc8986

## impl spec
### IPv6
 ```
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Version| Traffic Class |           Flow Label                  |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Payload Length        |  Next Header  |   Hop Limit   |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                                                               |
   +                                                               +
   |                                                               |
   +                         Source Address                        +
   |                                                               |
   +                                                               +
   |                                                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                                                               |
   +                                                               +
   |                                                               |
   +                      Destination Address                      +
   |                                                               |
   +                                                               +
   |                                                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```
 - version : v6 = 0110
 - Traffic Class = 0000 0000 (0x00)
 - Flow Label = 0000 0000 0000 0000 0000 (0x00)
 - Payload length = パケット全体の大きさ-普通のヘッダの大きさ
 - Next Header = 59 (No Next Header)
      - http://euclid.nmu.edu/~rappleto/Classes/CS442/Notes/IPv6_Header.html
 - Hop Limit = 64
 - あとは適当

### SRH
```
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 | Next Header   |  Hdr Ext Len  | Routing Type  | Segments Left |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |  Last Entry   |     Flags     |              Tag              |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                                                               |
 |            Segment List[0] (128-bit IPv6 address)             |
 |                                                               |
 |                                                               |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                                                               |
 |                                                               |
                               ...
 |                                                               |
 |                                                               |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                                                               |
 |            Segment List[n] (128-bit IPv6 address)             |
 |                                                               |
 |                                                               |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 //                                                             //
 //         Optional Type Length Value objects (variable)       //
 //                                                             //
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```