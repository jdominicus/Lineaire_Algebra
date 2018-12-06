#include "Application.h"
#include "Graphics.h"
#include "EventManager.h"
#include "Graph.h"
#include "Vector.h"
#include "Matrix.h"
#include "Shape.h"
#include "KeyEvent.h"

Application::Application() : running{ true }
{
	eventManager = std::make_unique<EventManager>();
	graphics = std::make_unique<Graphics>();
	eventManager->addApplicationListener(this);
	eventManager->addKeyListener(this);

	graph = std::make_unique<Graph>();
	matrix = std::make_unique<Matrix<int>>();

	s1 = std::make_unique<Shape<float>>();
	s1->addVector(std::make_unique<Vector<float>>(50, 50, 50));
	s1->addVector(std::make_unique<Vector<float>>(100, 50, 50));
	s1->addVector(std::make_unique<Vector<float>>(100, 50, 100));
	s1->addVector(std::make_unique<Vector<float>>(50, 50, 100));
	s1->addVector(std::make_unique<Vector<float>>(75, 100, 75));
	s1->addConnection(0, 1);
	s1->addConnection(1, 2);
	s1->addConnection(2, 3);
	s1->addConnection(3, 0);
	s1->addConnection(0, 4);
	s1->addConnection(1, 4);
	s1->addConnection(2, 4);
	s1->addConnection(3, 4);

	Matrix<int> translation(4, 4);
	translation(0, 0) = 1;
	translation(1, 1) = 1;
	translation(2, 2) = 1;
	translation(3, 3) = 1;
	translation(0, 2) = -75;
	translation(1, 2) = -75;
	translation(2, 2) = -75;

	Matrix<int> scale(4, 4);
	scale(0, 0) = 2;
	scale(1, 1) = 2;
	scale(2, 2) = 2;
	scale(3, 3) = 1;

	Matrix<int> translation2(4, 4);
	translation2(0, 0) = 1;
	translation2(1, 1) = 1;
	translation2(2, 2) = 1;
	translation2(3, 3) = 1;
	translation2(0, 2) = 75;
	translation2(1, 2) = 75;
	translation2(2, 2) = 75;

	std::cout << translation << std::endl;
	std::cout << scale << std::endl;
	std::cout << translation2 << std::endl;
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
	s1->printMidPoint();
}

void Application::onKeyDown(KeyEvent& keyEvent)
{
	switch (keyEvent.key())
	{
		case KeyEvent::Space:
			graphics->changeView(); break;
		case KeyEvent::Up:
			s1->scaleInPlace(2, 2, 2); break;
		case KeyEvent::Down:
			s1->scaleInPlace(0.5f, 0.5f, 0.5f); break;
		case KeyEvent::Left:
			s1->translate(50, 0, 50); break;
		case KeyEvent::Right:
			s1->translate(-50, 0, -50); break;
	}
}

void Application::onKeyUp(KeyEvent& keyEvent)
{

}
