#pragma once

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
#include <gtk/gtk.h>

#include "client.h"

#define BACKIMAGE_PATH "./Resources/images/back.jpg"
#define PORT 8888
#define WIDTH 1280
#define HEIGHT 720
