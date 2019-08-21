#pragma once
#include <vector>
#include "Vector.h"
#include <math.h>
#include <cmath>
#include <iostream>
#ifndef  Matrix_H
#define Matrix_H

class Matrix
{
protected:
	std::vector<std::vector<float> > mat;
private:
	unsigned rows;
	unsigned cols;

public:
	Matrix();
	Matrix(unsigned rows, unsigned cols);
	//Matrix(Vector vec);

	
	Matrix(const Matrix& rhs);
	virtual ~Matrix();
	
	unsigned getRows() const;

	unsigned getCols() const;

	Matrix& operator=(Matrix);
	Matrix operator+(Matrix&);
	Matrix operator-(Matrix&);
	Matrix operator*(Matrix&);
	Matrix transpose();
	Matrix identity();
	////Multiplicar por un escalar
	Matrix operator+(float&);
	Matrix operator-(float&);
	Matrix operator*(float&);
	Matrix operator/(float&);
	Vector operator*(const Vector&);
	


	float& operator()(const unsigned&, const unsigned&);
	void Print(); void ModifyMatrix(); void VectorInMatrix(Vector&, Vector&);

};

#endif // ! Matrix_H
