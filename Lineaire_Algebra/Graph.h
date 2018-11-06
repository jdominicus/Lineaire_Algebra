#pragma once

#include <vector>
#include <memory>

class Vector;
class Graphics;

class Graph
{
	public:
		Graph();
		~Graph();

	private:
		std::vector<std::unique_ptr<Vector>> vectors;

	public:
		void addVector(std::unique_ptr<Vector> vector);
		void draw(const Graphics& graphics);
		void drawVectors(const Graphics& graphics) const;
		void scaleAll(int x, bool multiply);
		void calculateAll(Vector& vector, bool add);
};

