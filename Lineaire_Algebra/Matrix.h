#pragma once

#include <vector>
#include "Coordinate.h"
#include <memory>

class Matrix
{
public:
	Matrix();
	~Matrix();

private:
	std::vector<std::unique_ptr<Coordinate>> coordinates;

public:
	void addCoordinate(std::unique_ptr<Coordinate> coordinate);
	void scale(int x, bool multiply);
	void translate(int hor, int ver);
	void draw(const Graphics& graphics) const;
};