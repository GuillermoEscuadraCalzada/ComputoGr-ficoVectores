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
//
//Matrix::Matrix(Vector vec)
//{
//	mat.resize(3);
//	for (int i = 0; i < mat.size(); i++) {
//		mat[i].resize(1, 0);
//	}
//	rows = 3;
//	cols = 1;
//	mat[0][0] = vec.x;
//	mat[1][0] = vec.y;
//	mat[2][0] = 1;
//
//}

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

//Vector Matrix::translate(Vector& vec) {
//
//	unsigned newRows = rows + 1;
//	unsigned newCols = cols + 1;
//	Matrix traslacion(newRows, newCols);
//	Matrix v(vec);
//
//	for (int i = 0; i < newRows; i++)
//		for (int j = 0; j < newCols; j++) {
//			if (i == j)
//				traslacion(i, j) = 1;
//			else
//				traslacion(i, j) = 0;
//		}
//
//	printf("Elije donde trasladar en x:\n");
//	std::cin >> traslacion(0,2);
//	printf("Elije donde trasladar en y:\n");
//	std::cin >> traslacion(1,2);
//	traslacion.Print();
//	printf("\n");
//
//	v = traslacion * v;
//
//	return Vector(v(0,0),v(1,0));
//}
//
//Vector Matrix::scale(Vector& vec)
//{
//	unsigned newRows = rows + 1;
//	unsigned newCols = cols + 1;
//	Matrix escalar(newRows, newCols);
//	Matrix v(vec);
//
//	for (int i = 0; i < newRows; i++)
//		for (int j = 0; j < newCols; j++) {
//			if (i == j)
//				escalar(i, j) = 1;
//			else
//				escalar(i, j) = 0;
//		}
//
//	printf("Elije cuanto escalar en x:\n");
//	std::cin >> escalar(0, 0);
//	printf("Elije cuanto escalar en y:\n");
//	std::cin >> escalar(1, 1);
//	escalar.Print();
//	printf("\n");
//
//	v = escalar * v;
//
//	return Vector(v(0, 0), v(1, 0));
//}
//
//Vector Matrix::rotation(Vector& vec, int angle)
//{
//	unsigned newRows = rows + 1;
//	unsigned newCols = cols + 1;
//	Matrix traslacion(newRows, newCols);
//	Matrix v(vec);
//
//	for (int i = 0; i < newRows; i++)
//		for (int j = 0; j < newCols; j++) {
//			traslacion(0,0)= std::cos((angle * 57.2958)/180);
//			traslacion(0,1) = std::sin((angle * 57.2958) / 180);
//			traslacion(1,0) = -std::sin((angle * 57.2958) / 180);
//			traslacion(1,1) = std::cos((angle * 57.2958) / 180);
//			traslacion(2, 2) = 1;
//		}
//
//	traslacion.Print();
//	printf("\n");
//	v = traslacion * v;
//
//	return Vector(v(0, 0), v(1, 0));
//}

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

	/*for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix(i, j) = mat[i][j] + number;
		}
	}*/
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

	/*for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matr(i, j) = mat[i][j] * number;
		}
	}*/
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

void Matrix::ModifyMatrix(int a){

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cin >> a;
			mat[i][j]= a;
		}
	}

}


