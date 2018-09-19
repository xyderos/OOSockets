#ifndef UDP_TCPSERVERSOCKET_H
#define UDP_TCPSERVERSOCKET_H

#include "../Socket/TCPSocket.h"

class TCPServerSocket : public Socket {

public:

    explicit TCPServerSocket(unsigned short localPort, int queueLen = 5);

    TCPServerSocket(const std::string &localAddress, unsigned short localPort, int queueLen = 5);

    TCPSocket *accept();

private:

    void setListen(int queueLen);
};


#endif
