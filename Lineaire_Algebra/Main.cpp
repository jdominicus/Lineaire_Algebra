
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

	graph->addVector(std::make_unique<Vector>(100, 5));
	graph->addVector(std::make_unique<Vector>(20, -3));
	graph->addVector(std::make_unique<Vector>(-5, 50));
	graph->addVector(std::make_unique<Vector>(-30, -30));

	//graph->scaleAll(10, true);
	//graph->scaleAll(10, false);
	//graph->calculateAll(*std::make_unique<Vector>(30, 30), true);
	//graph->calculateAll(*std::make_unique<Vector>(5, 5), false);
	//hierboven worden de 4 verschillende berekeningen met vectoren allemaal getest

	while (true)
	{
		graphics->beforeFrame();

		graphics->clear();
		graphics->drawAxis();
		graph->drawVectors(*graphics);
		graphics->update();

		graphics->afterFrame();
	}

	return 0;
}
