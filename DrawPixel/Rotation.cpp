#include "pch.h"
#include "Rotation.h"

float Rotation::setAngle(float _angle) {
	angle = _angle;
	return angle;
}
Rotation::Rotation(float angle) {
	const float mult = angle;
	mat.resize(3);
	for (int i = 0; i < mat.size(); i++) {
		mat[i].resize(3, 0);
	}
	mat[0][0] = std::cos(mult);
	mat[0][1] = std::sin(mult);
	mat[1][0] = -std::sin(mult);
	mat[1][1] = std::cos(mult);
}


Rotation::~Rotation()
{
}

