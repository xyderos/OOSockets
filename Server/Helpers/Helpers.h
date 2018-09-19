#ifndef UDP_HELPERS_H
#define UDP_HELPERS_H

#include <pthread.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <zconf.h>
#include <iostream>
#include <cstdlib>
#include "../Exception/SocketException.h"

#ifndef _BSZ
#define _BSZ 32
#endif

void fillAdr(const std::string &address, unsigned short port, sockaddr_in &addr) {

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;

    hostent *host;

    if ((host = gethostbyname(address.c_str())) ==nullptr )
        throw SocketException("Failed to resolve name (gethostbyname())");

    addr.sin_addr.s_addr = static_cast<in_addr_t>(*((unsigned long *) host->h_addr_list[0]));

    addr.sin_port =static_cast<in_port_t>(inet_addr(reinterpret_cast<const char *>(port)));
}

#endif
