#pragma once

#include "Graphics.h"

template<typename U>
class Matrix;

template <typename T>
class Vector
{
	public:
		Vector(T x, T y, T z);
		Vector(const Vector<T>& other);
		Vector(const Matrix<T>& other);
		
	private:
		T x;
		T y;
		T z;

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
		const T& getX() const;
		const T& getY() const;
		const T& getZ() const;
};

template<typename T>
Vector<T>::Vector(T x, T y, T z) : x{ x }, y{ y }, z{ z }
{
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	y = other.y;
	x = other.x;
	z = other.z;
}

template<typename T>
Vector<T>::Vector(const Matrix<T>& other)
{
	x = other(0, 0);
	y = other(1, 0);
	z = other(2, 0);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other)
{
	Vector v = *this;
	v.x += other.x;
	v.y += other.y;
	v.z += other.z;
	return v;
}

template<typename T>
void Vector<T>::operator+=(const Vector<T>& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

template<typename T>
Vector<T> Vector<T>::operator-(const Vector<T>& other)
{
	Vector v = *this;
	v.x -= other.x;
	v.y -= other.y;
	v.z -= other.z;
	return v;
}

template<typename T>
void Vector<T>::operator-=(const Vector<T>& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

template<typename T>
Vector<T> Vector<T>::operator*(const T& other)
{
	Vector v = *this;
	v.x *= other;
	v.y *= other;
	v.z *= other;
	return v;
}

template<typename T>
void Vector<T>::operator*=(const T& other)
{
	x *= other;
	y *= other;
	z *= other;
}

template<typename T>
Vector<T> Vector<T>::operator/(const T& other)
{
	Vector v = *this;
	v.x /= other;
	v.y /= other;
	v.z /= other;
	return v;
}

template<typename T>
void Vector<T>::operator/=(const T& other)
{
	x /= other;
	y /= other;
	z /= other;
}

template<typename T>
Vector<T> operator*(const T& number, const Vector<T>& other)
{
	other.x *= number;
	other.y *= number;
	other.z *= number;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Vector<T>& other)
{
	stream << other.x << " " << other.y << " " << other.z;
	return stream;
}

template<typename T>
void Vector<T>::draw(const Graphics& graphics) const
{
	graphics.drawVector((int)x, (int)y, (int)z);
}

template<typename T>
const T& Vector<T>::getX() const
{
	return x;
}

template<typename T>
const T& Vector<T>::getY() const
{
	return y;
}

template<typename T>
const T& Vector<T>::getZ() const
{
	return z;
}



