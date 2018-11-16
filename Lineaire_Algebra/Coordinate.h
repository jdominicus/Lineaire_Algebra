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

	public:
		punt getCoordinate();
		void scale(int x, bool multiply);
		void translate(int hor, int ver);
		void draw(const Graphics& graphics) const;
};

