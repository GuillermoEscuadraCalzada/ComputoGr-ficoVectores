#include "pch.h"
#include "Vector.h"


Vector::Vector() {
	x = y = z = 0;
}

Vector::~Vector() {

}

Vector::Vector(float a, float b) {
	x = a; y = b; z = 0;
}

Vector::Vector(float a, float b, float c) {
	x = a; y = b; z = c;
}

float Vector::productoPunto(const Vector& vector2) {
	float punto;
	punto = x * vector2.x + y * vector2.y + z * vector2.z;
	return punto;
}

float Vector::magnitud() {
	//magnitud de un vector nos regresa la distancia de todo el vector.
	return sqrt(x * x + y * y + z * z);
}

void Vector::vectorNormal() {
	float magn = magnitud();

	if (magn != 0) {
		x /= magn;
		y /= magn;
		z /= magn;
	}

}

Vector Vector::productoCruz(const Vector& vector2) {
	Vector cruz;
	cruz.x = y * vector2.z - z * vector2.y;
	cruz.y = -(x*vector2.z - z * vector2.x);
	cruz.z = x * vector2.y - y * vector2.x;

	return Vector(cruz.x,cruz.y, cruz.z);
}

Vector Vector::operator+(const Vector vector2)
{
	Vector suma;
	suma.x = x + vector2.x;
	suma.y = y + vector2.y;
	suma.z = z + vector2.z;
	return Vector(suma.x, suma.y, suma.z);
}

Vector Vector::operator-(const Vector vector2)
{
	Vector resta;
	resta.x = x - vector2.x;
	resta.y = y - vector2.y;
	resta.z = z - vector2.z;
	return Vector(resta.x, resta.y, resta.z);
}

Vector Vector::operator*(float numero)
{
	//multiplicacion por un numero escalar, regresa un vector.
	Vector escalar;
	escalar.x = x * numero;
	escalar.y = y * numero;
	escalar.z = z * numero;
	return Vector(escalar.x, escalar.y, escalar.z);
}

Vector Vector::operator/(float numero)
{
	Vector div;
	div.x = x / numero;
	div.y = y / numero;
	div.z = z / numero;
	return Vector(div.x, div.y, div.z);
}

Vector Vector::operator=(const Vector vector2)
{
	
	return Vector(x=vector2.x,y=vector2.y,z=vector2.z);
}

void Vector::setValues(int _x, int _y, int _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void Vector::Print() {
	std::cout << "Este es tu vector: (" << x << ", " << y << ")\n";
}

void Vector::ModifyVector()
{
	//El usuario ingresará cada valor del eje 'X' y 'Y'
	std::cout << "Ingresa los valores de x: ";
	std::cin >> x; printf("\n");
	std::cout << "Ingresa los valores de y: ";
	std::cin >> y; printf("\n\n");
}
