#include<untp.h>
int main(int argc,char **argv)
{
int sockfd;
struct spckaddr_in srveraddr;
if(argc!=2)
err_quiet(:usage:tcpcli<IPaddress>");
spckfd=socket(AF_INET,SOCK_STREAM,0);
bzzero(&serveraddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port htons(SERV_PORT);
Inet_pto(AF_INET,argv[1],&servaddr,size0f(servaddr));
connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
str_cli(stdin,sockfd);
exit(0);
}

