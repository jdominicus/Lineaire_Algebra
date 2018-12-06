#ifndef Matrix_hpp
#define Matrix_hpp

#include <vector>
#include <iostream>

template <typename T>
class Matrix
{
	template <typename>
	friend class Vector;

	public:
		Matrix();
		Matrix(int n, int m);
		Matrix(const Matrix<T>& other);
		virtual ~Matrix();

		T& operator()(int n, int m);
		const T& operator()(int n, int m) const;
		Matrix<T>& operator=(const Matrix<T>& other);

		Matrix<T> operator+(const Matrix<T>& other);
		void operator+=(const Matrix<T>& other);
		Matrix<T> operator-(const Matrix<T>& other);
		void operator-=(const Matrix<T>& other);
		Matrix<T> operator*(const Matrix<T>& other);
		void operator*=(const Matrix<T>& other);

		Matrix<T> operator+(const T& other);
		void operator+=(const T& other);
		Matrix<T> operator-(const T& other);
		void operator-=(const T& other);
		Matrix<T> operator*(const T& other);
		void operator*=(const T& other);
		Matrix<T> operator/(const T& other);
		void operator/=(const T& other);

		Vector<T> operator*(const Vector<T>& other);
		void operator*=(const Vector<T>& other);

		template<typename U>
		friend Matrix<U> operator*(const U& number, const Matrix<U>& other);

		template<typename U>
		friend std::ostream& operator<<(std::ostream& stream, const Matrix<U>& other);

	protected:
		int rows;
		int collumns;
		std::vector<T> elements;
};

template <typename T>
Matrix<T>::Matrix() : Matrix(1, 1)
{
}

template <typename T>
Matrix<T>::Matrix(int n, int m) : rows{ n }, collumns{ m }
{
	for (int i = 0; i < rows * collumns; i++)
		elements.emplace_back(T());
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
	this->elements = other.elements;
	this->rows = other.rows;
	this->collumns = other.collumns;
}

template <typename T>
Matrix<T>::~Matrix()
{
}

template <typename T>
T& Matrix<T>::operator()(int row, int col)
{
	return elements[row * collumns + col];
}

template <typename T>
const T& Matrix<T>::operator()(int row, int col) const
{
	return elements[row * collumns + col];
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
	this->rows = other.rows;
	this->collumns = other.collumns;
	this->elements = std::vector<T>(other.elements);
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other)
{
	Matrix m = *this;

	for (int i = 0; i < m.elements.size(); i++)
		m.elements.at(i) += other.elements.at(i);

	return m;
}

template <typename T>
void Matrix<T>::operator+=(const Matrix<T>& other)
{
	for (int i = 0; i < this->elements.size(); i++)
		this->elements.at(i) += other.elements.at(i);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other)
{
	Matrix m = *this;

	for (int i = 0; i < m.elements.size(); i++)
		m.elements.at(i) -= other.elements.at(i);

	return m;
}

template <typename T>
void Matrix<T>::operator-=(const Matrix<T>& other)
{
	for (int i = 0; i < this->elements.size(); i++)
		this->elements.at(i) -= other.elements.at(i);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
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
				T value = 0;

				for (int k = 0; k < (*this).collumns; k++)
					value += (*this)(i, k) * other(k, j);

				m(i, j) = value;
			}
		}

		return m;
	}
}

template <typename T>
void Matrix<T>::operator*=(const Matrix<T>& other)
{
	if (this->collumns == other.rows)
	{
		Matrix m(this->rows, other.collumns);

		for (int i = 0; i < m.rows; i++)
		{
			for (int j = 0; j < m.collumns; j++)
			{
				T value = 0;

				for (int k = 0; k < (*this).collumns; k++)
					value += (*this)(i, k) * other(k, j);

				m(i, j) = value;
			}
		}

		*this = m;
	}
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const T& other)
{
	Matrix<T> m = *this;

	for (int i = 0; i < m.elements.size(); i++)
		m.elements.at(i) += other;

	return m;
}

template <typename T>
void Matrix<T>::operator+=(const T& other)
{
	for (int i = 0; i < this->elements.size(); i++)
		this->elements.at(i) += other;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const T& other)
{
	Matrix<T> m = *this;

	for (int i = 0; i < m.elements.size(); i++)
		m.elements.at(i) -= other;

	return m;
}

template <typename T>
void Matrix<T>::operator-=(const T& other)
{
	for (int i = 0; i < this->elements.size(); i++)
		this->elements.at(i) -= other;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T& other)
{
	Matrix m = *this;

	for (T& element : m.elements)
		element *= other;

	return m;
}

template <typename T>
void Matrix<T>::operator*=(const T& other)
{
	for (T& element : this->elements)
		element *= other;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T& other)
{
	Matrix m = *this;

	for (T& element : m.elements)
		element /= other;

	return m;
}

template <typename T>
void Matrix<T>::operator/=(const T& other)
{
	for (T& element : this->elements)
		element /= other;
}

template <typename T>
Vector<T> Matrix<T>::operator*(const Vector<T>& other)
{
	Matrix<T> m(this->rows, 1);
	m(0, 0) = other.x;
	m(0, 1) = other.y;
	m(0, 2) = other.z;

	for (int i = 3; i < this->rows; i++)
		m(0, i) = 1;

	Matrix<T> n = *this * m;
	return Vector<T>(n(0, 0), n(0, 1), n(0, 2));
}

template <typename T>
void Matrix<T>::operator*=(const Vector<T>& other)
{

}

template <typename U>
Matrix<U> operator*(const U& number, const Matrix<U>& other)
{
	Matrix<U> m = other;

	for (U& element : m.elements)
		element *= number;

	return m;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Matrix<T>& other)
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

#endif
