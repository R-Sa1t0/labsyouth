# Topo
```
tofu@R-OB-Dev-VM01:~/Dev/labsyouth$ sudo cat /sys/kernel/debug/tracing/available_filter_functions | grep seg6
bpf_push_seg6_encap
bpf_lwt_seg6_action
bpf_lwt_seg6_store_bytes
bpf_lwt_seg6_adjust_srh
lwt_seg6local_func_proto
seg6_net_exit
seg6_genl_set_tunsrc
seg6_genl_dumphmac_done
seg6_genl_dumphmac_start
seg6_genl_dumphmac
seg6_genl_get_tunsrc
seg6_genl_sethmac
seg6_net_init
seg6_validate_srh
seg6_exit
seg6_encap_nlsize
seg6_encap_cmp
seg6_destroy_state
seg6_fill_encap_info
seg6_build_state
seg6_do_srh_inline
seg6_do_srh_encap
seg6_do_srh
seg6_input
seg6_output
seg6_iptunnel_exit
seg6_local_get_encap_size
seg6_local_cmp_encap
seg6_lookup_any_nexthop
seg6_local_fill_encap
seg6_local_input
seg6_local_build_state
seg6_local_destroy_state
seg6_lookup_nexthop
seg6_bpf_has_valid_srh
seg6_local_exit
seg6_hmac_cmpfn
seg6_free_hi
seg6_hmac_exit
seg6_hmac_net_exit
seg6_hmac_compute
seg6_hmac_info_lookup
seg6_hmac_validate_skb
seg6_push_hmac
seg6_hmac_info_add
seg6_hmac_info_del
seg6_hmac_net_init
tofu@R-OB-Dev-VM01:~/Dev/labsyouth$
```



```
root@Dev-VM01:/home/tofu/Dev/labsyouth/topo/srv6_test# tcpdump -i N1-R1 -n -vvv
tcpdump: listening on N1-R1, link-type EN10MB (Ethernet), snapshot length 262144 bytes
^C20:50:06.411751 IP6 (hlim 63, next-header Routing (43) payload length: 122) fc00:900:1::1 > fc00:900:2::10: RT6 (len=2, type=4, segleft=0, last-entry=0, flags=0x0, tag=0, [0]fc00:900:2::10) IP (tos 0x0, ttl 64, id 2330, offset 0, flags [DF], proto ICMP (1), length 84)
    10.0.1.1 > 10.0.2.1: ICMP echo request, id 53219, seq 0, length 64
20:50:06.411813 IP6 (flowlabel 0x6c683, hlim 63, next-header ICMPv6 (58) payload length: 170) fc00:120::2 > fc00:900:1::1: [icmp6 sum ok] ICMP6, destination unreachable, unreachable route fc00:900:2::10
20:50:07.412811 IP6 (hlim 63, next-header Routing (43) payload length: 122) fc00:900:1::1 > fc00:900:2::10: RT6 (len=2, type=4, segleft=0, last-entry=0, flags=0x0, tag=0, [0]fc00:900:2::10) IP (tos 0x0, ttl 64, id 2389, offset 0, flags [DF], proto ICMP (1), length 84)
    10.0.1.1 > 10.0.2.1: ICMP echo request, id 53219, seq 1, length 64
20:50:07.412859 IP6 (flowlabel 0x6c683, hlim 63, next-header ICMPv6 (58) payload length: 170) fc00:120::2 > fc00:900:1::1: [icmp6 sum ok] ICMP6, destination unreachable, unreachable route fc00:900:2::10
20:50:08.414022 IP6 (hlim 63, next-header Routing (43) payload length: 122) fc00:900:1::1 > fc00:900:2::10: RT6 (len=2, type=4, segleft=0, last-entry=0, flags=0x0, tag=0, [0]fc00:900:2::10) IP (tos 0x0, ttl 64, id 2556, offset 0, flags [DF], proto ICMP (1), length 84)
    10.0.1.1 > 10.0.2.1: ICMP echo request, id 53219, seq 2, length 64
20:50:08.414104 IP6 (flowlabel 0x6c683, hlim 63, next-header ICMPv6 (58) payload length: 170) fc00:120::2 > fc00:900:1::1: [icmp6 sum ok] ICMP6, destination unreachable, unreachable route fc00:900:2::10
20:50:09.415301 IP6 (hlim 63, next-header Routing (43) payload length: 122) fc00:900:1::1 > fc00:900:2::10: RT6 (len=2, type=4, segleft=0, last-entry=0, flags=0x0, tag=0, [0]fc00:900:2::10) IP (tos 0x0, ttl 64, id 2567, offset 0, flags [DF], proto ICMP (1), length 84)
    10.0.1.1 > 10.0.2.1: ICMP echo request, id 53219, seq 3, length 64
20:50:09.415400 IP6 (flowlabel 0x6c683, hlim 63, next-header ICMPv6 (58) payload length: 170) fc00:120::2 > fc00:900:1::1: [icmp6 sum ok] ICMP6, destination unreachable, unreachable route fc00:900:2::10
20:50:10.416613 IP6 (hlim 63, next-header Routing (43) payload length: 122) fc00:900:1::1 > fc00:900:2::10: RT6 (len=2, type=4, segleft=0, last-entry=0, flags=0x0, tag=0, [0]fc00:900:2::10) IP (tos 0x0, ttl 64, id 2739, offset 0, flags [DF], proto ICMP (1), length 84)
    10.0.1.1 > 10.0.2.1: ICMP echo request, id 53219, seq 4, length 64
20:50:10.416698 IP6 (flowlabel 0x6c683, hlim 63, next-header ICMPv6 (58) payload length: 170) fc00:120::2 > fc00:900:1::1: [icmp6 sum ok] ICMP6, destination unreachable, unreachable route fc00:900:2::10
20:50:11.417905 IP6 (hlim 63, next-header Routing (43) payload length: 122) fc00:900:1::1 > fc00:900:2::10: RT6 (len=2, type=4, segleft=0, last-entry=0, flags=0x0, tag=0, [0]fc00:900:2::10) IP (tos 0x0, ttl 64, id 2840, offset 0, flags [DF], proto ICMP (1), length 84)
    10.0.1.1 > 10.0.2.1: ICMP echo request, id 53219, seq 5, length 64
20:50:11.417987 IP6 (flowlabel 0x6c683, hlim 63, next-header ICMPv6 (58) payload length: 170) fc00:120::2 > fc00:900:1::1: [icmp6 sum ok] ICMP6, destination unreachable, unreachable route fc00:900:2::10
20:50:11.659511 IP6 (hlim 255, next-header ICMPv6 (58) payload length: 32) fe80::dcf8:d8ff:fe84:80c0 > fc00:110::1: [icmp6 sum ok] ICMP6, neighbor solicitation, length 32, who has fc00:110::1
          source link-address option (1), length 8 (1): de:f8:d8:84:80:c0
            0x0000:  def8 d884 80c0
20:50:11.659557 IP6 (hlim 255, next-header ICMPv6 (58) payload length: 32) fe80::784e:89ff:feec:7c2 > fc00:110::2: [icmp6 sum ok] ICMP6, neighbor solicitation, length 32, who has fc00:110::2
          source link-address option (1), length 8 (1): 7a:4e:89:ec:07:c2
            0x0000:  7a4e 89ec 07c2
20:50:11.659582 IP6 (hlim 255, next-header ICMPv6 (58) payload length: 24) fc00:110::2 > fe80::784e:89ff:feec:7c2: [icmp6 sum ok] ICMP6, neighbor advertisement, length 24, tgt is fc00:110::2, Flags [router, solicited]
20:50:11.659708 IP6 (hlim 255, next-header ICMPv6 (58) payload length: 24) fc00:110::1 > fe80::dcf8:d8ff:fe84:80c0: [icmp6 sum ok] ICMP6, neighbor advertisement, length 24, tgt is fc00:110::1, Flags [router, solicited]
20:50:12.419226 IP6 (hlim 63, next-header Routing (43) payload length: 122) fc00:900:1::1 > fc00:900:2::10: RT6 (len=2, type=4, segleft=0, last-entry=0, flags=0x0, tag=0, [0]fc00:900:2::10) IP (tos 0x0, ttl 64, id 2962, offset 0, flags [DF], proto ICMP (1), length 84)
    10.0.1.1 > 10.0.2.1: ICMP echo request, id 53219, seq 6, length 64
20:50:12.419352 IP6 (flowlabel 0x6c683, hlim 63, next-header ICMPv6 (58) payload length: 170) fc00:120::2 > fc00:900:1::1: [icmp6 sum ok] ICMP6, destination unreachable, unreachable route fc00:900:2::10
20:50:13.420580 IP6 (hlim 63, next-header Routing (43) payload length: 122) fc00:900:1::1 > fc00:900:2::10: RT6 (len=2, type=4, segleft=0, last-entry=0, flags=0x0, tag=0, [0]fc00:900:2::10) IP (tos 0x0, ttl 64, id 3171, offset 0, flags [DF], proto ICMP (1), length 84)
    10.0.1.1 > 10.0.2.1: ICMP echo request, id 53219, seq 7, length 64
20:50:13.420647 IP6 (flowlabel 0x6c683, hlim 63, next-header ICMPv6 (58) payload length: 170) fc00:120::2 > fc00:900:1::1: [icmp6 sum ok] ICMP6, destination unreachable, unreachable route fc00:900:2::10

20 packets captured
20 packets received by filter
0 packets dropped by kernel
root@Dev-VM01:/home/tofu/Dev/labsyouth/topo/srv6_test# 
```