#include "UDPSocket.h"

UDPSocket::UDPSocket(): CommunicatingSocket(SOCK_DGRAM, IPPROTO_UDP) {
    setBroadcast();
}

UDPSocket::UDPSocket(unsigned short localPort) : CommunicatingSocket(SOCK_DGRAM, IPPROTO_UDP) {

    setLocalPort(localPort);

    setBroadcast();
}

UDPSocket::UDPSocket(const std::string &localAddress, unsigned short localPort)
        : CommunicatingSocket(SOCK_DGRAM, IPPROTO_UDP) {

    setLocalAddressAndPort(localAddress, localPort);

    setBroadcast();
}

void UDPSocket::setBroadcast() {

    int broadcastPermission = 1;

    setsockopt(sockDesc, SOL_SOCKET, SO_BROADCAST, &broadcastPermission, sizeof(broadcastPermission));
}

void UDPSocket::disconnect() {

    sockaddr_in nullAddr{};

    memset(&nullAddr, 0, sizeof(nullAddr));

    nullAddr.sin_family = AF_UNSPEC;


    if (::connect(sockDesc, (sockaddr *) &nullAddr, sizeof(nullAddr)) < 0)

        if (errno != EAFNOSUPPORT)

            throw SocketException("Disconnect failed (connect())", true);
}

void UDPSocket::sendTo(const void *buffer, int bufferLen, const std::string &foreignAddress, unsigned short foreignPort) {

    sockaddr_in destAddr{};

    fillAdr(foreignAddress, foreignPort, destAddr);

    if (sendto(sockDesc, buffer, static_cast<size_t>(bufferLen), 0, (sockaddr *) &destAddr, sizeof(destAddr)) != bufferLen)

        throw SocketException("Send failed (sendto())", true);
}

int UDPSocket::recvFrom(void *buffer, int bufferLen, std::string &sourceAddress, unsigned short &sourcePort) {

    sockaddr_in clAdr{};

    socklen_t addrLen = sizeof(clAdr);

    int rtn;

    if ((rtn = static_cast<int>(recvfrom(sockDesc, buffer, static_cast<size_t>(bufferLen), 0, (sockaddr *) &clAdr, &addrLen))) < 0)

        throw SocketException("Receive failed (recvfrom())", true);

    sourceAddress = inet_ntoa(clAdr.sin_addr);

    sourcePort = ntohs(clAdr.sin_port);

    return rtn;
}

void UDPSocket::setMulticastTTL(unsigned char mcTTL) {

    if (setsockopt(sockDesc, IPPROTO_IP, IP_MULTICAST_TTL, &mcTTL, sizeof(mcTTL)) < 0)

        throw SocketException("Multicast TTL set failed (setsockopt())", true);
}

void UDPSocket::joinGroup(const std::string &mcGroup) {

    struct ip_mreq mcReq{};

    mcReq.imr_multiaddr.s_addr = inet_addr(mcGroup.c_str());

    mcReq.imr_interface.s_addr =inet_addr(INADDR_ANY);

    if (setsockopt(sockDesc, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mcReq, sizeof(mcReq)) < 0)

        throw SocketException("Multicast group join failed (setsockopt())", true);
}

void UDPSocket::leaveGroup(const std::string &mcGroup) {

    struct ip_mreq mcReq{};

    mcReq.imr_multiaddr.s_addr = inet_addr(mcGroup.c_str());

    mcReq.imr_interface.s_addr =inet_addr(INADDR_ANY);

    if (setsockopt(sockDesc, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mcReq, sizeof(mcReq)) < 0)

        throw SocketException("Multicast group leave failed (setsockopt())", true);
}