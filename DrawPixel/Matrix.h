#pragma once
#include <vector>
#include "Vector.h"
#include <iostream>
#ifndef  Matrix_H
#define Matrix_H

class Matrix
{
private:
	std::vector<std::vector<float> > mat;
	unsigned rows;
	unsigned cols;
	int t;
public:
	Matrix();
	Matrix(unsigned rows, unsigned cols);
	Matrix(unsigned _rows, unsigned _cols, int y) : rows(_rows), cols(_cols), t(y) {};

	
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
	Matrix translate(Matrix, Matrix, int, int);
	//
	////Multiplicar por un escalar
	Matrix operator+(float&);
	Matrix operator-(float&);
	Matrix operator*(float&);
	Matrix operator/(float&);
	//Vector operator*(const Vector&);

	float& operator()(const unsigned&, const unsigned&);
	void Print(); void ModifyMatrix(int);

};

#endif // ! Matrix_H
