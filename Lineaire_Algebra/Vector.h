#pragma once
#include "Graphics.h"
class Matrix;

class Vector
{
	public:
		Vector(float x, float y, float z);
		Vector(const Vector& other);
		Vector(const Matrix& other);
		
	private:
		float x;
		float y;
		float z;

		friend class Matrix;

	public:
		Vector& operator=(const Vector& other);

		Vector operator+(const Vector& other);
		void operator+=(const Vector& other);
		Vector operator-(const Vector& other);
		void operator-=(const Vector& other);
		Vector operator*(const float& other);
		void operator*=(const float& other);
		Vector operator/(const float& other);
		void operator/=(const float& other);

		//friend Vector operator*(const float& number, const Vector& other);
		friend std::ostream& operator<<(std::ostream& stream, Vector& other);

		void draw(const Graphics& graphics) const;
		const float& getX() const;
		const float& getY() const;
		const float& getZ() const;
};