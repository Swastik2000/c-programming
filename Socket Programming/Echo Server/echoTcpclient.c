#include<stdio.h>
#include<netinet/in.h>
#include <sys/socket.h>
#include<stdlib.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>
#define MAXLINE 1024
void str_cli(FILE *fp, int sockfd);
int main(int argc, char **argv)
{
	int	sockfd;
	struct sockaddr_in	servaddr;
	if (argc != 3)
		fprintf(stderr,"usage: tcpcli <IPaddress:port>");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))==0)
			printf("Connect Success\n");
	str_cli(stdin, sockfd);		/* do it all */
	exit(0);
}// close main 
void str_cli(FILE *fp, int sockfd)
{void str_cli(FILE *fp, int sockfd)
	char sendline[MAXLINE], recvline[MAXLINE];
    ssize_t n;
    bzero(sendline,sizeof(sendline));
    bzero(recvline,sizeof(sendline));
    printf("Enter messages for client::\n");
	while (fgets(sendline, MAXLINE, fp) != NULL) {//EOF
		write(sockfd, sendline, strlen(sendline));
        n=read(sockfd,recvline,MAXLINE);
        if (n == 0){
			fprintf(stderr,"str_cli: server terminated prematurely\n");
            return;
        }
        recvline[n]=0;
        fputs(recvline,stdout);
        bzero(sendline,sizeof(sendline));
        bzero(recvline,sizeof(sendline));	
	}
}
