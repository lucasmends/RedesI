#ifndef SOCKET_H
#define SOCKET_H

#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> /*for socket(), connect(), send() and recv()*/
#include <arpa/inet.h>
#include <unistd.h> /* for close() */
#include <netinet/in.h> /* for IP Socket data types */
#include <sys/types.h>
#include<errno.h>

#define NRCON 5
#define BUFFSIZE 32
#define PORTA 5001

using namespace std;

class Socket
{
    public:
        Socket(){

    }
        ~Socket();

        void executar();
    private:
    	int ssocket;
    	int csocket;
        struct sockaddr_in end_servidor;
        struct end_cliente;
};

#endif // SOCKET_H
