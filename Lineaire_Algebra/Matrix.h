#pragma once
#include <iostream>
#include <vector>
class Vector;

class Matrix
{
	friend class Vector;

	public:
		Matrix();
		Matrix(int n, int m);
		Matrix(const Matrix& other);
		virtual ~Matrix();

		double& operator()(int n, int m);
		const double& operator()(int n, int m) const;
		Matrix& operator=(const Matrix& other);

		Matrix operator+(const Matrix& other);
		void operator+=(const Matrix& other);
		Matrix operator-(const Matrix& other);
		void operator-=(const Matrix& other);
		Matrix operator*(const Matrix& other);
		void operator*=(const Matrix& other);

		Matrix operator+(const double& other);
		void operator+=(const double& other);
		Matrix operator-(const double& other);
		void operator-=(const double& other);
		Matrix operator*(const double& other);
		void operator*=(const double& other);
		Matrix operator/(const double& other);
		void operator/=(const double& other);

		Vector operator*(const Vector& other);

		friend Matrix operator*(const double& number, const Matrix& other);
		friend std::ostream& operator<<(std::ostream& stream, const Matrix& other);

	protected:
		int rows;
		int collumns;
		std::vector<double> elements;
};