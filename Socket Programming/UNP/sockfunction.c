#include<sys/types.h>
#include<sys/socket.h>
int socket(int family,int tyoe,int protocol);


//.........connect function...................
#inclue<sys/types.h>
#inclue<sys/socket.h>
int connect(int sockfd,struct sockaddr *serv_addr,int adrlen);

//.........bind function.....................
#include<sys/types.h>
#include<sys/socket.h>
int bind(int sockfd,struct sockaddr *my_addr,int adrlen);                                              
server.sin_port=o;
server.sin_addr.s_adde=INADDR_ANY;
//.........listen function........
#include<sys/types.h>
#include<sys/socket.h>
int listen(int sockfd,int backlog);

//..........accept function..........
#include<sys/types.h>
#include<sys/socket.h>
int accept(int sockfd,struct sockaddr *cliaddr,socklen_t *addrlen);

//.......... send function..........
#include<sys/types.h>
#include<sys/socket.h>
int send(int sockfd,const void *msg,int len, int flag)

// ..........recv function.........
#include<sys/types.h>
#include<sys/socket.h>
int recv(int sockfd,coid *buf, int len,unsigned int flags);

//..........sendto function.........
#include<sys/types.h>
#include<sys/socket.h>
int sendto(int sockfd, const void *msg, int len,unsigned int flags, const struct sockaddr *to, int tolen);

//..........recvfrom function..........
#include<sys/types.h>
#include<sys/socket.h>
int recvfrom(int sockfd,void *buf,int len,unsigned int flages,struct sockaddr *from,int fromlen);

//.....close function........
#include<sys/types.h>
#include<sys/socket.h>
int close(int sockfd);

//...........shutdown function.........
#include<sys/types.h>
#include<sys/socket.h>
int shutdowmn(int sockfd,int how);



