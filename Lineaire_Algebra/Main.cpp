
#define SDL_MAIN_HANDLED
#include "Graphics.h"
#include "Graph.h"
#include "Vector.h"

#include <iostream>
#include <memory>

int main()
{
	auto graphics = std::make_unique<Graphics>();
	auto graph = std::make_unique<Graph>();

	graph->addVector(std::make_unique<Vector>());

	while (true)
	{
		graphics->beforeFrame();

		graphics->clear();
		graph->draw(*graphics);
		graphics->update();

		graphics->afterFrame();
	}

	return 0;
}
