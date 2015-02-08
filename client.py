#! /usr/local/bin/python

import socket
import struct
import random

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

addr = ("localhost", 8765)
s.connect(addr)

multiplier = random.randint(0, 100)
msg = " ".join(["PING"]*multiplier)
msgLen = len(msg)

print "sending '{}' ({} 'PINGs') with a message length of {}".format(msg, multiplier, msgLen)

s.send(struct.pack("i", msgLen))
s.send(msg)

data = s.recv(4)
print "recieved: {}".format(data)
