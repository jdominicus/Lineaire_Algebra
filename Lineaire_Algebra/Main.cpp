
#define SDL_MAIN_HANDLED
#include "Graphics.h"
#include "Graph.h"
#include "Vector.h"
#include "Matrix.h"
#include "Coordinate.h"

#include <memory>

int main()
{
	auto graphics = std::make_unique<Graphics>();
	auto graph = std::make_unique<Graph>();
	auto matrix = std::make_unique<Matrix>();
	matrix->addCoordinate(std::make_unique<Coordinate>(50, 50));
	matrix->addCoordinate(std::make_unique<Coordinate>(100, 50));
	matrix->addCoordinate(std::make_unique<Coordinate>(100, 100));
	matrix->addCoordinate(std::make_unique<Coordinate>(50, 100));

	auto matrix_2 = std::make_unique<Matrix>(*matrix);

	//graph->addVector(std::make_unique<Vector>(5, 5));
	//graph->addVector(std::make_unique<Vector>(5, 10));
	//graph->addVector(std::make_unique<Vector>(10, 5));
	//graph->addVector(std::make_unique<Vector>(10, 10));

	//graph->scaleAll(10, true);
	//graph->scaleAll(10, false);
	//graph->calculateAll(*std::make_unique<Vector>(30, 30), true);
	//graph->calculateAll(*std::make_unique<Vector>(5, 5), false);
	//hierboven worden de 4 verschillende berekeningen met vectoren allemaal getest

	//matrix->scale(3, true);
	matrix->translate(-75, -75);
	auto matrix_3 = std::make_unique<Matrix>(*matrix);

	matrix->scale(3, true);
	auto matrix_4 = std::make_unique<Matrix>(*matrix);

	matrix->translate(75, 75);
	auto matrix_5 = std::make_unique<Matrix>(*matrix);

	while (true)
	{
		graphics->beforeFrame();
		graphics->clear();
		  
		graphics->drawAxis();
		//graph->drawVectors(*graphics);
		matrix->draw(*graphics);
		matrix_2->draw(*graphics, 0, 255, 0);
		matrix_3->draw(*graphics, 0, 0, 255);
		matrix_4->draw(*graphics, 0, 255, 255);
		matrix_5->draw(*graphics, 255, 255, 0);

		graphics->update();
		graphics->afterFrame();
	}

	return 0;
}
