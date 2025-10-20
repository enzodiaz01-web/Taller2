#pragma once
#include "Nodo.h"
class SparseMatrix {
private:
	Nodo* start;
public:
	SparseMatrix();
	void add(int value, int xPos, int yPos);
	int get(int xPos, int yPos);
	void remove(int xPos, int yPos);
	void printStoredValues();
	double density();
	SparseMatrix* multiply(SparseMatrix* second);
	~SparseMatrix();
	double densidad(int filas, int columnas);
	int getPosicion(int PosX, int PosY);
	void deleteEnPosision(int PosX, int PosY);
};