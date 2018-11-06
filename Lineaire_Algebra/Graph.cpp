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

void Graph::draw(const Graphics& graphics)
{
	graphics.drawRect(0, 0, 100, 100);
	graphics.drawRect(100, 100, 100, 100);
	graphics.drawRect(200, 200, 100, 100);
	graphics.drawRect(300, 300, 100, 100);
	graphics.drawRect(400, 400, 100, 100);
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
