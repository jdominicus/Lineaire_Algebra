#include "Matrix.h"
#include "Coordinate.h"
#include "Graphics.h"

Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}

Matrix::Matrix(const Matrix& other)
{
	for (auto& c : other.coordinates)
		coordinates.emplace_back(std::make_unique<Coordinate>(c->getCoordinate().x, c->getCoordinate().y));
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

void Matrix::rotate(int degrees)
{
	for (auto& c : coordinates)
	{
		c->rotate(degrees);
	}
}

void Matrix::draw(const Graphics& graphics, int r, int g, int b) const
{
	Coordinate* pC = nullptr;
	Coordinate* sC = nullptr;

	for (auto& c : coordinates)
	{
		if (pC == nullptr)
		{
			sC = pC = c.get();
		}
		else
		{
			graphics.drawLine(pC->getCoordinate().x, pC->getCoordinate().y, c->getCoordinate().x, c->getCoordinate().y, r, g, b);
			pC = c.get();
		}
	}

	graphics.drawLine(pC->getCoordinate().x, pC->getCoordinate().y, sC->getCoordinate().x, sC->getCoordinate().y, r, g, b);
}
