.........sendto function().....
int sendto(int sockfd,const void msg,int len,unsigned int flags,const struct sockaddr *to,int tolen);
......recefrom function......
int recvfrom(int sockf, void *buf, int len,unsigned int flags, struct soaddr *from,int lfromlen);
........udp echo main function.......
#include "unp.h"
int main(int argc,char **argv)
{
 int sockfd;
 struct sockaddr_in servaddr,cliaddr;
 sockfd=socket(AF_INET,SOCK_DGRAM,0);
 bzero(&servaddr,sizeof(srvaddr))
 servaddr.sin_family=AF_INET;
 servaddr.sin_adr.s_addr=htol(INADDR_ANY);
 servaddr.sin_port=htons(SERV_PORT);
 Bind(sockfd,(SA *) servaddr,sizeof(servddr));
 dg_echo(sockfd,(SA *) &cliaddr,sizeof(cliaddr));
}

........dg echo function.....
#include "unp.h"
oid dg_echo(int sockfd,SA *pcliaddr,socklen_t clilen)
{
 int n;
 socklen_t len;
 char mesg[MAXLINE];
 for( ; ; )
 {
  len=clilen;
  n=Recvfrom(sockfd,mesgn,0,pcliaddr,len);
 }
}
