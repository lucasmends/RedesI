#include <iostream>
#ifndef MATRIZ_H
#define MATRIZ_H

class Matriz
{
    public:
        float **matriz;

        Matriz(const int &A,const int &B){
            this->L = A;
            this->C = B;
            matriz = new float*[L];
            for(int i = 0; i < L; i++){
                matriz[i] = new float[C];
            }
        }

        ~Matriz(){
            delete matriz;
        }

        Matriz operator+(const Matriz&);
        Matriz operator-(const Matriz&);
        Matriz& operator=(const Matriz&);
        Matriz const transposta();

        Matriz operator*(const Matriz&);

        void mostrar(){
            for(int i = 0; i < L; i++){
                for(int j = 0; j < C; j++){
                    std::cout << matriz[i][j] << " ";
                }
                std::cout << "\n";
            }
        }

        int getL(){
            return L;
        }

        int getC(){
            return C;
        }
    private:
        int L;
        int C;

};

#endif // MATRIZ_H
