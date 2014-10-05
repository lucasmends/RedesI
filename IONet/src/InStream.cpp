#include "InStream.h"

InStream::~InStream()
{
    //dtor
}

short InStream::readShort() const
{
    short intNet;

    recv(stream->getSocket(), &intNet, sizeof(short),0);

    return ntohs(intNet);
}

int InStream::readInt() const
{
    int intNet;

    recv(stream->getSocket(), &intNet, sizeof(int),0);

    return ntohl(intNet);
}

unsigned InStream::readUns() const
{
    unsigned intNet;

    recv(stream->getSocket(), &intNet, sizeof(unsigned),0);

    return ntohl(intNet);
}

char InStream::readChar() const
{
    char charNet;

    recv(stream->getSocket(), &charNet, sizeof(char),0);

    return charNet;
}

std::string* InStream::readString() const{
    std::string *str = new std::string();

    size_t length = this->readUns();

    for(size_t i = 0; i < length; i++)
        str->append((const char*)this->readChar());

    return str;
}
