#include "Vector.h"

Vector::Vector(double length, double direction) : length {length}, direction {direction}
{
}

Vector::~Vector()
{
}

void Vector::scale(int x, bool multiply)
{
	if (multiply)
	{
		length *= x;
		direction *= x;
	}
	else if (x != 0)
	{
		length /= x;
		direction /= x;
	}
}

void Vector::calculate(Vector& vector, bool add)
{
	if (add)
	{
		length += vector.length;
		direction += vector.direction;
	}
	else
	{
		length -= vector.length;
		direction -= vector.direction;
	}
}

void Vector::draw(const Graphics& graphics) const
{
	graphics.drawVector(length, direction);
	//draw starting point or arrowtips
}
