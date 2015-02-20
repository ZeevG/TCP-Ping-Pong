import struct


def recv_variable_length(socket):
    data = socket.recv(4)
    # print "Attempting to unpack a python struct"
    (msg,) = struct.unpack("i", data)

    data = ""
    remaining = int(msg)
    while remaining > 0:
        print "recv loop"
        recieved = socket.recv(remaining)
        remaining = remaining - len(recieved)
        data += recieved

    return data


def send_variable_length(socket, message):
    msg_len = len(message)
    socket.send(struct.pack("i", msg_len))
    socket.send(message)
