#pragma once
#include "Matrix.h"
class Translation : public Matrix
{
public:
	void setVX(int);
	void setVY(int);


	Translation(int vx, int vy);
	~Translation();
private:
	int vx, vy;
};

