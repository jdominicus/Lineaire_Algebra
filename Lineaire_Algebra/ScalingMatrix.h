#pragma once

#include "Matrix.h"

template <typename T>
class ScalingMatrix : public Matrix<T>
{
	public:
		ScalingMatrix<T>(int n, int m, T x, T y, T z);
		~ScalingMatrix() override;
};

template <typename T>
ScalingMatrix<T>::ScalingMatrix(int n, int m, T x, T y, T z) : Matrix<T>(n, m)
{
	(*this)(0, 0) = x;
	(*this)(1, 1) = y;
	(*this)(2, 2) = z;
	(*this)(3, 3) = 1;
}

template <typename T>
ScalingMatrix<T>::~ScalingMatrix()
{
}
