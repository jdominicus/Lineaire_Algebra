#pragma once

#include "Matrix.h"

template <typename T>
class TranslationMatrix : public Matrix<T>
{
	public:
		TranslationMatrix<T>(int n, int m, T x, T y, T z);
		~TranslationMatrix() override;
};

template <typename T>
TranslationMatrix<T>::TranslationMatrix(int n, int m, T x, T y, T z) : Matrix<T>(n, m)
{
	for (int i = 0; i < n; i++)
		(*this)(i, i) = 1;

	(*this)(0, 3) = x;
	(*this)(1, 3) = y;
	(*this)(2, 3) = z;
}

template <typename T>
TranslationMatrix<T>::~TranslationMatrix()
{
}
