#include <iostream>
#include "SparseMatrix.h"
using namespace std;

// Constructor
SparseMatrix::SparseMatrix() {
    start = nullptr;
}

// Destructor
SparseMatrix::~SparseMatrix() {
    Nodo* current = start;
    while (current != nullptr) {
        Nodo* temp = current;
        current = current->next;
        delete temp;
    }

}
// Obtener el valor en (x, y)
int SparseMatrix::get(int xPos, int yPos) {
    Nodo* current = start;
    while (current != nullptr) {
        if (current->x == xPos && current->y == yPos) {
            return current->value;
        }
        current = current->next;
    }
    return 0;
}

// Calcular densidad de la matriz
int SparseMatrix::density() {
    if (start == nullptr) return 0;

    int count = 0;
    int maxX = 0, maxY = 0;

    Nodo* current = start;
    while (current != nullptr) {
        count++;
        if (current->x > maxX) maxX = current->x;
        if (current->y > maxY) maxY = current->y;
        current = current->next;
    }

    int total = (maxX + 1) * (maxY + 1);
    if (total == 0) return 0;

    double dens = (double)count / total * 100.0;
    cout << "Densidad: " << dens << "% (" << count << "/" << total << ")" << endl;
    return (int)dens;
}

// Multiplicar dos matrices poco pobladas
SparseMatrix* SparseMatrix::multiply(SparseMatrix* second) {
    SparseMatrix* result = new SparseMatrix();
    if (start == nullptr || second->start == nullptr)
        return result;

    Nodo* a = start;
    while (a != nullptr) {
        Nodo* b = second->start;
        while (b != nullptr) {
            if (a->y == b->x) {
                int prev = result->get(a->x, b->y);
                result->add(prev + a->value * b->value, a->x, b->y);
            }
            b = b->next;
        }
        a = a->next;
    }
    return result;
}
