```
sudo ip netns exec C2 nc -lu 8080
sudo ip netns exec C1 nc -u 10.0.1.2 8080
```