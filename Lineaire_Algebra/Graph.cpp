#include "Graph.h"
#include "Vector.h"
#include "Graphics.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::addVector(std::unique_ptr<Vector<int>> vector)
{
	vectors.emplace_back(std::move(vector));
}

void Graph::drawVectors(const Graphics& graphics) const
{
	for (auto&& v : vectors)
		v->draw(graphics);
}
