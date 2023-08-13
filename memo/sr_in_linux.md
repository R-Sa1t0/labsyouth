おかしいところ : 
 - L2VPNの設定がIP Routeとしてしか設定できない
     - 例 : https://github.com/slankdev/tinet/tree/master/examples/basic_srv6/linux/l2vpn
     - 本来は
         - C1とC2が同じセグメントなはず
         - トンネルとして利用するデバイスとsrc/dst addrとsidだけ指定すればよいはず
     - 今は、
         - セグメントが分離されている (10.0.0.0/24 -> 10.0.0.0/24と10.0.1.0/24) 
         - 宛先ip(prefix)を指定する必要がある
     - L2VPNはトンネル先まで含めて同じセグメントになるはず
     - 自分はセグメントAにいる -> 自分が直接接続しているAに対する(遠回りに見える)ip routeは無視されて使われない -> トンネル先にEthernetフレームが届かない
 - 

 - 2018 : https://github.com/tinynetwork/tinet/tree/master/examples/basic_srv6/linux/l2vpn
     - 動かない
 - 2018 : https://github.com/tinynetwork/tinet/tree/master/examples/basic_srv6/linux/vpn_v4_per_ce
     - 動かない
 - 
