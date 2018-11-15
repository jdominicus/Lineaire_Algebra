
#define SDL_MAIN_HANDLED
#include "Graphics.h"
#include "Graph.h"
#include "Vector.h"
#include "Matrix.h"

#include <memory>

int main()
{
	auto graphics = std::make_unique<Graphics>();
	auto graph = std::make_unique<Graph>();
	auto matrix = std::make_unique<::Matrix>();

	matrix->addVector(std::make_unique<Vector>(5, 5));
	matrix->addVector(std::make_unique<Vector>(5, 10));
	matrix->addVector(std::make_unique<Vector>(10, 5));
	matrix->addVector(std::make_unique<Vector>(10, 10));

	//graph->scaleAll(10, true);
	//graph->scaleAll(10, false);
	//graph->calculateAll(*std::make_unique<Vector>(5, 5), true);
	//graph->calculateAll(*std::make_unique<Vector>(5, 5), false);
	//hierboven worden de 4 verschillende berekeningen met vectoren allemaal getest

	while (true)
	{
		graphics->beforeFrame();

		graphics->clear();
		//graph->draw(*graphics);
		graphics->drawAxis();
		graph->drawVectors(*graphics);
		graphics->update();

		graphics->afterFrame();
	}

	return 0;
}
