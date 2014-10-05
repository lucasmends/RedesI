#ifndef INSTREAM_H
#define INSTREAM_H

#include "Socket.h"
#include <string>

class InStream
{
    public:
        InStream(Socket *socket):stream(socket){}
        ~InStream();

        short readShort() const;
        int readInt() const;
        unsigned readUns() const;
        char readChar() const;
        std::string* readString() const;

    private:
        Socket *stream;
};

#endif // INSTREAM_H
