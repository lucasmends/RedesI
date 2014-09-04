#include <iostream>
#include <stdio.h>
#include <sys/socket.h> /*for socket(), connect(), send() and recv()*/
#include <arpa/inet.h> /*for sockaddr_in and inet_addr()*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /*for close()*/
#include <netinet/in.h> /*for IP Socket data types*/
#include <string>

#define BUFFSIZE 64


using namespace std;

int main(int argc, char const *argv[])
{
	int csocket, n;
	struct sockaddr_in end_server;
	char buffer[BUFFSIZE];

	char op[1];

	if(argc != 3){
		cout << "Utilize: ./Programa <ip> <porta> " << endl;
		return -1;
	}

	csocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(csocket < 0){
        cout << "ERROR, no such host" << endl;
		return -2;
	}

	/* Construct the server sockaddr_in structure */
	memset(&end_server, 0, sizeof(end_server));
	end_server.sin_family = AF_INET;
	end_server.sin_addr.s_addr = inet_addr(argv[1]);
	end_server.sin_port = htons(atoi(argv[2]));

	/* Establish connection */
	if (connect(csocket, (struct sockaddr *) &end_server, sizeof(end_server)) < 0) {
        cout << "erro no conect" << endl;
		return -3;
	}

    int dim, dim2;
    float elemento;
    int enviar;
    cout << "Qual a dimensao da sua matriz?" << endl;
    cin >> dim >> dim2;

    enviar = htons(dim);
    send(csocket, &enviar, sizeof(enviar),0);
    enviar = htons(dim2);
    send(csocket, &enviar, sizeof(enviar),0);

	cout << "Quais sao os elementos da sua matriz?" << endl;
	for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim2; j++){
            cout << "M1[" << i + 1 << "][" << j + 1 << "] :";
            cin >> elemento;
            elemento = htons(elemento);
            send(csocket, &elemento, sizeof(elemento), 0);
        }
	}

    cout << "Operacao: ";
    cin >> op[0];

	send(csocket, &op, sizeof(op),0);

    float exibir;

    if(op[0] == 't'){

        cout << "Resposta" << endl;

		for(int i = 0; i < dim; i++){
			for(int j = 0; j < dim2; j++){
				recv(csocket, &elemento, sizeof(elemento), 0);
				exibir = ntohs(elemento);
				cout << exibir << " ";
			}
			cout << endl;
        }
    }
    else{
 	cout << "Quais sao os elementos da outra matriz?" << endl;
        for(int i = 0; i < dim; i++){
            for(int j = 0; j < dim2; j++){
                cout << "M2[" << i + 1 << "][" << j + 1 << "] :";
                cin >> elemento;
                elemento = htons(elemento);
                send(csocket, &elemento, sizeof(elemento), 0);
            }
        }

        cout << "Resposta" << endl;

		for(int i = 0; i < dim; i++){
			for(int j = 0; j < dim2; j++){
				recv(csocket, &elemento, sizeof(elemento), 0);
				exibir = ntohs(elemento);
				cout << exibir << " ";
			}
			cout << endl;
        }

    }

    return 0;
}
