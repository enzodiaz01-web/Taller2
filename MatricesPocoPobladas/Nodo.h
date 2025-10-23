#pragma once
struct Nodo {
    int col;
    int valor;
    Nodo* next;
    Nodo(int c, int val) {
        this->col = c;
        this->valor = val;
        this->next = nullptr;
    }
};