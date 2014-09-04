#include "Socket.h"
#include "Matriz.h"

void Socket::executar()
{
	int l, c;
	float valor;
	char op[1];
	while (1) {
		unsigned int clientlen = sizeof(this->end_client);
		/* wait for client connection */
		/* the accept() system call causes the process to block until a client connects to the server*/
		csocket = accept(ssocket, (struct sockaddr *) &end_client, &clientlen);
		if(csocket < 0){
			error("error accept");
		}


		recv(csocket, &l, sizeof(l),0);
		recv(csocket, &c, sizeof(c),0);

		Matriz m1(l, c);
		Matriz m2(l, c);

		for(int i = 0; i <;i++){
			for(j=0;j<matriz1.size[1];j++){
				recv(csocket, &temp2, sizeof(temp2),0);
				matriz1.m[i][j] = ntohs(temp2);
			}
		}


		n = write(csocket, "Digite uma operacao: ", 50);
		if(n<0){
			error("ERROR writing to socket");
		}

		recv(csocket, &op, sizeof(op),0);

		//printf("%c\n", op[0]);


		if(op[0]=='+'){
			n = write(csocket, "Insira a matriz a somar: ", 50);
			if(n<0){
				error("ERROR writing to socket");
			}

			matriz2.size[0] = matriz1.size[0];
			matriz2.size[1] = matriz1.size[1];
			matriz2.m = malloc(matriz1.size[0]*sizeof(float *));

			for(i=0;i<matriz2.size[0];i++){
				matriz2.m[i] = malloc(matriz2.size[1]*sizeof(float));
			}

			for(i=0;i<matriz2.size[0];i++){
				for(j=0;j<matriz2.size[1];j++){
					recv(csocket, &temp2, sizeof(temp2),0);
					matriz2.m[i][j] = ntohs(temp2);
				}
			}

			n = write(csocket, "Matriz resultante: \n", 50);
			if(n<0){
				error("ERROR writing to socket");
			}
			printf("oi!");
			for(i=0;i<matriz2.size[0];i++){
				for(j=0;j<matriz2.size[1];j++){
					resultMatrix = sum_matrix(matriz1, matriz2);
					temp2 = htons(resultMatrix[i][j]);
					send(csocket, &temp2, sizeof(temp2),0);
				}
			}
			//deallocate matriz 1, matriz 2 and matriz result
		}

		else if(op[0]=='-'){
			n = write(csocket, "Insira a matriz a subtrair: ", 50);
			if(n<0){
				error("ERROR writing to socket");
			}

			matriz2.size[0] = matriz1.size[0];
			matriz2.size[1] = matriz1.size[1];
			matriz2.m = malloc(matriz1.size[0]*sizeof(float *));

			for(i=0;i<matriz2.size[0];i++){
				matriz2.m[i] = malloc(matriz2.size[1]*sizeof(float));
			}

			for(i=0;i<matriz2.size[0];i++){
				for(j=0;j<matriz2.size[1];j++){
					recv(csocket, &temp2, sizeof(temp2),0);
					matriz2.m[i][j] = ntohs(temp2);
				}
			}

			n = write(csocket, "Matriz resultante: \n", 50);
			if(n<0){
				error("ERROR writing to socket");
			}
			printf("oi!");
			for(i=0;i<matriz2.size[0];i++){
				for(j=0;j<matriz2.size[1];j++){
					resultMatrix = sub_matrix(matriz1, matriz2);
					temp2 = htons(resultMatrix[i][j]);
					send(csocket, &temp2, sizeof(temp2),0);
				}
			}

			//deallocate matriz 1, matriz 2 and matriz result
		}
	}

	close(ssocket);
}
