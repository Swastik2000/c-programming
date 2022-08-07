/* TCP echo server */
// add headers
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>
#define MAXLINE 200
void str_echo(int confd)
{
    int n;
    char buffer[MAXLINE];
    while(1)
    {
        while((n=read(confd, buffer, MAXLINE))>0)
        {
        
        printf("value of n=%d",n);
        
            write(confd, buffer, n);
        }
       if(n==0)
       {
       break;
       }
        if(n<0 && errno == EINTR)
        {
                continue;
        }
        if(n<0)
        {
            printf("read failed....\n");
            break;
        }
     }
}
void handel_fun(int sig)
{
    printf("SIGCHLD signal is generated ... \n");
}



int main(){
    //signal(SIGCHLD, SIG_IGN);
    
   int listenfd,confd,count=1,br;
   pid_t pid;
   socklen_t clilen,len;
   struct sockaddr_in servaddr,cliaddr;
   
   len=sizeof(servaddr);
   servaddr.sin_family=AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(0);
   
   
   
   listenfd=socket(AF_INET,SOCK_STREAM,0);
   if(listenfd>0){
         fprintf(stderr,"Socket created success\n");
   }
   else{
      fprintf(stderr,"socket creat error\n");
      return 1;
  }
  br=bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
  if(br==0){
       printf("bind success: with return value=%d\n",br);
   }
   else{
    printf("bind UNsuccess: with return value=%d\n",br);
    printf("Retry different port\n");
    exit(2);
   }
  getsockname(listenfd,(struct sockaddr *)&servaddr,&len);
  listen(listenfd,1024);
 
 
 

 
  for( ; ; )
  {
        clilen=sizeof(struct sockaddr_in);
        printf("Waiting for client %d in port=%d\n",count,ntohs(servaddr.sin_port));
        confd=accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
        printf("Connected client details...\n");
        printf("client port=%d\n",ntohs(cliaddr.sin_port)); 
        printf("client IP=%s\n",inet_ntoa(cliaddr.sin_addr));
         getsockname(confd,(struct sockaddr *)&servaddr,&len);
        printf("Server Details\n");
        printf("Sver port=%d\n",ntohs(servaddr.sin_port)); 
        printf("Server IP=%s\n",inet_ntoa(servaddr.sin_addr));
        printf("---------------------------------------------------------------\n");
        pid=fork();
        if(pid==0){     //child server process
           close(listenfd);
           //d0-------------------
           str_echo(confd);
           exit(0);
        }
        //parent serer process
        count=count+1;
        close(confd);
       }
       return 0;
    }
        
