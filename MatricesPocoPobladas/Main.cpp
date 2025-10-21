#include <iostream>
#include "SparseMatrix.h"
#include <chrono>
#include <ctime>
#include <cstdlib>
using namespace std;
//comando de accion g++ Main.cpp SparseMatrix.cpp -o Main.exe ; .\Main.exe
void llenarMatrizRand(SparseMatrix &matrix, int Nelementos, double densidad){
    int total = Nelementos * Nelementos;
    int elementos = static_cast<int>(total * densidad);
    for(int i=0; i<elementos;++i){
        int fila = rand() % Nelementos;
        int col = rand() % Nelementos;
        int valor = rand() % 100 +1;
        while (matrix.get(fila, col) != 0) {
            fila = rand() % Nelementos;
            col  = rand() % Nelementos;
        }
        matrix.add(valor, fila, col);

    }      
}
double TiempoInsercion(int n, double densidad, int repeticiones){
    double contTime=0;
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

    cout << "      PRUEBAS DE RENDIMIENTO     \n";

    for (double densidad : densidades) {
      cout<< "Densidad "<< densidad * 100<<"%"<<endl;
      for (int n : dataSets){
        double promedio = TiempoInsercion(n,densidad,repeticiones);
        cout << "Tamano" << n << "x"<< n <<"Tiempo promedio de insercion: "<<promedio <<endl;
      }
    }

    cout << " Todas las pruebas finalizadas."<<endl;
    return 0;
}

