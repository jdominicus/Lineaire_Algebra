#include "Matrix.h"
#include "Coordinate.h"
#include "Graphics.h"

Matrix::Matrix()
{
	for (int i = 0; i < 5; i++)
	{
		std::vector<Coordinate*> row;

		for (int j = 0; j < 3; j++)
		{
			Coordinate* c = new Coordinate(2, 5);
			row.push_back(c);
		}

		matrix.push_back(row);
	}
}

Matrix::~Matrix()
{
}

Matrix::Matrix(const Matrix& other)
{
	for (auto& c : other.coordinates)
		coordinates.emplace_back(std::make_unique<Coordinate>(c->getCoordinate().x, c->getCoordinate().y));

	for (auto& row : other.matrix)
	{
		for (auto& c : row)
		{
			
		}
	}
}

Matrix& Matrix::operator*(int other)
{
	for (std::vector<Coordinate*> row : matrix)
	{
		for (Coordinate* coordinate : row)
		{
			coordinate->changeCoordinates(coordinate->getCoordinate().x * other, coordinate->getCoordinate().y * other);
		}
	}

	return *this;
}

Matrix& Matrix::operator=(Matrix& other)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			matrix.at(i).at(j) = new Coordinate(other.matrix.at(i).at(j)->getCoordinate().x, other.matrix.at(i).at(j)->getCoordinate().y);
		}
	}

	return *this;
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
