#include <iostream>
#include "SparseMatrix.h"
using namespace std;

int main() {
    SparseMatrix A, B;

    A.add(2, 0, 0);
    A.add(6, 0, 1);

    B.add(7, 0, 4);
    B.add(2, 1, 4);

    cout << "Matriz A:\n";
    A.printStoredValues();

    cout << "\nMatriz B:\n";
    B.printStoredValues();

    cout << "\nDensidad de A: ";
    A.density();

    SparseMatrix* C = A.multiply(&B);

    cout << "\nResultado de A x B:\n";
    C->printStoredValues();

    delete C;
    return 0;
}