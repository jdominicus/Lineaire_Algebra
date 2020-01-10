#pragma once
#include "Graphics.h"
class Matrix;

class Vector
{
	public:
		Vector(double x, double y, double z);
		Vector();
		Vector(const Vector& other);
		Vector(const Matrix& other);
		
	private:
		double x_;
		double y_;
		double z_;

		friend class Matrix;

	public:
		Vector& operator=(const Vector& other);

		Vector crossProduct(const Vector& other);
		double dotProduct(const Vector& other);
		double magnitude() const;
		double angle(const Vector& other);
		void normalize();

		Vector operator+(const Vector& other);
		void operator+=(const Vector& other);
		Vector operator-(const Vector& other);
		void operator-=(const Vector& other);
		Vector operator*(const double& other);
		void operator*=(const double& other);
		Vector operator/(const double& other);
		void operator/=(const double& other);

		//friend Vector operator*(const double& number, const Vector& other);
		friend std::ostream& operator<<(std::ostream& stream, Vector& other);

		void draw(const Graphics& graphics) const;
		const double& getX() const;
		const double& getY() const;
		const double& getZ() const;
		void setX(double x) { x_ = x; };
		void setY(double y) { y_ = y; };
		void setZ(double z) { z_ = z; };
};