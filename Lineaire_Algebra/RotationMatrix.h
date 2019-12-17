#pragma once

#include "Matrix.h"

class RotationMatrix : public Matrix
{
public:
	RotationMatrix(int n, int m, float radians,  char rotation);
	~RotationMatrix() override;
};

RotationMatrix::RotationMatrix(int n, int m, float radians, char rotation) : Matrix(n, m)
{
	for (int i = 0; i < n; i++)
		(*this)(i, i) = 1;

	switch (rotation)
	{
		case 'X':
			(*this)(1, 1) = cos(radians);
			(*this)(1, 2) = -sin(radians);
			(*this)(2, 1) = sin(radians);
			(*this)(2, 2) = cos(radians);
			break;
		case 'Y':	
			(*this)(0, 0) = cos(radians);
			(*this)(0, 2) = sin(radians);
			(*this)(2, 0) = -sin(radians);
			(*this)(2, 2) = cos(radians);
			break;
		case 'Z':
			(*this)(0, 0) = cos(radians);
			(*this)(0, 1) = -sin(radians);
			(*this)(1, 0) = sin(radians);
			(*this)(1, 1) = cos(radians);
			break;
	}
}

RotationMatrix::~RotationMatrix()
{
}

