#ifndef OUTSTREAM_H
#define OUTSTREAM_H
#include "Socket.h"

#include <string>

class OutStream
{
    public:
        OutStream(Socket *socket):stream(socket){}
        ~OutStream();

        void send(const short &) const;
        void send(const int &) const;
        void send(const unsigned &) const;
        void send(const char &) const;
        void sendChars(const std::string &) const;
        void send(const std::string &) const;

    private:
        Socket *stream;
};

#endif // OUTSTREAM_H
