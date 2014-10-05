#ifndef SOCKET_H
#define SOCKET_H

#include <unistd.h> /* for close() */
#include "NetUtils.h"

class Socket
{
    public:
        Socket(const struct sockaddr_in &end_socket, const int &socket): end_socket(end_socket), socket(socket)
        { }


        int getSocket() const{
            return socket;
        }
    private:
        struct sockaddr_in end_socket;
        int socket;
};

#endif // SOCKET_H
