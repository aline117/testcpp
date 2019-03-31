//
// Created by lance on 2019-03-31.
//

#ifndef CPPTEST_UDP_CONNECT_H
#define CPPTEST_UDP_CONNECT_H


#define BUFSZ  1024
#define PORT   8000

enum {
    kReadEvent = 1,
    kWriteEvent = 2
};

extern int setNonBlock(int fd);

#endif //CPPTEST_UDP_CONNECT_H
