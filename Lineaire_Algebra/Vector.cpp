#include "Vector.h"
#include "Matrix.h"

Vector::Vector(float x, float y, float z) : x{ x }, y{ y }, z{ z }
{
}

Vector::Vector(const Vector& other)
{
	y = other.y;
	x = other.x;
	z = other.z;
}

Vector::Vector(const Matrix& other)
{
	x = other(0, 0);
	y = other(1, 0);
	z = other(2, 0);
}

Vector& Vector::operator=(const Vector& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Vector Vector::operator+(const Vector& other)
{
	Vector v = *this;
	v.x += other.x;
	v.y += other.y;
	v.z += other.z;
	return v;
}

void Vector::operator+=(const Vector& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

Vector Vector::operator-(const Vector& other)
{
	Vector v = *this;
	v.x -= other.x;
	v.y -= other.y;
	v.z -= other.z;
	return v;
}

void Vector::operator-=(const Vector& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

Vector Vector::operator*(const float& other)
{
	Vector v = *this;
	v.x *= other;
	v.y *= other;
	v.z *= other;
	return v;
}

void Vector::operator*=(const float& other)
{
	x *= other;
	y *= other;
	z *= other;
}

Vector Vector::operator/(const float& other)
{
	Vector v = *this;
	v.x /= other;
	v.y /= other;
	v.z /= other;
	return v;
}

void Vector::operator/=(const float& other)
{
	x /= other;
	y /= other;
	z /= other;
}

//Vector operator*(const float& number, Vector& other)
//{
//	return Vector(other.x * number, other.y * number, other.z * number);
//}

std::ostream& operator<<(std::ostream& stream, Vector& other)
{
	stream << other.x << " " << other.y << " " << other.z;
	return stream;
}

void Vector::draw(const Graphics& graphics) const
{
	graphics.drawVector((int)x, (int)y, (int)z);
}

const float& Vector::getX() const
{
	return x;
}

const float& Vector::getY() const
{
	return y;
}

const float& Vector::getZ() const
{
	return z;
}