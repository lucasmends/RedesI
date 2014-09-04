#include <iostream>
#include "Matriz.h"

#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> /*for socket(), connect(), send() and recv()*/
#include <arpa/inet.h>
#include <unistd.h> /* for close() */
#include <netinet/in.h> /* for IP Socket data types */
#include <sys/types.h>
#include <cerrno>

#define NRCON 5
#define BUFFSIZE 64
#define PORTA 5006

using namespace std;

int main()
{

	int ssocket, csocket;
	struct sockaddr_in end_servidor;
	struct sockaddr_in end_cliente;
	int l, c;
	float valor;
	char op[1];

	if ((ssocket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Erro criação socket");
		exit(-1);
	}

	/* Construct the server sockaddr_in structure */
	memset(&end_servidor, 0, sizeof(end_servidor)); /* Clear struct */
	end_servidor.sin_family = AF_INET; /* Internet/IP */
	end_servidor.sin_addr.s_addr = htonl(INADDR_ANY); /* Incoming addr */
//	end_servidor.sin_port = htons("5001"); /* server port */
	end_servidor.sin_port = htons(PORTA); /* server port */
	/* Bind the server socket */
	if (bind(ssocket, (struct sockaddr *) &end_servidor, sizeof(end_servidor)) < 0) {
		perror("erro bind");
		exit(-1);
	}

	/* Listen on the server socket */
	if (listen(ssocket, NRCON) < 0) {
		perror("erro listen");
		exit(-1);
	}

	while (1) {
		unsigned int clientlen = sizeof(end_cliente);
		/* wait for client connection */
		/* the accept() system call causes the process to block until a client connects to the server*/
		csocket = accept(ssocket, (struct sockaddr *) &end_cliente, &clientlen);
		if(csocket < 0){
			cout << "error accept";
			return -1;
		}

        cout << "Cliente conectado" << endl;

		recv(csocket, &l, sizeof(l),0);
		recv(csocket, &c, sizeof(c),0);

        int d, d2;
        d = ntohs(l);
        d2 = ntohs(c);
        cout << d << " " << d2 << " " << endl;
		Matriz m1(d, d2);
		Matriz m2(d, d2);
        Matriz resposta(d, d2);

		for(int i = 0; i < m1.getL(); i++){
			for(int j = 0; j < m1.getC(); j++){
				recv(csocket, &valor, sizeof(valor),0);
				cout << ntohs(valor) << " " << endl;
				m1.matriz[i][j] = ntohs(valor);
			}
		}

        m1.mostrar();

        recv(csocket, &op, sizeof(op),0);

        cout << op[0] << endl;

        if(op[0] == 't')
        {
            resposta = m1.transposta();
			for(int i = 0; i < resposta.getL(); i++){
				for(int j = 0; j < resposta.getC(); j++){
					valor = htons(resposta.matriz[i][j]);
					send(csocket, &valor, sizeof(valor),0);
				}
			}
        }
        else{
            for(int i = 0; i < m2.getL(); i++){
                for(int j = 0; j < m2.getC(); j++){
                    recv(csocket, &valor, sizeof(valor),0);
                    cout << ntohs(valor) << " " << endl;
                    m2.matriz[i][j] = ntohs(valor);
                }
            }

            switch(op[0]){
                case '+':
                    resposta = m1 + m2;
                    for(int i = 0; i < resposta.getL(); i++){
                        for(int j = 0; j < resposta.getC(); j++){
                            valor = htons(resposta.matriz[i][j]);
                            send(csocket, &valor, sizeof(valor),0);
                        }
                    }
                    break;
                case '-':
                    resposta = m1 - m2;
                    for(int i = 0; i < resposta.getL(); i++){
                        for(int j = 0; j < resposta.getC(); j++){
                            valor = htons(resposta.matriz[i][j]);
                            send(csocket, &valor, sizeof(valor),0);
                        }
                    }
                    break;
                case '*':
                    resposta = m1*m2;
                    for(int i = 0; i < resposta.getL(); i++){
                        for(int j = 0; j < resposta.getC(); j++){
                            valor = htons(resposta.matriz[i][j]);
                            send(csocket, &valor, sizeof(valor),0);
                        }
                    }
                    break;
                default:
                    int n = write(csocket, "Operacao inválida", 50);
                    if(n<0){
                        cout << "Erro escrevendo no socket" << endl;
                        return -1;
                    }
                }
        }
	}
	close(ssocket);

    std::cin.get();
    return 0;
}
