#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>


char* recieve(int client_socket){
    char * payload;
    long payload_size;
    long remaining;
    int result;

    remaining = payload_size = recieve_size(client_socket);

    payload = (char*)malloc((sizeof(char) * payload_size) + 1);
    memset(payload, (int)NULL, (sizeof(char) * payload_size) + 1);

    while (remaining > 0) {
        remaining = remaining - recv(client_socket, &payload[payload_size-remaining], remaining, 0);
    }

    return payload;
}

int recieve_size(int client_socket){
    int payload_size;
    int remaining = sizeof(int);
    
    // Just read the first 4 bytes
    // Potential problem here if recv returns less than 4 bytes
    // Not sure how likely that is to happpen
    // Could store data in a bytes array and cast it to an int
    recv(
         client_socket,
         &payload_size,
         remaining,
         0
     );

    return payload_size;
}

void send_response(int socket, char* payload){
    int payload_size;
    int result;

    payload_size = strlen(payload);

    result = send(socket, &payload_size, sizeof(int), 0);
    result = send(socket, payload, payload_size, 0);
    if(result < 0) print_error();

}

void print_error(){
    perror("Problemo!");
    exit(EXIT_FAILURE);
}