
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

	//graph->addVector(std::make_unique<Vector>(5, 5));
	//graph->addVector(std::make_unique<Vector>(5, 10));
	//graph->addVector(std::make_unique<Vector>(10, 5));
	//graph->addVector(std::make_unique<Vector>(10, 10));

	//graph->scaleAll(10, true);
	//graph->scaleAll(10, false);
	//graph->calculateAll(*std::make_unique<Vector>(30, 30), true);
	//graph->calculateAll(*std::make_unique<Vector>(5, 5), false);
	//hierboven worden de 4 verschillende berekeningen met vectoren allemaal getest

	matrix->addCoordinate(std::make_unique<Coordinate>(5, 5));
	matrix->addCoordinate(std::make_unique<Coordinate>(5, 30));
	matrix->addCoordinate(std::make_unique<Coordinate>(30, 5));
	matrix->addCoordinate(std::make_unique<Coordinate>(30, 30));

	//matrix->scale(3, true);
	matrix->translate(-5, -5);
	matrix->scale(5, true);
	matrix->translate(5, 5);

	while (true)
	{
		graphics->beforeFrame();

		graphics->clear();
		graphics->drawAxis();
		//graph->drawVectors(*graphics);
		matrix->draw(*graphics);
		graphics->update();

		graphics->afterFrame();
	}

	return 0;
}
