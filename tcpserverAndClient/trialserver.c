#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h> // struct sockaddr_in is stored here
#include<stdlib.h>
#include<string.h>
// add headers
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#define MAXLINE 200


void gelhi(int sockhold){
    int n;
    char buff[MAXLINE];
    n=read(sockhold, buff, MAXLINE);
    printf("Data Recived= %s  \n",&buff );
    write(sockhold, buff, n);
}
int main(){
    //variable
    int sock, sockhold, br;
    pid_t pid;
    socklen_t serverlen, clilen;
    struct sockaddr_in server,cliserver;
    // Socket Creation
    sock=(socket(AF_INET, SOCK_STREAM, 0));
    if ( sock > 0){
        printf("Socket creation successfull \n");
    }
    else{
        printf(" Socket creation failed \n");
        return 1;
    }

        // Server Creation details
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port= htons(0);
    // Binding
    serverlen=sizeof(server);
    if(bind(sock,(struct sockaddr *)&server,sizeof(server))==0){
    
        printf("Binding Successfull \n");
    }
    else{
        printf("Binding Unsuccessful \n %d",&br);
        exit(2);
    }
    getsockname(sock,(struct sockaddr *)&server,&serverlen);
    printf("Port Number: %d \n",ntohs(server.sin_port));
    // Listen
    listen(sock,1021);
    // Accept
    for ( ; ; ){
    clilen=sizeof(struct sockaddr_in);
    sockhold = accept(sock,(struct sockaddr *)&cliserver,&clilen);
    pid = fork();
    if(pid ==0){
        close(sock);
        
        gelhi(sockhold);
        exit(0);
    }
    close(sockhold);
    }
    return 0;
}