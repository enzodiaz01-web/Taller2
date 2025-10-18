#include <iostream>
#include "SparseMatrix.h"
#include <set>
#include <chrono>
using namespace std;

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


int main() {
    srand(time(0));
    TestTime(50,100,100);
    TestTime(250,200,200);
    TestTime(500,300,300);
    TestTime(1000,500,500);
    TestTime(5000,1000,1000);
    
    return 0;
}