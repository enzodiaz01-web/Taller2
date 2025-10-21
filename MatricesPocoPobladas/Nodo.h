#pragma once
struct Nodo {
    int col;
    int valor;
    Nodo* next;
    Nodo(int col, int val) {
        col = col;
        valor = val;
        next = nullptr;
    }
};