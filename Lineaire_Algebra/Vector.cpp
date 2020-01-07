#include "Vector.h"
#include "Matrix.h"

Vector::Vector(double x, double y, double z) : x{ x }, y{ y }, z{ z }
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

Vector Vector::crossProduct(const Vector& other)
{
	double x_new = y * other.z - z * other.y;
	double y_new = z * other.x - x * other.z;
	double z_new = x * other.y - y * other.x;
	return Vector(x_new, y_new, z_new);
}

double Vector::dotProduct(const Vector& other)
{
	return x * other.x + y * other.y + z * other.z;
}

double Vector::magnitude() const
{
	return sqrt((pow(x, 2) + pow(y,2) + pow(z,2)));
}

double Vector::length() const
{
	return sqrt(x * x + y * y + z * z);
}

void Vector::normalize()
{
	const double vLength = length();

	x /= vLength;
	y /= vLength;
	z /= vLength;
}

double Vector::angle(const Vector& other)
{
	return (dotProduct(other) / (magnitude() * other.magnitude()));
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

Vector Vector::operator*(const double& other)
{
	Vector v = *this;
	v.x *= other;
	v.y *= other;
	v.z *= other;
	return v;
}

void Vector::operator*=(const double& other)
{
	x *= other;
	y *= other;
	z *= other;
}

Vector Vector::operator/(const double& other)
{
	Vector v = *this;
	v.x /= other;
	v.y /= other;
	v.z /= other;
	return v;
}

void Vector::operator/=(const double& other)
{
	x /= other;
	y /= other;
	z /= other;
}

//Vector operator*(const double& number, Vector& other)
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

const double& Vector::getX() const
{
	return x;
}

const double& Vector::getY() const
{
	return y;
}

const double& Vector::getZ() const
{
	return z;
}