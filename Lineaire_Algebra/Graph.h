#pragma once

#include <vector>
#include <memory>

class Graphics;
class Vector;

class Graph
{
	public:
		Graph();
		~Graph();

	private:
		std::vector<std::unique_ptr<Vector>> vectors;

	public:
		void addVector(std::unique_ptr<Vector>vector);
		void drawVectors(const Graphics& graphics) const;
};

