#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>


char* recieve(int client_socket){
    char * payload;
    int payload_size;

    payload_size = recieve_size(client_socket);

    payload = (char*)malloc((sizeof(char) * payload_size) + 1);
    memset(payload, (int)NULL, (sizeof(char) * payload_size) + 1);

    recv(client_socket, payload, payload_size, 0);
    
    return payload;
}

int recieve_size(int client_socket){
    int payload_size;
    
    // Just read the first 4 bytes
    recv(client_socket, &payload_size, sizeof(int), 0);
    
    return payload_size;
}

void send_response(int socket, char* payload){
    int payload_size;

    payload_size = strlen(payload);

    send(socket, &payload_size, sizeof(int), 0);
    send(socket, payload, payload_size, 0);

}

void print_error(){
    perror("Problemo!");
    exit(EXIT_FAILURE);
}