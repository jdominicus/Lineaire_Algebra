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
#include "Bullet.h"
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
	for (auto& projectile : projectiles)
	{
		projectile->update(*graphics->getRenderer(), *camera_.get());
	}
}

void Application::update(double time)
{
	planet_->update(time);
	ship_->move();
	ship_->update(time);
	camera_->setLookat(ship_.get());

	for (auto it = projectiles.begin(); it != projectiles.end();)
	{
		(*it)->move();

		if (abs((*it)->position_->getX()) > 250 || abs((*it)->position_->getY()) > 250 || abs((*it)->position_->getZ() > 250))
			it = projectiles.erase(it);
		else
			++it;			
	}
	
	for (auto it = projectiles.begin(); it != projectiles.end();)
	{
   		if (planet_->collidesWith(**it))
		{
			planet_->hit();
			it = projectiles.erase(it);
		}
		else
			++it;
	}

	if (ship_->collidesWith(*planet_))
		std::cout << "You got hit" << std::endl;
}

void Application::onKeyDown(KeyEvent& keyEvent)
{
	switch (keyEvent.key())
	{
		case KeyEvent::Space:
			projectiles.emplace_back(std::make_unique<Bullet>(ship_.get()));
			break;
		case KeyEvent::Up:
			camera_->moveZ(-0.5);
			break;
		case KeyEvent::Down:
			camera_->moveZ(0.5);
			break;
		case KeyEvent::Left:
			camera_->moveX(-0.5);
			break;
		case KeyEvent::Right:
			camera_->moveX(0.5);
			break;
		case KeyEvent::F1:
			camera_->rotateHorizontal(-10);
			break;
		case KeyEvent::F2:
			camera_->rotateHorizontal(10);
			break;
		case KeyEvent::F3:
			camera_->rotateVertical(-10);
			break;
		case KeyEvent::F4:
			camera_->rotateVertical(10);
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
			ship_->accelerate();
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
