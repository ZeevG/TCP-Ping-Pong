#! /usr/local/bin/python

import socket
import threading

from utils import recv_variable_length, send_variable_length


def main():
    print "creating socket"
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    print "binding socket to localhost"
    server_socket.bind(("localhost", 8765))

    print "listening"
    server_socket.listen(5)

    client_num = 0
    while True:
        #accept connections from outside
        print "waiting for a client to connect..."
        (clientsocket, address) = server_socket.accept()
        #now do something with the clientsocket
        #in this case, we'll pretend this is a threaded server

        t = threading.Thread(target=handle_client, args=(clientsocket, client_num))
        t.run()

        client_num += 1


def handle_client(socket, ident):
    data = recv_variable_length(socket)
    print "Recieved {}".format(data)

    count = data.count("PING")
    message = " ".join(["PONG"]*count)

    send_variable_length(socket, message)


if __name__ == "__main__":
    main()
