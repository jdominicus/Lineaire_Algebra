#include "Application.h"
#include "Graphics.h"
#include "EventManager.h"
#include "Graph.h"
#include "Vector.h"
#include "Matrix.h"
#include "Shape.h"
#include "KeyEvent.h"
#include "Planet.h"
#include "Ship.h"
#include <chrono>

Application::Application() : running{ true }
{
	eventManager = std::make_unique<EventManager>();
	graphics = std::make_unique<Graphics>();
	eventManager->addApplicationListener(this);
	eventManager->addKeyListener(this);

	graph = std::make_unique<Graph>();
	planet_ = std::make_unique<Planet>();
	ship_ = std::make_unique<Ship>();

	Vector v1(2, 3, 4);
	Vector v2(5, 6, 7);
	double angle = v1.angle(v2);
	std::cout << angle << std::endl;
}

Application::~Application()
{
}

void Application::start()
{
	std::chrono::duration<double> deltaTime{};

	while (running)
	{
		auto start = std::chrono::high_resolution_clock::now();

		graphics->beforeFrame();
		graphics->clear();

		update(deltaTime.count() * 1000);
		render();

		graphics->update();

		eventManager->handleEvents();

		auto finish = std::chrono::high_resolution_clock::now();
		deltaTime = finish - start;
	}
}

void Application::quit()
{
	running = false;
}

void Application::render()
{
	graphics->drawAxis();
	planet_->draw(*graphics);
	ship_->draw(*graphics);
}

void Application::update(double time)
{
	planet_->update(time);
	ship_->update(time);
}

void Application::onKeyDown(KeyEvent& keyEvent)
{
	switch (keyEvent.key())
	{
		case KeyEvent::Space:
			graphics->changeView(); 
			break;
		case KeyEvent::Up:
			//s1->scaleInPlace(2, 2, 2); 
			break;
		case KeyEvent::Down:
			//s1->scaleInPlace(0.5f, 0.5f, 0.5f); 
			break;
		case KeyEvent::Left:
			//s1->rotateAroundAxis(2 * pi / 32, *(std::make_unique<Vector>(-1000, 50, 50)), *(std::make_unique<Vector>(-1025, 50, 50)));
			break;
		case KeyEvent::Right:
			//s1->rotateAroundAxis(-2 * pi / 32, *(std::make_unique<Vector>(-1000, 50, 50)), *(std::make_unique<Vector>(-1025, 50, 50)));
			break;
		case KeyEvent::F1:
			//s1->rotateAroundPoint(2 * pi / 32, 'Y', *(std::make_unique<Vector>(50, 50, 50)));
			break;
		case KeyEvent::F2:
			//s1->rotateAroundPoint(-2 * pi / 32, 'Y', *(std::make_unique<Vector>(50, 50, 50)));
			break;
		case KeyEvent::F3:
			//s1->rotateInPlace(2 * pi / 32, 'Y');
			break;
		case KeyEvent::F4:
			//s1->rotateInPlace(-2 * pi / 32, 'Y');
			break;
		case KeyEvent::F5:
			//s1->scaleFromPoint(2, 2, 2, *(std::make_unique<Vector>(250, 250, 250)));
			break;
		case KeyEvent::F6:
			//s1->scaleFromPoint(0.5f, 0.5f, 0.5f, *(std::make_unique<Vector>(250, 250, 250)));
			break;

		case KeyEvent::Q:
			ship_->barrelRollLeft_ = true;
			break;
		case KeyEvent::E:
			ship_->barrelRollRight_ = true;
			break;
		case KeyEvent::A:
			ship_->turnLeft_ = true;
			break;
		case KeyEvent::D:
			ship_->turnRight_ = true;
			break;
		case KeyEvent::W:
			ship_->moveUp_ = true;
			break;
		case KeyEvent::S:
			ship_->moveDown_ = true;
			break;
		case KeyEvent::Shift:
			ship_->accelerate_ = true;
			break;
	}
}

void Application::onKeyUp(KeyEvent& keyEvent)
{
	switch (keyEvent.key())
	{
		case KeyEvent::Q:
			ship_->barrelRollLeft_ = false;
			break;
		case KeyEvent::E:
			ship_->barrelRollRight_ = false;
			break;
		case KeyEvent::A:
			ship_->turnLeft_ = false;
			break;
		case KeyEvent::D:
			ship_->turnRight_ = false;
			break;
		case KeyEvent::W:
			ship_->moveUp_ = false;
			break;
		case KeyEvent::S:
			ship_->moveDown_ = false;
			break;
		case KeyEvent::Shift:
			ship_->accelerate_ = false;
			break;
	}
}
