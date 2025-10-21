#include <iostream>
#include "SparseMatrix.h"
#include <ctime>
#include <cstdlib>
using namespace std;
//comando de accion g++ Main.cpp SparseMatrix.cpp -o Main.exe ; .\Main.exe
//"C:\Users\User\Documents\GitHub\Taller2\MatricesPocoPobladas"

void llenarMatrizRand(SparseMatrix &matrix, int Nelementos, int maxcoord){
    srand(time(0));
    int cont=0;
    while(cont< Nelementos){
        int fila = rand() % maxcoord;
        int col = rand() % maxcoord;
        int val = (rand() % 100) +1;
        if(matrix.get(fila,col)==0){
            matrix.add(val,fila,col);
            cont++;
        }
    }
}
double TiempoInsercion(int n, double densidad, int repeticiones){
    double contTime=0.0;
    for(int i=0; i<repeticiones;++i){
        SparseMatrix matriz;
        clock_t inicio = clock();
        llenarMatrizRand(matriz,n,densidad);
        clock_t fin = clock();
        double tiempo = double(fin - inicio)/CLOCKS_PER_SEC;
        contTime += tiempo;

    }
    return contTime/repeticiones;
}
int main() {
    srand(time(nullptr));

    int dataSets[] = {50, 250, 500, 1000, 5000};
    double densidades[] = {0.3, 0.75};
    int repeticiones =10;

    cout << "      PRUEBAS DE RENDIMIENTO     "<<endl;

    for (double densidad : densidades) {
      cout<< "Densidad: "<< densidad * 100<<"%"<<endl;
      for (int n : dataSets){
        int maxCoord = static_cast<int>(n/densidad);
        double promedio = TiempoInsercion(n,maxCoord,repeticiones);
        cout << "Numero de elementos: "<< n <<" Tiempo promedio de insercion: "<< promedio << "segundos" << endl;
      }
    }

    return 0;
}

