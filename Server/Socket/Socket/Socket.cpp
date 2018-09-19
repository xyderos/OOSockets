#include "Socket.h"

Socket::Socket(int type, int protocol) {

    if ((sockDesc = socket(PF_INET, type, protocol)) < 0)

        throw SocketException("Socket creation failed (socket())", true);
}

Socket::Socket(int sockDesc) {
    this->sockDesc = sockDesc;
}

Socket::~Socket() {

    close(sockDesc);

    sockDesc = -1;
}

std::string Socket::getLocalAddress() {

    sockaddr_in addr{};

    auto addr_len = static_cast<socklen_t >(sizeof(addr));

    if (getsockname(sockDesc, (sockaddr *) &addr, &addr_len) < 0)

        throw SocketException("Fetch of local address failed (getsockname())", true);

    return inet_ntoa(addr.sin_addr);
}

unsigned short Socket::getLocalPort() {

    sockaddr_in addr{};

    auto addr_len = static_cast<socklen_t >(sizeof(addr));

    if (getsockname(sockDesc, (sockaddr *) &addr, &addr_len) < 0)

        throw SocketException("Fetch of local port failed (getsockname())", true);

    return static_cast<in_port_t>(inet_addr(reinterpret_cast<const char *>(addr.sin_port)));
}

void Socket::setLocalPort(unsigned short localPort) {

    sockaddr_in localAddr{};

    memset(&localAddr, 0, sizeof(localAddr));

    localAddr.sin_family = AF_INET;

    localAddr.sin_addr.s_addr =inet_addr(INADDR_ANY);

    localAddr.sin_port = static_cast<in_port_t>(inet_addr(reinterpret_cast<const char *>(localPort)));

    if (bind(sockDesc, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0)

        throw SocketException("Set of local port failed (bind())", true);
}

void Socket::setLocalAddressAndPort(const std::string &localAddress, unsigned short localPort) {

    sockaddr_in localAddr{};

    fillAdr(localAddress, localPort, localAddr);

    if (bind(sockDesc, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0)

        throw SocketException("Set of local address and port failed (bind())", true);
}

unsigned short Socket::resolveService(const std::string &service, const std::string &protocol) {

    struct servent *srv;

    return (srv = getservbyname(service.c_str(), protocol.c_str())) == nullptr

           ? static_cast<unsigned short>((int)strtol(service.c_str(), (char **)nullptr, 10)) :

           static_cast<in_port_t>(inet_addr(reinterpret_cast<const char *>(srv->s_port)));
}

