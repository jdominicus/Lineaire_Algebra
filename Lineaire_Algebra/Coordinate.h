#pragma once

#include "Graphics.h"

struct punt
{
	int x, y;
};

class Coordinate
{
	public:
		Coordinate(int x, int y);
		~Coordinate();

	private:
		int x, y;
		int xSpawn, ySpawn;
		int degrees;

	public:
		punt getCoordinate();
		void scale(int x, bool multiply);
		void translate(int hor, int ver);
		void rotate(int degrees);
		double degreesToRadians(int degrees);
};

