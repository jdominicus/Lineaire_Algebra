#include "Vector.h"
#include "Matrix.h"

Vector::Vector(double x, double y, double z) : x_{ x }, y_{ y }, z_{ z }
{
}

Vector::Vector() : Vector(0, 0, 0)
{
}

Vector::Vector(const Vector& other)
{
	y_ = other.y_;
	x_ = other.x_;
	z_ = other.z_;
}

Vector::Vector(const Matrix& other)
{
	x_ = other(0, 0);
	y_ = other(1, 0);
	z_ = other(2, 0);
}

Vector& Vector::operator=(const Vector& other)
{
	x_ = other.x_;
	y_ = other.y_;
	z_ = other.z_;
	return *this;
}

Vector Vector::crossProduct(const Vector& other)
{
	double x = y_ * other.z_ - z_ * other.y_;
	double y = z_ * other.x_ - x_ * other.z_;
	double z = x_ * other.y_ - y_ * other.x_;
	return Vector(x, y, z);
}

double Vector::dotProduct(const Vector& other)
{
	return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
}

double Vector::magnitude() const
{
	return sqrt((pow(x_, 2) + pow(y_,2) + pow(z_,2)));
}

double Vector::angle(const Vector& other)
{
	return (dotProduct(other) / (magnitude() * other.magnitude()));
}

void Vector::normalize()
{
	const double vLength = magnitude();

	x_ /= vLength;
	y_ /= vLength;
	z_ /= vLength;
}

Vector Vector::operator+(const Vector& other)
{
	Vector v = *this;
	v.x_ += other.x_;
	v.y_ += other.y_;
	v.z_ += other.z_;
	return v;
}

void Vector::operator+=(const Vector& other)
{
	x_ += other.x_;
	y_ += other.y_;
	z_ += other.z_;
}

Vector Vector::operator-(const Vector& other)
{
	Vector v = *this;
	v.x_ -= other.x_;
	v.y_ -= other.y_;
	v.z_ -= other.z_;
	return v;
}

void Vector::operator-=(const Vector& other)
{
	x_ -= other.x_;
	y_ -= other.y_;
	z_ -= other.z_;
}

Vector Vector::operator*(const double& other)
{
	Vector v = *this;
	v.x_ *= other;
	v.y_ *= other;
	v.z_ *= other;
	return v;
}

void Vector::operator*=(const double& other)
{
	x_ *= other;
	y_ *= other;
	z_ *= other;
}

Vector Vector::operator/(const double& other)
{
	Vector v = *this;
	v.x_ /= other;
	v.y_ /= other;
	v.z_ /= other;
	return v;
}

void Vector::operator/=(const double& other)
{
	x_ /= other;
	y_ /= other;
	z_ /= other;
}

//Vector operator*(const double& number, Vector& other)
//{
//	return Vector(other.x * number, other.y * number, other.z * number);
//}

std::ostream& operator<<(std::ostream& stream, Vector& other)
{
	stream << other.x_ << " " << other.y_ << " " << other.z_;
	return stream;
}

void Vector::draw(const Graphics& graphics) const
{
	graphics.drawVector((int)x_, (int)y_, (int)z_);
}

const double& Vector::getX() const
{
	return x_;
}

const double& Vector::getY() const
{
	return y_;
}

const double& Vector::getZ() const
{
	return z_;
}