#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}

void Matrix::addVector(std::unique_ptr<Vector> vector)
{
	vectors.emplace_back(std::move(vector));
}

void Matrix::scale()
{
	
}

void Matrix::translate()
{
	
}

void Matrix::draw()
{
	
}
