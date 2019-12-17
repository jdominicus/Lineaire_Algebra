#include "Matrix.h"
#include "Vector.h"

Matrix::Matrix() : Matrix(1, 1)
{
}

Matrix::Matrix(int n, int m) : rows{ n }, collumns{ m }
{
	for (int i = 0; i < rows * collumns; i++)
		elements.emplace_back(float(0));
}

Matrix::Matrix(const Matrix& other)
{
	this->elements = other.elements;
	this->rows = other.rows;
	this->collumns = other.collumns;
}

Matrix::~Matrix()
{
}

float& Matrix::operator()(int row, int col)
{
	return elements[row * collumns + col];
}

const float& Matrix::operator()(int row, int col) const
{
	return elements[row * collumns + col];
}

Matrix& Matrix::operator=(const Matrix& other)
{
	this->rows = other.rows;
	this->collumns = other.collumns;
	this->elements = std::vector<float>(other.elements);
	return *this;
}

Matrix Matrix::operator+(const Matrix& other)
{
	Matrix m = *this;

	for (int i = 0; i < m.elements.size(); i++)
		m.elements.at(i) += other.elements.at(i);

	return m;
}

void Matrix::operator+=(const Matrix& other)
{
	for (int i = 0; i < this->elements.size(); i++)
		this->elements.at(i) += other.elements.at(i);
}

Matrix Matrix::operator-(const Matrix& other)
{
	Matrix m = *this;

	for (int i = 0; i < m.elements.size(); i++)
		m.elements.at(i) -= other.elements.at(i);

	return m;
}

void Matrix::operator-=(const Matrix& other)
{
	for (int i = 0; i < this->elements.size(); i++)
		this->elements.at(i) -= other.elements.at(i);
}

Matrix Matrix::operator*(const Matrix& other)
{
	if (this->collumns != other.rows)
		return *this;
	else
	{
		Matrix m(this->rows, other.collumns);

		for (int i = 0; i < m.rows; i++)
		{
			for (int j = 0; j < m.collumns; j++)
			{
				float value = 0;

				for (int k = 0; k < (*this).collumns; k++)
					value += (*this)(i, k) * other(k, j);

				m(i, j) = value;
			}
		}

		return m;
	}
}

void Matrix::operator*=(const Matrix& other)
{
	if (this->collumns == other.rows)
	{
		Matrix m(this->rows, other.collumns);

		for (int i = 0; i < m.rows; i++)
		{
			for (int j = 0; j < m.collumns; j++)
			{
				float value = 0;

				for (int k = 0; k < (*this).collumns; k++)
					value += (*this)(i, k) * other(k, j);

				m(i, j) = value;
			}
		}

		*this = m;
	}
}

Matrix Matrix::operator+(const float& other)
{
	Matrix m = *this;

	for (int i = 0; i < m.elements.size(); i++)
		m.elements.at(i) += other;

	return m;
}

void Matrix::operator+=(const float& other)
{
	for (int i = 0; i < this->elements.size(); i++)
		this->elements.at(i) += other;
}

Matrix Matrix::operator-(const float& other)
{
	Matrix m = *this;

	for (int i = 0; i < m.elements.size(); i++)
		m.elements.at(i) -= other;

	return m;
}

void Matrix::operator-=(const float& other)
{
	for (int i = 0; i < this->elements.size(); i++)
		this->elements.at(i) -= other;
}

Matrix Matrix::operator*(const float& other)
{
	Matrix m = *this;

	for (float& element : m.elements)
		element *= other;

	return m;
}

void Matrix::operator*=(const float& other)
{
	for (float& element : this->elements)
		element *= other;
}

Matrix Matrix::operator/(const float& other)
{
	Matrix m = *this;

	for (float& element : m.elements)
		element /= other;

	return m;
}

void Matrix::operator/=(const float& other)
{
	for (float& element : this->elements)
		element /= other;
}

Vector Matrix::operator*(const Vector& other)
{
	Matrix m(this->rows, 1);
	m(0, 0) = other.x;
	m(0, 1) = other.y;
	m(0, 2) = other.z;

	for (int i = 3; i < this->rows; i++)
		m(0, i) = 1;

	Matrix n = *this * m;
	return Vector(n(0, 0), n(0, 1), n(0, 2));
}

Matrix operator*(const float& number, const Matrix& other)
{
	Matrix m = other;

	for (float& element : m.elements)
		element *= number;

	return m;
}

std::ostream& operator<<(std::ostream& stream, const Matrix& other)
{
	for (int n = 0; n < other.rows; n++)
	{
		for (int m = 0; m < other.collumns; m++)
		{
			stream << other(n, m);
			stream << " ";
		}

		if (n < other.rows - 1)
			stream << "| ";
	}

	return stream;
}