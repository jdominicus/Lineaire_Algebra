#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}

void Matrix::addCoordinate(std::unique_ptr<Coordinate> coordinate)
{
	coordinates.emplace_back(std::move(coordinate));
}

void Matrix::scale(int s, bool multiply)
{
	for (auto& c : coordinates)
	{
		c->scale(s, multiply);
	}
}

void Matrix::translate(int hor, int ver)
{
	for (auto& c : coordinates)
	{
		c->translate(hor, ver);
	}
}

void Matrix::draw(const Graphics& graphics) const
{
	for (auto& c : coordinates)
	{
		c->draw(graphics);
	}

	coordinates[0]->getCoordinate().x;	//used for drawing lines in between
	coordinates[0]->getCoordinate().y;
}
