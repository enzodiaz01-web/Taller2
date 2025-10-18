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
// Insertar un dato en coordenadas (x, y)
void SparseMatrix::add(int value, int xPos, int yPos) {
    if (value == 0) return;

    if (start == nullptr) {
        start = new Nodo(xPos, yPos, value);
        return;
    }

    Nodo* current = start;
    Nodo* prev = nullptr;

    while (current != nullptr) {
        if (current->x == xPos && current->y == yPos) {
            current->value = value;
            return;
        }
        prev = current;
        current = current->next;
    }

    prev->next = new Nodo(xPos, yPos, value);
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

// Eliminar un valor en (x, y)
void SparseMatrix::remove(int xPos, int yPos) {
    if (start == nullptr) return;

    Nodo* current = start;
    Nodo* prev = nullptr;

    while (current != nullptr) {
        if (current->x == xPos && current->y == yPos) {
            if (current == start)
                start = current->next;
            else
                prev->next = current->next;
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Imprimir valores almacenados
void SparseMatrix::printStoredValues() {
    Nodo* current = start;
    if (!current) {
        cout << "(Matriz vacía)" << endl;
        return;
    }
    while (current != nullptr) {
        cout << "(" << current->x << ", " << current->y << ") --> " << current->value << endl;
        current = current->next;
    }
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
