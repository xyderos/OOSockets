#ifndef UDP_SHOCKETEXCEPTION_H
#define UDP_SHOCKETEXCEPTION_H

#include <exception>
#include <string>
#include <cerrno>


class SocketException : public std::exception {

private:

    std::string msg;

public:

    explicit SocketException(std::string message, bool inclSysMsg=false);

    ~SocketException()override ;

    const char *what() const _NOEXCEPT override ;

};


#endif
