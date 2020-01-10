#include "Planet.h"
#include "Shape.h"
#include "Camera.h"
#include "Vector.h"

Planet::Planet() : growing_{ true }, radius_{ 50 }
{
	addVector(std::make_unique<Vector>(10, 0, -40));
	addVector(std::make_unique<Vector>(10, 0, -50));
	addVector(std::make_unique<Vector>(20, 0, -50));
	addVector(std::make_unique<Vector>(20, 0, -40));
	addVector(std::make_unique<Vector>(10, 10, -40));
	addVector(std::make_unique<Vector>(10, 10, -50));
	addVector(std::make_unique<Vector>(20, 10, -50));
	addVector(std::make_unique<Vector>(20, 10, -40));

	addConnection(0, 1);
	addConnection(1, 2);
	addConnection(2, 3);
	addConnection(3, 0);
	addConnection(4, 5);
	addConnection(5, 6);
	addConnection(6, 7);
	addConnection(7, 4);
	addConnection(0, 4);
	addConnection(1, 5);
	addConnection(2, 6);
	addConnection(3, 7);

	updateColor(0, 255, 0);
}

Planet::~Planet()
{

}

void Planet::update(float time)
{
	time_ += time;

	if (time_ >= 500)
	{
		time_ = 0;
		growing_ = !growing_;
	}

	if (growing_)
		scaleFromPoint(1 + time / 2000, 1 + time / 2000, 1 + time / 2000, *std::make_unique<Vector>(15, 5, -65));

	if (!growing_)
		scaleFromPoint(1 - time / 2000, 1 - time / 2000, 1 - time / 2000, *std::make_unique<Vector>(15, 5, -65));
}

void Planet::update(SDL_Renderer& renderer, Camera& camera)
{
	/*camera.drawInWindow(renderer, *position_.get(), *getVectors()[3].get(), 0, 255, 0);
	camera.drawInWindow(renderer, *position_.get(), *getVectors()[1].get(), 0, 255, 0);
	camera.drawInWindow(renderer, *position_.get(), *getVectors()[2].get(), 0, 255, 0);*/
	Shape::update(renderer, camera);
}