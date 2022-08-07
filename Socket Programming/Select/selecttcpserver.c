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
#include<wait.h>
#include<sys/select.h>
#define MAXLINE 200
#define SERVPORT 33456

//#define FD_SETSIZE 256



void handel_fun(int sig)
{
    printf("SIGCHLD signal is generated ... \n");
    int stat;
    
    //pid_t pid = wait(&stat);
    pid_t pid;
    
    while((pid = waitpid(-1,&stat,WNOHANG))>0){
        printf("Child server terminated with [pid = %ld and statloc = %d]\n",(long)pid,stat);
   }
    
}
int main(){
  signal(SIGCHLD, handel_fun);
    int client[FD_SETSIZE];
   int listenfd,confd,sockfd,maxi,maxfd,nready,count=1,br,i,n;
   fd_set allset,rset;
     char buff[MAXLINE];
   
   pid_t pid;
   socklen_t clilen,len;
   struct sockaddr_in servaddr,cliaddr;
   len=sizeof(servaddr);
   servaddr.sin_family=AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(SERVPORT);
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
   
   
  //getsockname(listenfd,(struct sockaddr *)&servaddr,&len);
  listen(listenfd,1024);
  maxfd=listenfd;
  maxi =-1;
  for(i=0;i<FD_SETSIZE; i++)
  client[i]=-1;
  FD_ZERO(&allset);
  FD_SET(listenfd, &allset);
  
  for( ; ; ){
  rset=allset;
  nready=select(maxfd+1, &rset, NULL,NULL,NULL);
  
  if(FD_ISSET(listenfd, &rset)){
  clilen=sizeof(cliaddr);
  confd=accept(listenfd,(struct sockaddr *) & cliaddr, &clilen);
  
  for(i=0;i<FD_SETSIZE; i++)
  {
  if(client[i]<0)
  {client[i]=confd;
  break;}
  }
  if(i==FD_SETSIZE)
    perror("too many client");
  
  FD_SET(confd, &allset);
  if(confd>maxfd)
  maxfd=confd;
  if(i>maxi)
  maxi=i;
  if(--nready<=0)
  continue;
  
  }
  
 for( i=0;i<=maxi ;i++ ){
 
 if(sockfd=client[i]<0)
    continue;
   if(FD_ISSET(sockfd, &rset)){
   if((n=read(sockfd,buff,MAXLINE)==0))
   {
   close(sockfd);
   FD_CLR(sockfd, &allset);
   client[i]=-1;
      }
      else
      write(sockfd, buff, n);
      
      if(--nready<=0)
        break;
  }
  
  }   
       }
       return 0;
    }
        
