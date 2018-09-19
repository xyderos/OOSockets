#include "CommunicatingSocket.h"

CommunicatingSocket::CommunicatingSocket(int type, int protocol) : Socket(type, protocol) {
}

CommunicatingSocket::CommunicatingSocket(int newConnSD) : Socket(newConnSD) {
}

void CommunicatingSocket::connect(const std::string &foreignAddress, unsigned short foreignPort) {

    sockaddr_in dstAdr{};

    fillAdr(foreignAddress, foreignPort, dstAdr);

    if (::connect(sockDesc, (sockaddr *) &dstAdr, sizeof(dstAdr)) < 0)

        throw SocketException("Connect failed (connect())", true);

}

void CommunicatingSocket::send(const void *buffer, int bufferLen) {

    if (::send(sockDesc, buffer, static_cast<size_t>(bufferLen), 0) < 0)

        throw SocketException("Send failed (send())", true);

}

int CommunicatingSocket::recv(void *buffer, int bufferLen) {

    int rtn;

    if ((rtn = static_cast<int>(::recv(sockDesc, buffer, static_cast<size_t>(bufferLen), 0))) < 0)

        throw SocketException("Received failed (recv())", true);

    return rtn;
}

std::string CommunicatingSocket::getForeignAddress() {

    sockaddr_in addr{};

    unsigned int addr_len = sizeof(addr);

    if (getpeername(sockDesc, (sockaddr *) &addr,&addr_len) < 0)

        throw SocketException("Fetch of foreign address failed (getpeername())", true);

    return inet_ntoa(addr.sin_addr);
}

unsigned short CommunicatingSocket::getForeignPort() {

    sockaddr_in addr{};

    unsigned int addr_len = sizeof(addr);

    if (getpeername(sockDesc, (sockaddr *) &addr,&addr_len) < 0)

        throw SocketException("Fetch of foreign port failed (getpeername())", true);

    return static_cast<in_port_t>(inet_addr(reinterpret_cast<const char *>(addr.sin_port)));
}
