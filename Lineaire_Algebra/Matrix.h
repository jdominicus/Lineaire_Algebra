#pragma once

#include <vector>
#include <memory>

class Coordinate;
class Graphics;

class Matrix
{
	public:
		Matrix();
		~Matrix();
		Matrix(const Matrix& other);

	private:
		std::vector<std::unique_ptr<Coordinate>> coordinates;

	public:
		void addCoordinate(std::unique_ptr<Coordinate> coordinate);
		void scale(int x, bool multiply = true);
		void translate(int hor, int ver);
		void rotate(int degrees);
		void draw(const Graphics& graphics, int r = 255, int g = 255, int b = 255) const;
};