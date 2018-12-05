#pragma once

#include "Graphics.h"

template<typename U>
class Matrix;

template <typename T>
class Vector
{
	public:
		Vector(T length, T direction);
		Vector(const Vector<T>& other);
		Vector(const Matrix<T>& other);
		
	private:
		T length;
		T direction;

		template <typename>
		friend class Matrix;

	public:
		Vector<T>& operator=(const Vector<T>& other);

		Vector<T> operator+(const Vector<T>& other);
		void operator+=(const Vector<T>& other);
		Vector<T> operator-(const Vector<T>& other);
		void operator-=(const Vector<T>& other);
		Vector<T> operator*(const T& other);
		void operator*=(const T& other);
		Vector<T> operator/(const T& other);
		void operator/=(const T& other);

		template<typename U>
		friend Vector<U> operator*(const U& number, const Vector<U>& other);

		template<typename U>
		friend std::ostream& operator<<(std::ostream& stream, const Vector<U>& other);

		void draw(const Graphics& graphics) const;
		const T& getLenght() const;
		const T& getDirection() const;
};

template<typename T>
Vector<T>::Vector(T length, T direction) : length{ length }, direction{ direction }
{
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	this->direction = other.direction;
	this->length = other.length;
}

template<typename T>
Vector<T>::Vector(const Matrix<T>& other)
{
	if (other.rows > 2)
	{
		this->length = other(0, 0);
		this->direction = other(1, 0);
	}
	else
	{
		this->lenght = 0;
		this->direction = 0;
	}
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	this->length = other.length;
	this->direction = other.direction;
	return *this;
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other)
{
	Vector v = *this;
	v.length += other.length;
	v.direction += other.direction;
	return v;
}

template<typename T>
void Vector<T>::operator+=(const Vector<T>& other)
{
	length += other.length;
	direction += other.direction;
}

template<typename T>
Vector<T> Vector<T>::operator-(const Vector<T>& other)
{
	Vector v = *this;
	v.length -= other.length;
	v.direction -= other.direction;
	return v;
}

template<typename T>
void Vector<T>::operator-=(const Vector<T>& other)
{
	length -= other.length;
	direction -= other.direction;
}

template<typename T>
Vector<T> Vector<T>::operator*(const T& other)
{
	Vector v = *this;
	v.length *= other;
	v.direction *= other;
	return v;
}

template<typename T>
void Vector<T>::operator*=(const T& other)
{
	length *= other;
	direction *= other;
}

template<typename T>
Vector<T> Vector<T>::operator/(const T& other)
{
	Vector v = *this;
	v.length /= other;
	v.direction /= other;
	return v;
}

template<typename T>
void Vector<T>::operator/=(const T& other)
{
	length /= other;
	direction /= other;
}

template<typename T>
Vector<T> operator*(const T& number, const Vector<T>& other)
{
	other.length *= number;
	other.direction *= number;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Vector<T>& other)
{
	stream << other.length << " " << other.direction;
	return stream;
}

template<typename T>
void Vector<T>::draw(const Graphics& graphics) const
{
	graphics.drawVector((int)length, (int)direction);
}

template<typename T>
const T& Vector<T>::getLenght() const
{
	return length;
}

template<typename T>
const T& Vector<T>::getDirection() const
{
	return direction;
}



