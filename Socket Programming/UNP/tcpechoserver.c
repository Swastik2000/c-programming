#include<stdio.h>
#include<sys/types.h>
#include<sys/soclet.h>
#include<netint/in.h>
#include<netdb.h>
#define SERV_TCP_[ORT 5035
int main(int argc,char *argv[])
{
int sockfd;
struct sockaddr_in serv_addr;
struct hostent *server;
char buffr[4096];
sockfd=socket(AF_INET,SOCK_STREAM,0);
serv_addr.sin_family=AF_INET;
serv_addr.sin_addrs_addr=inet_addr("127.0.0.1");
serv_addr.sin_port=htons(SERV_TCP_PORT);
printf("\nReady for sending data");
connect(sockfd,(struct sockaddr*)&serv_adr,sizeof(serv_addr));
printf("\nEnter the message send \n");
printf("\nClient:");
fgets(buffer,4096,stdin);
write(sockfd,buffer,4096);
printf("Serverecho:%s",buffer);
printf("\n");
close(sockfd);
}
