#pragma once
#include<cmath>
#include <iostream>
class Vector
{
public:
	float x, y, z;
	Vector();
	~Vector();
	Vector(float, float);
	Vector(float, float, float);

	float productoPunto(const Vector& vector2);
	float magnitud();
	void vectorNormal();

	Vector productoCruz(const Vector& vector2);
	Vector operator+(const Vector vector2);
	Vector operator-(const Vector vector2);
	Vector operator*(float numero);
	Vector operator/(float numero);
	Vector operator=(const Vector vector2);

	void Print();
};

