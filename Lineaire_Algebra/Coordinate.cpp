#include "Coordinate.h"

Coordinate::Coordinate(int x, int y) : x{ x }, y{ y }, xSpawn{ x }, ySpawn{ y }, degrees{ 0 }
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

	xSpawn += hor;
	ySpawn += ver;
}

void Coordinate::rotate(int degrees)
{
	this->degrees += degrees;
	if (this->degrees >= 360)
		this->degrees -= 360;

	double radians = degreesToRadians(this->degrees);

	int newX = round(xSpawn * cos(radians) - ySpawn * sin(radians));
	int newY = round(ySpawn * cos(radians) + xSpawn * sin(radians));

	x = newX;
	y = newY;
}

double Coordinate::degreesToRadians(int degrees)
{
	double degrees_ = static_cast<double>(degrees);
	return degrees_ / 180 * 3.14159265359;
}
