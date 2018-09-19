#ifndef UDP_UDPSOCKET_H
#define UDP_UDPSOCKET_H

#include "../../Socket/CommSocket/CommunicatingSocket.h"

class UDPSocket : public CommunicatingSocket {

public:

    UDPSocket();

    explicit UDPSocket(unsigned short localPort);

    UDPSocket(const std::string &localAddress, unsigned short localPort);

    void disconnect();

    void sendTo(const void *buffer, int bufferLen, const std::string &foreignAddress, unsigned short foreignPort);

    int recvFrom(void *buffer, int bufferLen, std::string &sourceAddress, unsigned short &sourcePort);

    void setMulticastTTL(unsigned char mcTTL);

    void joinGroup(const std::string &mcGroup);

    void leaveGroup(const std::string &mcGroup);

private:

    void setBroadcast();

};


#endif
