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
};

