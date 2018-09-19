#include "TCPSocket.h"

TCPSocket::TCPSocket() : CommunicatingSocket(SOCK_STREAM, IPPROTO_TCP) {}

TCPSocket::TCPSocket(const std::string &foreignAddress, unsigned short foreignPort)
        : CommunicatingSocket(SOCK_STREAM, IPPROTO_TCP) {

    connect(foreignAddress, foreignPort);
}

TCPSocket::TCPSocket(int newConnSD) : CommunicatingSocket(newConnSD) {}