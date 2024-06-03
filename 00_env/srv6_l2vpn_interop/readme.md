 - baseはsrv6_l2vpn_hack
 - ノード名を変えて、l2vpn_hackと同時に起動できるように
 - N1のencap設定を無効化してある
```
sudo ip netns exec C2 nc -lu 8080
sudo ip netns exec C1 nc -u 10.0.1.2 8080
```