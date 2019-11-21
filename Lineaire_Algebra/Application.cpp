#include "Application.h"
#include "Graphics.h"
#include "EventManager.h"
#include "Graph.h"
#include "Vector.h"
#include "Matrix.h"
#include "Camera.h"
#include "Shape.h"
#include "KeyEvent.h"

Application::Application() : running{ true }
{
	eventManager = std::make_unique<EventManager>();
	graphics = std::make_unique<Graphics>();
	camera_ = std::make_unique<Camera<double>>();
	eventManager->addApplicationListener(this);
	eventManager->addKeyListener(this);

	graph = std::make_unique<Graph>();

	s1 = std::make_unique<Shape<double>>();
	s1->addVector(std::make_unique<Vector<double>>(50, 50, 50));
	s1->addVector(std::make_unique<Vector<double>>(100, 50, 50));
	s1->addVector(std::make_unique<Vector<double>>(100, 50, 100));
	s1->addVector(std::make_unique<Vector<double>>(50, 50, 100));
	s1->addVector(std::make_unique<Vector<double>>(75, 100, 75));
	s1->addConnection(0, 1);
	s1->addConnection(1, 2);
	s1->addConnection(2, 3);
	s1->addConnection(3, 0);
	s1->addConnection(0, 4);
	s1->addConnection(1, 4);
	s1->addConnection(2, 4);
	s1->addConnection(3, 4);
	s1->setReferencePoint();
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
	graphics->drawAxis(*camera_);
	s1->draw(*camera_, *graphics);
}

void Application::update()
{

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
			//s1->rotateFromOrigin(2 * pi / 30);
			break;
		case KeyEvent::Right:
			//s1->rotateFromOrigin(-2 * pi / 30);
			break;
		case KeyEvent::A:
			camera_.get()->goLeft();
			break;
		case KeyEvent::W:
			camera_.get()->goUp();
			break;
		case KeyEvent::S:
			camera_.get()->goDown();
			break;
		case KeyEvent::D:
			camera_.get()->goRight();
			break;
		case KeyEvent::F1:
			s1->rotateAroundPoint(2 * pi / 16, 'Y', *(std::make_unique<Vector<double>>(0, 0, 0)));
			break;
		case KeyEvent::F2:
			s1->rotateAroundPoint(-2 * pi / 16, 'Y', *(std::make_unique<Vector<double>>(0, 0, 0)));
			break;
		case KeyEvent::F3:
			s1->rotateInPlace(2 * pi / 16, 'Z');
			break;
		case KeyEvent::F4:
			s1->rotateInPlace(-2 * pi / 16, 'Z');
			break;
		case KeyEvent::F5:
			s1->scaleFromPoint(2, 2, 2, *(std::make_unique<Vector<double>>(250, 250, 250)));
			break;
		case KeyEvent::F6:
			s1->scaleFromPoint(0.5f, 0.5f, 0.5f, *(std::make_unique<Vector<double>>(250, 250, 250)));
			break;
	}
}

void Application::onKeyUp(KeyEvent& keyEvent)
{

}
