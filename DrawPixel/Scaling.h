#pragma once
#include "Matrix.h"
class Scaling : public Matrix
{
public:
	Scaling(int sx, int sy);
	~Scaling();

	int setSX(int);
	int setSY(int);
private:
	int sx, sy;
};

