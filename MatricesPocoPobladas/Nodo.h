#pragma once
struct Nodo {
    int x;
    int y;
    int value;
    Nodo* next;
    Nodo(int posX, int posY, int val) {
        x = posX;
        y = posY;
        value = val;
        next = nullptr;
    }
};