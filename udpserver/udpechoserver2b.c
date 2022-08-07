#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#define PORT 33456
#define MAXLINE 200
void dg_echo(int sockfd,struct sockaddr*pcliaddr,socklen_t client)
{
    int n;
    socklen_t len;
    char buffer[MAXLINE];
    memset(buffer,'\0',sizeof(buffer));
    for(;;)
     {
        len=client;
        n=recvfrom(sockfd,buffer,MAXLINE,0,pcliaddr,&len);
        printf("message from client %s\n",buffer);
        sendto(sockfd,buffer,n,0,pcliaddr,len);
        
    }
}
int main()
{
    int lisnfd,br;
    socklen_t clien,len;
    struct sockaddr_in servaddr,cliaddr;
    len=sizeof(servaddr);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(PORT);
    lisnfd=socket(AF_INET,SOCK_DGRAM,0);
    if(lisnfd<0)
    {
        fprintf(stderr,"Create error in socket\n");
        return 1;
    }
    br=bind(lisnfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(br==0)
    {
        printf("Bind success: with retur value=%d\n",br);
         printf("Server port number=%d\n",ntohs(servaddr.sin_port));
    printf("Server IP details=%s\n",inet_ntoa(servaddr.sin_addr));
    }
    else
    {
        printf("Bind unsucess: with return value=%d\n",br);
        printf("Retry.......");
        exit(2);
    }
    dg_echo(lisnfd,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
    printf("Connected client details.......");
    printf("Client port number=%d\n",ntohs(cliaddr.sin_port));
    printf("Client IP details=%s\n",inet_ntoa(cliaddr.sin_addr));
    return 0;
}
