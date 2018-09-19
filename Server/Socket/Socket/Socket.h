#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include "../../Exception/SocketException.h"
#include "../../Helpers/Helpers.h"
#include <netinet/in.h>
#include <netdb.h>

class Socket {

public:

    ~Socket();

    std::string getLocalAddress();

    unsigned short getLocalPort();

    void setLocalPort(unsigned short localPort);

    void setLocalAddressAndPort(const std::string &localAddress, unsigned short localPort = 0);

    static unsigned short resolveService(const std::string &service, const std::string &protocol = "tcp");

private:

    Socket(const Socket &sock);

    void operator=(const Socket &sock);

protected:

    int sockDesc;

    Socket(int type, int protocol);

    explicit Socket(int sockDesc);

};


#endif
