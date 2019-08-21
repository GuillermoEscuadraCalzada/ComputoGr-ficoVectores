#pragma once
#include "Matrix.h"
class Rotation :public Matrix
{
public:
	Rotation(float);
	~Rotation();

	float setAngle(float);
private:
	float angle;

};

