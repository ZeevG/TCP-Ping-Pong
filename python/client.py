#! /usr/local/bin/python

import socket
import random
import time

from utils import send_variable_length, recv_variable_length

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

addr = ("localhost", 8765)
s.connect(addr)

multiplier = random.randint(0, 100)
msg = " ".join(["PING"]*multiplier)

print "Sending: '{}' ({} 'PINGs')".format(msg, multiplier)
start_time = time.clock()
send_variable_length(s, msg)

data = recv_variable_length(s)
print "Recieved: '{}'".format(data)

count = data.count("PONG")

trip_time = time.clock() - start_time

if count == multiplier:
    print "Recieved the correct response"
else:
    print "Problemo!"
    print "Recieved an INCORRECT response."
    print "Sent {} PINGs recieved {} PONGs".format(multiplier, count)

print "Full round trip time is {} seconds".format(trip_time)
