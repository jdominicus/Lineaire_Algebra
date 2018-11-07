#include "Graph.h"
#include "Vector.h"
#include "Graphics.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::addVector(std::unique_ptr<Vector> vector)
{
	vectors.emplace_back(std::move(vector));
}

void Graph::drawVectors(const Graphics& graphics) const
{
	for (auto& v : vectors)
	{
		v->draw(graphics);
	}
}

void Graph::scaleAll(int x, bool multiply)
{
	for (auto& v : vectors)
	{
		v->scale(x, multiply);
	}
}

void Graph::calculateAll(Vector & vector, bool add)
{
	for (auto& v : vectors)
	{
		v->calculate(vector, add);
	}
}
