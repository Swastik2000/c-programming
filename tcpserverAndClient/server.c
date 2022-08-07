#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h> // struct sockaddr_in is stored here
#include<stdlib.h>
#include<string.h>

int main(){
    // Variables
    int sock;

    struct sockaddr_in server;
    int sockethold; // To hold the socket after connection
    char buff[1024]; // to hold the data
    int rval;


    // Socket Creation
    sock = socket(AF_INET, SOCK_STREAM,0);
    if (sock<0){
        printf("Failed to create a socket ");
        exit(1);
    }
    // creation of server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 5000;

    // Binding
    if(bind(sock,(struct sockaddr *)&server, sizeof(server)) == 0){
        printf("Binded");
    }
    else{
        printf(" Binding unsuccessfull choose another port ");
    }
    // Listiening
    listen(sock, 5); // 5 place indicates total number of connections possible
    // Accept
    for ( ; ; ){
        sockethold = accept(sock,(struct sockaddr *) 0, 0);
        if (sockethold == -1){
            printf("accept failed");
        }
    }

    return 0;
}