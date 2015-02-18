#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> /* arpa?? */
#include <unistd.h>

using namespace std;

// forward declaring these
// using a header file is pointless
int get_payload_size(int client_socket);
void recieve_payload(int client_socket, char * data, int payload_size);
void print_error();


int main(int argc, char* argv []){  

    int client_no = 0;
    struct sockaddr_in my_addr;
    int s;

    cout << "Creating Socket" << endl;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0){
        print_error();
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8765);
    inet_pton(AF_INET, "127.0.0.1", &my_addr.sin_addr);

    if(bind(s, (sockaddr *) &my_addr, sizeof(sockaddr_in)) < 0){
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

        cout << "waiting for a client to connect..." << endl;
        client_socket = accept(s, &client_addr, &addr_len);
        if(client_socket < 0){
            print_error();
        }

        payload_size = get_payload_size(client_socket);
        payload = (char*)malloc(sizeof(char) * payload_size);
        recieve_payload(client_socket, payload, payload_size);

        cout << "Recieved "<< payload << endl;










    }



    return 0;
}

int get_payload_size(int client_socket){
    int payload_size;

    // Just read the first 4 bytes
    read(client_socket, &payload_size, 4);

    return payload_size;
}

void recieve_payload(int client_socket, char * data, int payload_size){

    read(client_socket, data, payload_size);

}

void print_error(){
    perror("Problemo!");
}