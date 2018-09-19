#include "SocketException.h"

SocketException::SocketException(std::string message, bool inclSysMsg) : msg(std::move(message)) {

    if (inclSysMsg) {

        this->msg.append(": ");

        this->msg.append(strerror(errno));

    }
}

SocketException::~SocketException() = default;

const char *SocketException::what() const _NOEXCEPT {
    return this->msg.c_str();
}
