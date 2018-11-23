#include "Application.h"
#include "Graphics.h"
#include "EventManager.h"
#include "Graph.h"
#include "Vector.h"
#include "Matrix.h"
#include "Coordinate.h"

Application::Application() : running{ true }
{
	eventManager = std::make_unique<EventManager>();
	graphics = std::make_unique<Graphics>();
	eventManager->addApplicationListener(this);

	graph = std::make_unique<Graph>();
	matrix = std::make_unique<Matrix>();

	matrix->addCoordinate(std::make_unique<Coordinate>(50, 50));
	matrix->addCoordinate(std::make_unique<Coordinate>(100, 50));
	matrix->addCoordinate(std::make_unique<Coordinate>(100, 100));
	matrix->addCoordinate(std::make_unique<Coordinate>(50, 100));

	matrix_2 = std::make_unique<Matrix>(*matrix);
	matrix_3 = std::make_unique<Matrix>(*matrix);
	matrix_4 = std::make_unique<Matrix>(*matrix);
	matrix_5 = std::make_unique<Matrix>(*matrix);

	matrix->translate(-75, -75);

	matrix_2->translate(-75, -75);
	matrix_2->rotate(45);

	matrix_3->translate(-75, -75);
	matrix_3->rotate(45);
	matrix_3->scale(3);
	matrix_3->translate(75, 75);
	

	//matrix_4->translate(75, 75);
	//matrix->translate(75, 75);
}

Application::~Application()
{
}

void Application::start()
{
	while (running)
	{
		graphics->beforeFrame();
		graphics->clear();

		update();
		render();

		graphics->update();
		graphics->afterFrame();

		eventManager->handleEvents();
	}
}

void Application::quit()
{
	running = false;
}

void Application::render()
{
	graphics->drawAxis();
	matrix->draw(*graphics);
	matrix_2->draw(*graphics, 0, 255, 0);
	matrix_3->draw(*graphics, 0, 0, 255);
	matrix_4->draw(*graphics, 0, 255, 255);
	matrix_5->draw(*graphics, 255, 255, 0);
}

void Application::update()
{
	//matrix_2->rotate(1);
	matrix_3->rotate(1);
}
