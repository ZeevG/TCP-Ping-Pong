import struct


def recv_variable_length(socket):
    data = socket.recv(4)
    print "Attempting to unpack a python struct"
    (msg,) = struct.unpack("i", data)

    print "Reading {0} more bytes".format(msg)
    data = socket.recv(int(msg))
    return data


def send_variable_length(socket, message):
    msg_len = len(message)
    socket.send(struct.pack("i", msg_len))
    socket.send(message)
