#include <iostream>
#include "SparseMatrix.h"
#include <ctime>
#include <cstdlib>
using namespace std;
//comando de accion g++ Main.cpp SparseMatrix.cpp -o Main.exe ; .\Main.exe
//"C:\Users\User\Documents\GitHub\Taller2\MatricesPocoPobladas"

void llenarMatrizRand(SparseMatrix &matrix, int Nelementos, int maxcoord){
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
        llenarMatrizRand(matriz,n,static_cast<int>(densidad));
        clock_t fin = clock();
        double tiempo = double(fin - inicio)/CLOCKS_PER_SEC;
        contTime += tiempo;

    }
    return contTime/repeticiones;
}
double TiempoObtener(int n, int maxCoord, int repeticiones){
    double contTime = 0.0;  
    for(int i = 0; i < repeticiones; ++i){
        SparseMatrix matriz;
        llenarMatrizRand(matriz, n, maxCoord);
        clock_t inicio = clock();
        for(int j = 0; j < n; ++j){
            int fila = rand() % maxCoord;
            int col = rand() % maxCoord;
            matriz.get(fila, col);
        }
        clock_t fin = clock();
        double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;
        contTime += tiempo;
    }
    return contTime / repeticiones;
}
double TiempoMultiplicar(int n, int maxCoord, int repeticiones){
    double contTime = 0.0;  
    for(int i = 0; i < repeticiones; ++i){
        SparseMatrix matriz1, matriz2;
        llenarMatrizRand(matriz1, n, maxCoord);
        llenarMatrizRand(matriz2, n, maxCoord);
        clock_t inicio = clock();
        SparseMatrix* resultado = matriz1.multiply(&matriz2);
        clock_t fin = clock();
        delete resultado;
        double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;
        contTime += tiempo;
    }
    return contTime / repeticiones;
}
void Rendimiento() {
    int dataSets[] = {50, 250, 500, 1000, 5000};
    double densidades[] = {0.3, 0.75};
    int repeticiones =10;


    cout << "\n============================================\n";
    cout << "         PRUEBAS DE INSERCION\n";
    cout << "============================================\n";
    for (double densidad : densidades) {
        cout<< "Densidad: "<< densidad * 100<<"%"<<endl;
        cout << "----------------------------------------\n";
        for (int n : dataSets){
            int maxCoord = static_cast<int>(n/densidad);
            double promedio = TiempoInsercion(n,maxCoord,repeticiones);
            cout << "Numero de elementos: "<< n <<" | Tiempo promedio de insercion: "<< promedio << " s" << endl;
      }
    }
    cout << "\n============================================\n";
    cout << "         PRUEBAS DE OBTENCION (GET)\n";
    cout << "============================================\n";
    for (double densidad : densidades) {
        cout << "Densidad: " << densidad * 100 << "%"<<endl;
        cout << "----------------------------------------\n";
        for (int n : dataSets) {
            int maxCoord = static_cast<int>(n / densidad);
            double promedio = TiempoObtener(n, maxCoord, repeticiones);
            
            cout << "Numero de elementos: " << n <<" | Tiempo: " << promedio <<" s"<<endl;
        }
    }
    cout << "\n============================================\n";
    cout << "         PRUEBAS DE MULTIPLICACION\n";
    cout << "============================================\n";
    for (double densidad : densidades) {
        cout << "Densidad: " << densidad * 100 << "%"<<endl;
        cout << "----------------------------------------\n";
        for (int n : dataSets) {
            int maxCoord = static_cast<int>(n / densidad);
            double promedio = TiempoMultiplicar(n, maxCoord, repeticiones);
            cout << "Numero de elementos: " << n <<" | Tiempo: " <<  promedio << " s"<<endl;
        }
    }
}
void menu(){

    SparseMatrix matriz1, matriz2;
    SparseMatrix* resultado = nullptr;

    int opcion = -1;
    while (opcion != 0) {
        cout << " MENU MATRICES DISPERSAS \n";
        cout << "1. Agregar valor a matriz 1\n";
        cout << "2. Obtener valor de matriz 1\n";
        cout << "3. Eliminar valor de matriz 1\n";
        cout << "4. Imprimir matriz 1\n";
        cout << "5. Imprimir densidad de matriz 1\n";
        cout << "6. Llenar matriz 1 aleatoriamente\n";
        cout << "7. Agregar valor a matriz 2\n";
        cout << "8. Imprimir matriz 2\n";
        cout << "9. Multiplicar matriz1 x matriz2\n";
        cout << "0. Salir\n";
        cout << "Seleccione opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int fila, col, val;
                cout << "Fila: "; cin >> fila;
                cout << "Columna: "; cin >> col;
                cout << "Valor: "; cin >> val;
                matriz1.add(val, fila, col);
                cout<< "valor agregado correctamente\n";
                break;
            }
            case 2: {
                int fila, col;
                cout << "Fila: "; cin >> fila;
                cout << "Columna: "; cin >> col;
                cout << "Valor en (" << fila << "," << col << "): " 
                     << matriz1.get(fila, col) << endl;
                break;
            }
            case 3: {
                int fila, col;
                cout << "Fila: "; cin >> fila;
                cout << "Columna: "; cin >> col;
                matriz1.remove(fila, col);
                cout << "Valor eliminado si existía.\n";
                break;
            }
            case 4:
                cout << "Matriz 1:\n";
                matriz1.printStoredValues();
                break;
            case 5:
                cout << "Densidad matriz 1: " << matriz1.density() << "%\n";
                break;
            case 6: {
                int n, maxCoord;
                cout << "Numero de elementos: "; cin >> n;
                cout << "Maximo indice (filas/columnas): "; cin >> maxCoord;
                llenarMatrizRand(matriz1, n, maxCoord);
                cout << "Matriz 1 llenada aleatoriamente.\n";
                break;
            }
            case 7: {
                int fila, col, val;
                cout << "Fila: "; cin >> fila;
                cout << "Columna: "; cin >> col;
                cout << "Valor: "; cin >> val;
                matriz2.add(val, fila, col);
                break;
            }
            case 8:
                cout << "Matriz 2:\n";
                matriz2.printStoredValues();
                break;
            case 9:
                int n, maxCoord;
                cout << "Numero de elementos: "; cin >> n;
                cout << "Maximo indice (filas/columnas): "; cin >> maxCoord;
                llenarMatrizRand(matriz2, n, maxCoord);
                cout << "Matriz 2 llenada aleatoriamente.\n";
                break;
            case 10:
                if (resultado) delete resultado;
                resultado = matriz1.multiply(&matriz2);
                cout << "Resultado matriz1 x matriz2:\n";
                resultado->printStoredValues();
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    }

    if (resultado) delete resultado;

}
int main(){
    srand(time(nullptr));
    int opcion = -1;

    while (opcion != 0) {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1. Menu de matrices dispersas\n";
        cout << "2. Pruebas de rendimiento\n";
        cout << "0. Salir\n";
        cout << "Seleccione opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                menu();
                break;
            case 2:
                Rendimiento();
                break;
            case 0:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    }

    return 0;
}

