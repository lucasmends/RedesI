#include "ServerSocket.h"
#include "Socket.h"
#include "NetUtils.h"
#include <sys/socket.h> /*for socket(), connect(), send() and recv()*/

Socket ServerSocket::accept()
{
    struct sockaddr_in end_cliente;
    unsigned int clientlen = sizeof(end_cliente);
    int csocket;

    csocket = ::accept(ssocket, (struct sockaddr *) &end_cliente, &clientlen);
	if(csocket < 0){
		throw "Error accepting";
	}


    Socket client(end_cliente, csocket);
	return client;
}

Socket* ServerSocket::acceptP()
{
    struct sockaddr_in end_cliente;
    unsigned int clientlen = sizeof(end_cliente);
    int csocket;

    csocket = ::accept(ssocket, (struct sockaddr *) &end_cliente, &clientlen);
	if(csocket < 0){
		throw "Error accepting";
	}


    Socket *client = new Socket(end_cliente, csocket);
	return client;
}
