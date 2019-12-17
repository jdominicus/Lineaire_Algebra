#pragma once
#include "Matrix.h"

class TranslationMatrix : public Matrix
{
	public:
		TranslationMatrix(int n, int m, float x, float y, float z);
		~TranslationMatrix() override;
};

TranslationMatrix::TranslationMatrix(int n, int m, float x, float y, float z) : Matrix(n, m)
{
	for (int i = 0; i < n; i++)
		(*this)(i, i) = 1;

	(*this)(0, 3) = x;
	(*this)(1, 3) = y;
	(*this)(2, 3) = z;
}

TranslationMatrix::~TranslationMatrix()
{
}
