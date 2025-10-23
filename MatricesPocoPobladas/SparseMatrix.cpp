#include <iostream>
#include "SparseMatrix.h"
using namespace std;

// Constructor
SparseMatrix::SparseMatrix() {
    numCols=0;
}

// Destructor
SparseMatrix::~SparseMatrix() {
    for(auto head : filas){
        while (head) {
            Nodo* temp = head;
            head = head->next;
            delete temp;
        }
    }
}
// Insertar un dato en coordenadas (x, y)
void SparseMatrix::add(int valor, int fila, int col) {
    if (valor == 0) return;

    if (fila>=filas.size()) 
        filas.resize(fila+1,nullptr);
    
    if(col>=numCols)
        numCols=col+1;

    Nodo* &head=filas[fila];
    Nodo* current = head;
    Nodo* prev = nullptr;

    while (current && current->col < col) {
        prev = current;
        current = current->next;
    }

    if (current && current->col == col) {
        current->valor = valor;
        return;
    }else{
        Nodo* nuevo = new Nodo(col,valor);
        nuevo->next = current;
        if(prev) prev->next=nuevo;
        else head = nuevo;
    }
}

// Obtener el valor en (x, y)
int SparseMatrix::get(int fila, int col) {
    if(fila >=filas.size()) return 0;
    Nodo* current = filas[fila];
    while (current) {
        if (current->col == col) return current->valor;
        current = current->next;
    }
    return 0;
}

// Eliminar un valor en (x, y)
void SparseMatrix::remove(int fila, int col) {
    if (fila>=filas.size()) return;

    Nodo* current = filas[fila];
    Nodo* prev = nullptr;

    while (current) {
        if (current->col == col) {
            if (prev){
                prev->next=current->next;
            }else{
                filas[fila]=current->next;
            }    
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Imprimir valores almacenados
void SparseMatrix::printStoredValues() {
    for(int i=0; i<filas.size(); ++i){
        Nodo* current = filas[i];
        while (current != nullptr) {
            cout << "(" << i << ", " << current->col << ") -> " << current->valor << endl;
            current = current->next;
        }
    }
}
// Calcular densidad de la matriz
double SparseMatrix::density() {
    if (filas.empty() || numCols==0) return 0.0;

    int NoZero=0;

    for(auto head : filas){
        Nodo* current = head;
        while (current != nullptr) {
            NoZero++;
            current = current->next;
        }
    }
    int total = (filas.size()) * (numCols);
    return (double) NoZero / total *100.0;
    
}

// Multiplicar dos matrices poco pobladas
SparseMatrix* SparseMatrix::multiply(SparseMatrix* second) {
    SparseMatrix* result = new SparseMatrix();
    if (filas.empty() || second->filas.empty()) return result;
    for(int i=0;i<filas.size();++i){
        Nodo* aux = filas[i];
        while (aux) {
            int k = aux->col;
            if(k<second->filas.size()){
                Nodo* aux2 = second->filas[k];
                while (aux2) {
                    int val = result->get(i,aux2->col);
                    result->add(val +aux->valor * aux2->valor,i,aux2->col);
                    aux2 = aux2->next;
                }
            }
            aux = aux->next;
        }

    }
    return result;
}
