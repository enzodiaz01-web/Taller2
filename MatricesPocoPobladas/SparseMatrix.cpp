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
