#pragma once

#include <vector>
#include <memory>

class Graphics;

template <typename T>
class Vector;

class Graph
{
	public:
		Graph();
		~Graph();

	private:
		std::vector<std::unique_ptr<Vector<int>>> vectors;

	public:
		void addVector(std::unique_ptr<Vector<int>> vector);
		void drawVectors(const Graphics& graphics) const;
};

