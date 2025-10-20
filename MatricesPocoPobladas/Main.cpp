#include <iostream>
#include "SparseMatrix.h"
#include <chrono>
#include <ctime>
#include <cstdlib>
using namespace std;
//comando de accion g++ Main.cpp SparseMatrix.cpp -o Main.exe ; .\Main.exe
void SparseMatrixRandom(SparseMatrix &matrix, int Nelementos, int Xmax, int Ymax){
    int cont =0;
    while(cont<Nelementos){
        int x = rand() % Xmax;
        int y = rand() % Ymax;
        if(matrix.get(x,y)==0){
            int valor = rand() % 100 +1;
            matrix.add(valor, x, y);
            cont++;
        }
    }
}
void TestTime(int Nelementos, int Xmax, int Ymax){
    SparseMatrix A;
    auto start = chrono::high_resolution_clock::now();
    SparseMatrixRandom(A, Nelementos, Xmax,Ymax);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout <<"Se insertaron " << Nelementos <<" elementos, tiempo estimado " << elapsed.count() << "segundos" << endl;
}
void DensityTest(int Nelementos){
    int lowDMax= Nelementos*3;
    int HighDMax= Nelementos/2;
    cout <<" Densidad menor (<40%):" <<endl;
    TestTime(Nelementos, lowDMax,lowDMax);
    cout<<"Densidad mayor (>70%): "<< endl;
    TestTime(Nelementos, HighDMax,HighDMax);

}

void menu() {
    SparseMatrix A,B,C;
    srand(time(0));
    int opcion;
    do{
         cout << "\n===== MATRIZ POCO POBLADA =====" << endl;
        cout << "1. Insertar elemento" << endl;
        cout << "2. Obtener elemento" << endl;
        cout << "3. Eliminar elemento" << endl;
        cout << "4. Imprimir elementos" << endl;
        cout << "5. Calcular densidad" << endl;
        cout << "6. Multiplicar dos matrices" << endl;
        cout << "7. Pruebas de tiempo y densidad" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        int x,y,val,n;
        
        switch (opcion){
            case 1:{
                int x, y, val;
                cout << "\n--- Insertar elemento ---" << endl;
                cout << "Ingrese coordenada X: ";
                cin >> x;
                cout << "Ingrese coordenada Y: ";
                cin >> y;
                cout << "Ingrese valor (entero distinto de 0): ";
                cin >> val;
                A.add(val, x, y);    
                break;
            }case 2:{
                cout << "\n--- Insertar elemento ---" << endl;
                cout << "Ingrese coordenada X: ";
                cin >> x;
                cout << "Ingrese coordenada Y: ";
                cin >> y;
                cout << "Valor en (" << x << ", " << y << "): " << A.get(x, y) << endl;
                break;
            }case 3:  {
                cout << "\n--- Insertar elemento ---" << endl;
                cout << "Ingrese coordenada X: ";
                cin >> x;
                cout << "Ingrese coordenada Y: ";
                cin >> y;
                A.remove(x, y);
                cout << "Elemento eliminado (si existía)." << endl;
                break; 
            }case 4:{
                A.printStoredValues();
                break;
            }case 5:{
                cout << "Densidad de la matriz: " << A.density() * 100 << "%" << endl;
                break;
            }case 6: {
                cout << "Generando segunda matriz..." << endl;
                SparseMatrixRandom(B, 5, 5, 5);
                cout << "Resultado de la multiplicación:" << endl;
                SparseMatrix* resultado = A.multiply(&B);
                resultado->printStoredValues();
                delete resultado;
                break;
            }case 7:{
                cout << " Ejecutando todas las pruebas de rendimiento...";
                runAllTests();
                cout << "\nPresione Enter para volver al menú...";
                cin.ignore();
                cin.get();
            
                break;
            }case 0:{
                cout<<"Saliendo..."<<endl;
                break;
            }default:
            cout<<"Opcion invalida."<<endl;
        }
    }while(opcion!=0);
}
void runAllTests() {
    srand(time(0));
    int dataSets[] = {50, 250, 500, 1000, 5000};

    cout << "      PRUEBAS DE RENDIMIENTO     \n";

    for (int i = 0; i < 5; i++) {
        int n = dataSets[i];
        cout << " Probando con " << n << " elementos...";

        // ---- Prueba de densidad < 40% ----
        cout << "--- Densidad baja (<40%) ---";
        int lowDensityMax = n * 3;  // más dispersa
        TestTime(n, lowDensityMax, lowDensityMax);

        // ---- Prueba de densidad > 70% ----
        cout << "--- Densidad alta (>70%) ---";
        int highDensityMax = n / 2; // más concentrada
        TestTime(n, highDensityMax, highDensityMax);
    }

    cout << " Todas las pruebas finalizadas.";
}
int main(){
    menu();
    return 0;
}