#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h> /* arpa?? */

#include "utils.h"


int main(int argc, char* argv []){  

    int client_no = 0;
    struct sockaddr_in my_addr;
    int s;

    printf("Creating Socket\n");

    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0){
        print_error();
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8765);
    inet_pton(AF_INET, "127.0.0.1", &my_addr.sin_addr);

    if(bind(s, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_in)) < 0){
        print_error();
    }

    if(listen(s, 5)){
        print_error();
    }

    while(1){
        struct sockaddr client_addr;
        socklen_t addr_len;
        int client_socket, payload_size;
        char* payload;
        char* response;

        printf("waiting for a client to connect...\n");
        client_socket = accept(s, &client_addr, &addr_len);
        if(client_socket < 0){
            print_error();
        }
        
        client_no++;

        // Recieve payload. Internally uses malloc.
        payload = recieve(client_socket);
        payload_size = strlen(payload);
        printf("Recieved: %s\n", payload);
        

        // Add 1 to the payload size 
        // Just call each PING 5 chars to account for space
        int num_pings = (payload_size + 1) / 5;

        // build response
        response = (char*)malloc(sizeof(char) * payload_size + 1);
        memset(response, (int)NULL, (sizeof(char) * payload_size) + 1);
        
        for(int ii = 0; ii < num_pings; ii++){
            
            // Check the payload contains "PING" in the expected location
            if(strncmp(payload+(ii*5), "PING", 4) == 0){
                
                if(ii < num_pings - 1){
                    strncpy(response+(ii*5), "PONG ", 5); // Space included "PONG "
                }else{
                    strncpy(response+(ii*5), "PONG", 4);
                }
            }
            
        }
        
        // send the response to the client
        send_response(client_socket, response);

    }



    return 0;
}



