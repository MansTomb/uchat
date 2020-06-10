#pragma once

#include <arpa/inet.h> //close
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <sys/types.h>
#include <unistd.h>

#include "libmx.h"

#define PORT 8888
#define MAX_CLIENTS 128
