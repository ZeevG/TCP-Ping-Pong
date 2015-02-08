#! /usr/local/bin/python

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

addr = ("localhost", 8765)
s.connect(addr)

print "sending PING"

s.send("PING")

data = s.recv(4)
print "recieved: {}".format(data)
