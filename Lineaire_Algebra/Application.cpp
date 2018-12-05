#include "Application.h"
#include "Graphics.h"
#include "EventManager.h"
#include "Graph.h"
#include "Vector.h"
#include "Matrix.h"
#include "Shape.h"

Application::Application() : running{ true }
{
	eventManager = std::make_unique<EventManager>();
	graphics = std::make_unique<Graphics>();
	eventManager->addApplicationListener(this);

	graph = std::make_unique<Graph>();
	matrix = std::make_unique<Matrix<int>>();

	s1 = std::make_unique<Shape<float>>();

	s1->addVector(std::make_unique<Vector<float>>(50, 50));
	s1->addVector(std::make_unique<Vector<float>>(50, 100));
	s1->addVector(std::make_unique<Vector<float>>(100, 100));
	s1->addVector(std::make_unique<Vector<float>>(100, 50));
	s1->addConnection(0, 1);
	s1->addConnection(1, 2);
	s1->addConnection(2, 3);
	s1->addConnection(3, 0);

	s1->scaleInPlace(3, 3);
	s1->scaleInPlace(0.333f, 0.333f);
	s1->scaleInPlace(3, 3);
	s1->rotate(3.1415 / 4);
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
	s1->draw(*graphics);
}

void Application::update()
{
	s1->rotate(3.141592 / 100);
}
