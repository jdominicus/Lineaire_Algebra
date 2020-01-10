#include "Application.h"
#include "Graphics.h"
#include "EventManager.h"
#include "Graph.h"
#include "Vector.h"
#include "Matrix.h"
#include "Shape.h"
#include "KeyEvent.h"
#include "Ship.h"

Application::Application() : running{ true }
{
	eventManager = std::make_unique<EventManager>();
	camera_ = std::make_unique<Camera>();
	graphics = std::make_unique<Graphics>();
	eventManager->addApplicationListener(this);
	eventManager->addKeyListener(this);

	graph = std::make_unique<Graph>();

	ship = std::make_unique<Ship>();

	camera_->setLookat(ship.get());
	
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
	//graphics->drawAxis();

	//s1->update(*graphics->getRenderer(), *camera_.get());
	ship->update(*graphics->getRenderer(), *camera_.get());
	//s3->update(*graphics->getRenderer(), *camera_.get());
}

void Application::update()
{

}

void Application::onKeyDown(KeyEvent& keyEvent)
{
	switch (keyEvent.key())
	{
		case KeyEvent::Space:
			graphics->changeView(); 
			break;
		case KeyEvent::Up:
			camera_->moveZ(0.1);
			//s1->scaleInPlace(2, 2, 2); 
			break;
		case KeyEvent::Down:
			camera_->moveZ(-0.1);
			//s1->scaleInPlace(0.5f, 0.5f, 0.5f); 
			break;
		case KeyEvent::Left:
			camera_->moveX(-0.1);
			//s1->rotateAroundAxis(2 * pi / 32, *(std::make_unique<Vector>(-1000, 50, 50)), *(std::make_unique<Vector>(-1025, 50, 50)));
			break;
		case KeyEvent::Right:
			camera_->moveX(0.1);
			//s1->rotateAroundAxis(-2 * pi / 32, *(std::make_unique<Vector>(-1000, 50, 50)), *(std::make_unique<Vector>(-1025, 50, 50)));
			break;
		case KeyEvent::F1:
			s1->rotateAroundPoint(2 * pi / 32, 'Y', *(std::make_unique<Vector>(50, 50, 50)));
			break;
		case KeyEvent::F2:
			s1->rotateAroundPoint(-2 * pi / 32, 'Y', *(std::make_unique<Vector>(50, 50, 50)));
			break;
		case KeyEvent::F3:
			s1->rotateInPlace(2 * pi / 32, 'Y');
			break;
		case KeyEvent::F4:
			s1->rotateInPlace(-2 * pi / 32, 'Y');
			break;
		case KeyEvent::F5:
			s1->scaleFromPoint(2, 2, 2, *(std::make_unique<Vector>(250, 250, 250)));
			break;
		case KeyEvent::F6:
			s1->scaleFromPoint(0.5f, 0.5f, 0.5f, *(std::make_unique<Vector>(250, 250, 250)));
			break;
	}
}

void Application::onKeyUp(KeyEvent& keyEvent)
{

}
