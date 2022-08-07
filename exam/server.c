#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc,char const *argv[]){

    int server_fd,new_socket,valread;
    int opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Ping back from server";
    
    //make the socket function
    
    if((server_fd = socket(AF_INET,SOCK_STREAM,0))==0){
            perror("Socket failed");
            exit(EXIT_FAILURE);
    }
    
    //assign values to structure
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    // check for binding // bind returns 0 if the bind is successfull else -1
    
    if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0){
            perror("Bind failed");
            exit(EXIT_FAILURE);    
    }
    
    //make the listen function
    
    if(listen(server_fd,3)<0){
            perror("Listening failed");
            exit(EXIT_FAILURE);
    }
    
    if((new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0){
            perror("Accept failed");
            exit(EXIT_FAILURE);
    }
    
    valread = read(new_socket,buffer,1024);
    printf("%s\n",buffer);
    send(new_socket,hello,strlen(hello),0);
    printf("Hello message sent\n");
    

    return 0;
}
