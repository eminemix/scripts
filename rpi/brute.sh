#!/bin/bash

iptables -N SSHATTACK
iptables -A SSHATTACK -j LOG --log-prefix "SSH bruteforce!" --log-level 7
iptables -A SSHATTACK -j DROP

iptables -A INPUT -i eth0 -p tcp -m state --dport 22 --state NEW -m recent --set
iptables -A INPUT -i eth0 -p tcp -m state --dport 22 --state NEW -m recent --update --seconds 120 --hitcount 4 -j SSHATTACK
