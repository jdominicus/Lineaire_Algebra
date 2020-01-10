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
	camera_ = std::make_unique<Camera>();
	graphics = std::make_unique<Graphics>();
	eventManager->addApplicationListener(this);
	eventManager->addKeyListener(this);

	graph = std::make_unique<Graph>();
	planet_ = std::make_unique<Planet>();
	ship_ = std::make_unique<Ship>();
	camera_->setLookat(ship_.get());
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
	planet_->update(*graphics->getRenderer(), *camera_.get());
	ship_->update(*graphics->getRenderer(), *camera_.get());
}

void Application::update(double time)
{
	planet_->update(time);
	ship_->update(time);
	camera_->setLookat(ship_.get());
}

void Application::onKeyDown(KeyEvent& keyEvent)
{
	switch (keyEvent.key())
	{
		case KeyEvent::Space:
			graphics->changeView(); 
			break;
		case KeyEvent::Up:
			camera_->moveZ(0.5);
			break;
		case KeyEvent::Down:
			camera_->moveZ(-0.5);
			break;
		case KeyEvent::Left:
			camera_->moveX(-0.5);
			break;
		case KeyEvent::Right:
			camera_->moveX(0.5);
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
