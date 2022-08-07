//udp clinet driver program
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MAXLINE 1000
#define PORT 5000

//driver code
int main()
{
 char buffer[100];
 char *message="Hello server";
 int sockfd,n;
 struct sockaddr_in servaddr;
 //clear servaddr
 bsero(&servaddr,sizeof(servaddr));
 servaddrsin_addr.s_addr=inet_addr("127.0.0.1");
 servaddr.sin_port=htons(PORT);
 servaddr.sin_family=AF_INET;
 
 //create datagram socket
 sockfd=socket(AF_INET,SOCK_DGRAM,0);
 
 //connect to server
 if(connect(sockfd,(struct sockaddr *)&servaddr, sizeof(servaddr))<0)
 {
   printf("\n Error:Connect Failed \n");
   exit(0);
 }
 //request to send program
 //no need to specify server address in sendto
 //send stores the peers IP and port
 sendto(sockfd,message,MAXLINE,0,(struct sockaddr*)NULL.sizof(servaddr));
 //waiting for response
 recvfro(sockfd,bufer,sizeof(buffer),0,(struct sockaddr*)NULL,NULL);
 puts(buffer);
 //close the descripter
 close(sockfd);
}
