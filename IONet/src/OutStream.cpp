#include "OutStream.h"

#include <sys/socket.h>
#include "Socket.h"


void OutStream::send(const short &num) const{

    ::send(stream->getSocket(), (const void *) htons(num), sizeof(short),0);
}

void OutStream::send(const int &num) const{
    ::send(stream->getSocket(), (const void *) htonl(num), sizeof(int),0);
}

void OutStream::send(const unsigned &num) const{
    ::send(stream->getSocket(), (const void *) htonl(num), sizeof(int),0);
}

void OutStream::send(const char &cha) const{

    ::send(stream->getSocket(), (const void *) cha, sizeof(char),0);
}

void OutStream::sendChars(const std::string &str) const{

    for(int i = 0; i < str.length(); i++)
        this->send(str[i]);
}

void OutStream::send(const std::string &str) const{

    this->send(int(str.length()));
    for(size_t i = 0; i < str.length(); i++)
        this->send(str[i]);
}
