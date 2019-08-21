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
			matriz(i, j) = mat[i][j] - mtrx(i, j);
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

Matrix  Matrix::identity()
{
	Matrix matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == j)
				matriz(i, j) = 1;
			else
				matriz(i, j) = 0;
		}
	}
	return matriz;
}


Vector Matrix::operator*(const Vector& vec1) {
	//Matrix matrx(rows,cols);

	Vector vectorResultante(0,0,0);
	
	mat.resize(3);
	for (int i = 0; i < mat.size(); i++) {
		mat[i].resize(3, 0);
	}
	
	vectorResultante.x = vec1.x * mat[0][0] + vec1.y * mat[0][1] + vec1.z*mat[0][2];
	vectorResultante.y = vec1.x * mat[1][0] + vec1.y * mat[1][1] + vec1.z*mat[1][2];
	vectorResultante.z = vec1.x * mat[2][0] + vec1.y * mat[2][1] + vec1.z*mat[2][2];

	return vectorResultante;

}

//Operaciones con números
Matrix Matrix::operator+(float &number)
{
	Matrix matrix(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix(i, j) = mat[i][j] + number;
		}
	}
	return matrix;
}

Matrix Matrix::operator-(float& number)
{
	Matrix matrz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrz(i, j) = mat[i][j] - number;
		}
	}

	return matrz;
}

Matrix Matrix::operator*(float &number)
{
	Matrix matr(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matr(i, j) = mat[i][j] * number;
		}
	}
	return matr;
}

Matrix Matrix::operator/(float &number)
{
	Matrix matri(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matri(i, j) = mat[i][j] / number;
		}
	}
	return matri;
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
		printf("\n");
	}
	printf("\n");
}

void Matrix::ModifyMatrix(){
	int a = 0;
	printf("Ingresa los valores de cada elemento de la matriz.\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cin >> a;
			mat[i][j]= a;
		}
	}

}

void Matrix::VectorInMatrix(Vector &vec1, Vector &vec2)
{
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			
			mat[0][0] = vec1.x;
			mat[0][1] = vec1.y;
			mat[1][0] = vec2.x;
			mat[1][1] = vec2.y;
		}
	}


}


