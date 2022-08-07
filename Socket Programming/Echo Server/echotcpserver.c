#include<stdio.h>
#include<netinet/in.h>
#include <sys/socket.h>
#include<stdlib.h>
#include <arpa/inet.h>
#include<unistd.h>
#include <errno.h>
#include<strings.h>
#include<sys/wait.h>
#define MAXLINE 1024
void str_echo(int );
void sig_child(int signo){
   pid_t pid;
   int stat;
   pid=wait(&stat);
   printf("Child %d terminated\n",pid);
}

int main(int argc, char **argv)
{
	int	sockfd, confd,count=1;
	pid_t	 pid;
	socklen_t	 clilen,len;
    len=sizeof(struct sockaddr_in);
	struct sockaddr_in	cliaddr, servaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port= htons(0);
	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    getsockname(sockfd,(struct sockaddr *)&servaddr,&len);
    printf("port=%d\n",ntohs(servaddr.sin_port));
	listen(sockfd, 10);
   //signal(SIGCHLD,sig_child);
	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		printf("Waiting for client %d to connect at port=%d\n",count,ntohs(servaddr.sin_port));
		confd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen);
         printf("Continue for loop\n");
       pid=fork();
		if ( pid == 0) {	/* child server process */
			close(sockfd);	/* close listening socket */
			str_echo(confd);	/* process the request */
			exit(0);
		}
		count=count+1;
		close(confd);			/* parent closes connected socket */
	}  
}
void str_echo(int confd)
{
	ssize_t	n;
	char	buf[MAXLINE];
	while ( (n = read(confd, buf, MAXLINE)) > 0)
		write(confd, buf, n);
}

