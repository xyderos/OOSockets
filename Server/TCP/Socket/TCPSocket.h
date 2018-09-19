#ifndef UDP_TCPSOCKET_H
#define UDP_TCPSOCKET_H

#include "../../Socket/CommSocket/CommunicatingSocket.h"

class TCPSocket : public CommunicatingSocket {

public:

    TCPSocket();

    TCPSocket(const std::string &foreignAddress, unsigned short foreignPort);

private:

    friend class TCPServerSocket;

    explicit TCPSocket(int newConnSD);
};


#endif
