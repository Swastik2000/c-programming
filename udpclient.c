#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#define PORT 33468
#define MAXLINE 1000

void dg_cli(FILE *FP, int sockfd, const struct sockaddr* pservaddr, socklen_t servlen){
printf("dg_cli");
int n;
char sendline[MAXLINE], recvline[MAXLINE+1];
memset(sendline, '\0', sizeof(sendline));
memset(recvline, '\0', sizeof(recvline));
while(1){
printf("Enter the message ");
fgets(sendline,200,stdin);
sendto(sockfd,sendline,strlen(sendline),0,pservaddr,servlen);
printf("sent data \n");
n=recvfrom(sockfd,recvline,MAXLINE,0,NULL,NULL);
recvline[n]='\0';
fputs(recvline,stdout);
}
}


int main(int argc,char *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t len;
    len=sizeof(struct sockaddr_in);
    if(argc!=3)
    {
        fprintf(stderr,"socket create success....\n");
        return 1;
    }
    servaddr.sin_family=AF_INET;    
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    servaddr.sin_port=htons(atoi(argv[2]));
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd>0)
    {
        fprintf(stderr,"socket create success...\n");
    }
    else
    {
        fprintf(stderr,"create an error...\n");
        return 1;
    }
    printf("dg_cli out");
    dg_cli(stdin,sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    printf("connected server details \n");
    printf("connected server port details=%d \n",ntohs(servaddr.sin_port));
    printf("connected server ip details=%s \n",inet_ntoa(servaddr.sin_addr));
    getsockname(sockfd,(struct sockaddr*)&cliaddr, &len);
    exit(0);
}            
