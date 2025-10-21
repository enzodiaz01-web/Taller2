#pragma once
#include "Nodo.h"
#include <vector>
class SparseMatrix {
private:
	std::vector<Nodo*> filas;
	int numCols;
public:
	SparseMatrix();
	void add(int value, int xPos, int yPos);
	int get(int xPos, int yPos);
	void remove(int xPos, int yPos);
	void printStoredValues();
	int density();
	SparseMatrix* multiply(SparseMatrix* second);

	~SparseMatrix();
	
};