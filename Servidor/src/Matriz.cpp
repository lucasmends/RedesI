#include <iostream>
#include "Matriz.h"

Matriz Matriz::operator+(const Matriz &dir){
    if(this->L != dir.L || this->C != dir.C){
        throw "Matrizes de dimensoes diferentes";
    }
    Matriz resposta(this->L, this->C);
    for(int i = 0; i < dir.L; i++){
        for(int j = 0; j < dir.C; j++){
            resposta.matriz[i][j] = dir.matriz[i][j] + this->matriz[i][j];
        }
    }
    return resposta;
}

Matriz Matriz::operator-(const Matriz &dir){
    if(this->L != dir.L || this->C != dir.C){
        throw "Matrizes de dimensoes diferentes";
    }
    Matriz resposta(dir.L, dir.C);
    for(int i = 0; i < dir.L; i++){
        for(int j = 0; j < dir.C; j++){
            resposta.matriz[i][j] = this->matriz[i][j] -dir.matriz[i][j];
        }
    }
    return resposta;
}

Matriz& Matriz::operator=(const Matriz &dir){
    if(this->L != dir.L || this->C != dir.C){
        throw "Matrizes de dimensoes diferentes";
    }
    for(int i = 0; i < dir.L; i++){
        for(int j = 0; j < dir.C; j++){
            this->matriz[i][j] = dir.matriz[i][j];
        }
    }

    return *this;
}

Matriz const Matriz::transposta(){
    Matriz resposta(this->C, this->L);
    for(int i = 0; i < this->L; i++){
        for(int j = 0; j < this->C; j++){
            resposta.matriz[j][i] = this->matriz[i][j];
        }
    }

    return resposta;
}

Matriz Matriz::operator*(const Matriz &dir){
    if( this->C != dir.L){
        throw "Matriz nao podem ser multiĺicadas";
    }
    Matriz resposta(this->L, dir.C);
    float soma = 0.0;
    for(int i = 0; i < this->L; i++){
        for(int j = 0; j < dir.C; j++){
            for(int k = 0; k < this->C; k++){
                soma += this->matriz[i][k]*dir.matriz[j][k];
            }
        resposta.matriz[i][j] = soma;
        soma = 0.0;
        }
    }
    return resposta;
}
