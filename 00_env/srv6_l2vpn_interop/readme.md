 - baseはsrv6_l2vpn_hack
 - ノード名を変えて、l2vpn_hackと同時に起動できるように
 - N1のencap設定を無効化してある
```
sudo ip netns exec IC2 nc -lu 8080
sudo ip netns exec IC1 nc -u 10.0.1.2 8080

sudo ip netns exec IC1 socat UDP-SENDTO:10.0.1.2:8020,sourceport=8010 -
sudo ip netns exec IC2 socat UDP-SENDTO:10.0.1.1:8010,sourceport=8020 -
```