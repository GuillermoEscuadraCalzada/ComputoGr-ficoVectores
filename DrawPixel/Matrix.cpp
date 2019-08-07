#include "pch.h"
#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix(unsigned _rows, unsigned _cols)
{
	mat.resize(_rows);
	for (int i = 0; i < mat.size(); i++) {
		mat[i].resize(_cols, 0);
	}
	rows = _rows;
	cols = _cols;
}

//Constructor de copia
Matrix::Matrix(const Matrix & other)
{
	mat = other.mat;
	cols = other.getCols();
	rows = other.getRows();
}

Matrix::~Matrix()
{
}

//Obtener filas y columnas
unsigned Matrix::getRows() const
{
	return this->rows;
}

unsigned Matrix::getCols() const
{
	return this->cols;
}


Matrix & Matrix::operator=(Matrix other)
{
	if (&other == this)
		return*this;

	unsigned newRows = other.getRows();
	unsigned newCols = other.getCols();
	mat.resize(newRows);

	for (unsigned i = 0; i < mat.size(); i++) {
		mat[i].resize(newCols);
	}
	for (unsigned i = 0; i < newRows; i++) {
		for (unsigned j = 0; j < newCols; j++) {
			mat[i][j] = other(i, j);
		}
	}

	rows = newRows;
	cols = newCols;

	return*this;

}

//operaciones con otra matriz
Matrix Matrix::operator+(Matrix & mtrx)
{
	Matrix matriz(rows, cols);
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			 matriz(i,j) = mat[i][j] + mtrx(i,j);
		}
	}
	
	return matriz;
}

Matrix Matrix::operator-(Matrix &mtrx)
{
	Matrix matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = this->mat[i][j] - mtrx(i, j);
		}
	}

	return matriz;
}

Matrix Matrix::operator*(Matrix& mtrx)
{
	Matrix matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = 0;
		}
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < mtrx.getCols(); j++) {
			for (int k = 0; k < cols; k++) {
				matriz(i, j) += mat[i][k] * mtrx(k,j);
			}
		}
	}
	
	return matriz;
}

Matrix Matrix::transpose()
{
	Matrix matriz(rows, cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			matriz(i,j) = mat[j][i];
		}

	return matriz;
}

//Operaciones con números
Matrix Matrix::operator+(float &number)
{
	Matrix matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = this->mat[i][j] + number;
		}
	}
	return matriz;
}

Matrix Matrix::operator-(float& number)
{
	Matrix matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = this->mat[i][j] - number;
		}
	}
	return matriz;
}

Matrix Matrix::operator*(float &number)
{
	Matrix matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = this->mat[i][j] * number;
		}
	}
	return matriz;
}

Matrix Matrix::operator/(float &number)
{
	Matrix matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = this->mat[i][j] / number;
		}
	}
	return matriz;
}

float & Matrix::operator() (const unsigned & row, const unsigned &col)
{
	return this->mat[row][col];
}

void Matrix::Print()
{
	printf("Esta es tu matriz.\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Matrix::ModifyMatrix(int a){

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cin >> a;
			mat[i][j]= a;
		}
	}

}


