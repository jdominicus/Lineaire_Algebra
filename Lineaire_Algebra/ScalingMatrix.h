#pragma once

#include "Matrix.h"

class ScalingMatrix : public Matrix
{
	public:
		ScalingMatrix(int n, int m, double x, double y, double z);
		~ScalingMatrix() override;
};

ScalingMatrix::ScalingMatrix(int n, int m, double x, double y, double z) : Matrix(n, m)
{
	(*this)(0, 0) = x;
	(*this)(1, 1) = y;
	(*this)(2, 2) = z;
	(*this)(3, 3) = 1;
}

ScalingMatrix::~ScalingMatrix()
{
}
