#ifndef UDP_COMMUNICATINGSOCKET_H
#define UDP_COMMUNICATINGSOCKET_H

#include "../Socket/Socket.h"

class CommunicatingSocket : public Socket {

public:

    void connect(const std::string &foreignAddress, unsigned short foreignPort);

    void send(const void *buffer, int bufferLen);

    int recv(void *buffer, int bufferLen);

    std::string getForeignAddress();

    unsigned short getForeignPort();

protected:

    CommunicatingSocket(int type, int protocol);

    explicit CommunicatingSocket(int newConnSD);

};


#endif
