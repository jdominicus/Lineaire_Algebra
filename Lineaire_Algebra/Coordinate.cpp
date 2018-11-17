#include "Coordinate.h"

Coordinate::Coordinate(int x, int y) : x{x}, y{y}
{
}

Coordinate::~Coordinate()
{
}

punt Coordinate::getCoordinate()
{
	return punt{ x, y };
}

void Coordinate::scale(int s, bool multiply)
{
	if (multiply)
	{
		x *= s;
		y *= s;
	}
	else if (x != 0)
	{
		x /= s;
		y /= s;
	}
}

void Coordinate::translate(int hor, int ver)
{
	x += hor;
	y += ver;
}
