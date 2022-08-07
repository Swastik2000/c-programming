#inclue(stdio.h>
#inclue<netinet/in.h>
#inclue<netbd.h>
#define SER_TCP_PORT 5035
int main(int argc,char**argv)
{
 int sockfd,newsockfd,clength;
 struct sockaddr_inserv_addr,cli_addr;
 char buffer[409];
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 serv_addr.sin_family=AF_INET;
 serv_addr.sin_addr=INADDR_ANY;
 printf("\nStart");
 bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
 printf("\nListening..");
 printf("\n")
 listen(sockfd,5);
 clength=sizeof(cli_addr);
 newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clength);
 print("\nAccept");
 print("\n");
 read(newsockfd,buffer,4096);
 printf("\client message:%s",buffer);
 write(newsockfd,buffe,4096);
 printf("\n");
 close(sockfd);
 return 0;
} 
 
