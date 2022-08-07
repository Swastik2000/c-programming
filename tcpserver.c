/* TCP echo server */
// add headers 
//System header files declare the interfaces to parts of the operating system. 
//We include them in our program to supply the definitions and declarations we need to invoke system calls and libraries.
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>

// maxline is the maximum number of characters to echo 
#define MAXLINE 200
// str_echo is the function to echo the string and here it have read and write function
void str_echo(int confd)
{
    int n;
    char buffer[MAXLINE];
    while(1)
    {
        // n stores read discriptor
        while((n=read(confd, buffer, MAXLINE))>0)
        {
        
        printf("value of n=%d",n);
            // Here we write which means send the data from server to client
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

//A main is a predefined keyword or function in C. It is the first function of every C program that is responsible for starting the execution and termination of the program

int main(){

   // Declaring variables Variables

   
     // listenfd is the file descriptor for the socket
   // confd is the file descriptor for the connection
   // br stores the return value of bind system call
   int listenfd,confd,count=1,br;


     // pid is the process id of the child process and its value is 0 if the child process is not created stored in the variable
   pid_t pid;


     // socklen_t is a type definition for the length of the socket address structure
   // clilen is the length of the client address structure
   // len is the length of the server address structure
   socklen_t clilen,len;


      // sockaddr_in is the structure for the internet address and allocation of memory to struct server_addr
   // sockaddr is the structure for the socket address
   // servaddr is the structure for the server address
   // cliaddr is the structure for the client address
   struct sockaddr_in servaddr,cliaddr;

   // Store Server details in servaddr structure
    // In sin_family Storing server address family  AF_INET=IPv4
   servaddr.sin_family=AF_INET;

    // In sin_addr.s_addr storing server ip address
    // Here inaddr_any refers to any ip address computer wants
    // if you want to manually add then replace INADDR_ANY with your IP
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   
   // in sin_port storing server port number
   // Swastika is htons(0) then computer will select it automatically
   // if you want to store particular port number then use htons(port number)
   // like i want 2000 port number then it will be htons(2000)
   servaddr.sin_port=htons(0);
   
   
   // Creating a socket
    // socket is a system call that creates a new socket.
    // AF_INET is the address domain of the socket.
    // SOCK_STREAM is the type of the socket.
    // 0 is the protocol number.
    // The socket is returned in the listenfd variable.
    // If the socket creation fails, the program exits.
    
   listenfd=socket(AF_INET,SOCK_STREAM,0);
   if(listenfd>0){
         fprintf(stderr,"Socket created success\n");
   }
   else{
      fprintf(stderr,"socket creat error\n");
      return 1;
  }

  // Binding the socket to the address
    // bind() is a system call that binds the socket to the address. 
    // It assigns the address specified by addr to the socket referred to by the file  descriptor  listenfd.  
    // The socket is passed as the first argument.
    // The address is passed as the second argument.
    // The length of the address is passed as the third argument.
    // The return value is stored in the br variable.
    // return : -1 if failed 0 on success
    // If the bind fails, the program exits.

  br=bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
  if(br==0){
       printf("bind success: with return value=%d\n",br);
   }
   else{
    printf("bind UNsuccess: with return value=%d\n",br);
    printf("Retry different port\n");
    exit(2);
   }

    
    
    //len is the length of the server address structure
    len=sizeof(servaddr);



   // Listening for the connections
    // listen is a system call that listens for incoming connections.
    // The socket[listenfd] is passed as the first argument.
    // The maximum number of pending connections[ 1024 it can be anything ] is passed as the second argument.
    // description: listen() marks the socket referred to by listenfd as a passive socket, that is, as a socket that will be used to accept 
    // incoming connection requests using accept()
    // return : 0 if success and -1 if failed
    listen(listenfd,1024);
 
 
 
// for loop for accepting the connections
    
 
 
  for( ; ; )
  {     // clilen is the length of the client address structure
        clilen=sizeof(struct sockaddr_in);

        // Its printing the server port number
        printf("Waiting for client %d in port=%d\n",count,ntohs(servaddr.sin_port));


        // accept is a system call that accepts a connection on a socket.
        // The socket is passed as the first argument.
        // The address of the connecting client is passed as the second argument.
        // The length of the address is passed as the third argument.
        // The file descriptor for the new connection is returned in the confd variable.
        // If the accept fails, the program exits.
        /* description: the  accept()  system  call is used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET).  It extracts
            the first connection request on the queue of pending connections for the listening socket, listenfd, creates  a  new
            connected  socket, and returns a new file descriptor referring to that socket.  The newly created socket is not in
            the listening state.  The original socket listenfd is unaffected by this call.
        * return : non negative int (fd ) on success or -1 if failed
        */
        confd=accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

        /* * syntax of getpeername
                 * input : int sockfd : file descriptor of socket
                 *                      const char struct sockaddr *addr : pointer to variable of sockaddr type
                 *                      socklen_t : size of sockaddr
                 * description : returns  the address of the peer connected to the socket sockfd, in the buffer
                                 pointed to by addr.  The addrlen argument should be initialized to indicate
                                 the amount of space pointed to by  addr.   On return  it  contains  the actual
                                 size of the name returned (in bytes).  The name is truncated if the buffer
                                 provided is too small.
                 * return : 0 on success , -1 on failure
                 * **/
        getpeername(confd, (struct sockaddr *)&cliaddr, &clilen);
        // Printing the client address like port and ip address
        printf("Connected client details...\n");
        printf("client port=%d\n",ntohs(cliaddr.sin_port)); 
        printf("client IP=%s\n",inet_ntoa(cliaddr.sin_addr));

            // getsockname is a system call that returns the socket address of the socket.
    // description :  getsockname()  returns  the current address to which the socket listenfd is bound, in the buffer pointed to by addr.
    // The socket is passed as the first argument.
    // The address is passed as the second argument.
    // The length of the address is passed as the third argument.
    // return : 0 if success and -1 if failed

        getsockname(listenfd,(struct sockaddr *)&servaddr,&len);

         // Printing the server address like port and ip address
        printf("Server Details\n");
        printf("Sver port=%d\n",ntohs(servaddr.sin_port)); 
        printf("Server IP=%s\n",inet_ntoa(servaddr.sin_addr));
        printf("---------------------------------------------------------------\n");

        // Creating child process using fork system call
        //System call fork() is used to create processes. It takes no arguments and returns a process ID. The purpose of fork() is to create a new process, which becomes the child process of the caller. After a new child process is created, both processes will execute the next instruction following the fork() system call.
 
        pid=fork();
        if(pid==0){     //child server process
           close(listenfd);
           //d0-------------------
           str_echo(confd); // Calling the function defined above
           exit(0);
        }
        count=count+1;
        close(confd);
       }
       return 0;
    }
        
