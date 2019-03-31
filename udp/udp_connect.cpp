//
// Created by lance on 2019-03-31.
//

#include <sys/socket.h>
#include <sys/event.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "udp_connect.h"
#include "uLog.h"


//12 #define exit_if(r, ...) if(r) {printf(__VA_ARGS__); printf("error no: %d error msg %s\n", errno, strerror(errno)); exit(1);}

int setNonBlock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if(flags<0) {
        LER("setNonBlock fcntl flags:%d  ei:%s",flags,strerror(errno));
        return flags;
    }
    //exit_if(flags<0, "fcntl failed");
    int r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    LIE(r>=0,"setNonBlock fcntl ec:%d/%s",r,strerror(errno));

    return r;
    //exit_if(r<0, "fcntl failed");
}


