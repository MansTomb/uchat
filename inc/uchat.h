#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <errno.h>  
#include <arpa/inet.h>    //close  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros  
#include <sys/socketvar.h>
#include <arpa/inet.h>

#define TRUE 1
#define FALSE 0
#define PORT 8888
