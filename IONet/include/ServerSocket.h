#ifndef SERVERSOCKET_H

#include "Socket.h"
#include <sys/socket.h>
#include <unistd.h> /* for close() */
#include <netinet/in.h>
#include <cstring>
#define SERVERSOCKET_H

#define NRCON 5

class ServerSocket
{
    public:
        ServerSocket(const unsigned int &port){
            if ((ssocket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
                    throw "Error creating socket";
                }
            memset(&end_servidor, 0, sizeof(end_servidor)); /* Clear struct */
            end_servidor.sin_family = AF_INET; /* Internet/IP */
            end_servidor.sin_addr.s_addr = htonl(INADDR_ANY); /* Incoming addr */
        //	end_servidor.sin_port = htons("5001"); /* server port */
            end_servidor.sin_port = htons(port); /* server port */
            /* Bind the server socket */
            if (bind(ssocket, (struct sockaddr *) &end_servidor, sizeof(end_servidor)) < 0) {
                throw "Error binding";
            }
            if (listen(ssocket, NRCON) < 0) {
                throw "Error listening";
            }
        }

        ~ServerSocket(){
            this->close();
        }

        Socket accept();
        Socket* acceptP();

        void close(){
            ::close(ssocket);
            memset(&end_servidor, 0, sizeof(end_servidor));
        }
    private:
        int ssocket;
        struct sockaddr_in end_servidor;
};

#endif // SERVERSOCKET_H
