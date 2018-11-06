#pragma once
#include "Graphics.h"

class Vector
{
	public:
		Vector(double direction, double length);
		~Vector();

	private:
		double length;
		double direction;

	public:
		void scale(int x, bool multiply);			//bool true = multiply, false = divide
		void calculate(Vector& vector, bool add);	//bool true = add, false = substract
		void draw(const Graphics& graphics) const;
};

