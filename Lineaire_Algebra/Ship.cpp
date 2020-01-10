#include "Ship.h"
#include "Camera.h"

Ship::Ship() : Shape()
{
	addVector(std::make_unique<Vector>(-0.5, 0, 0));
	addVector(std::make_unique<Vector>(0.5, 0, 0));
	addVector(std::make_unique<Vector>(0, 0, -1));
	addVector(std::make_unique<Vector>(0, 0.5, 0));

	addConnection(0, 1);
	addConnection(0, 2);
	addConnection(0, 3);
	addConnection(1, 2);
	addConnection(1, 3);
	addConnection(2, 3);
}

void Ship::update(SDL_Renderer& renderer, Camera& camera)
{
	camera.drawInWindow(renderer, *position_.get(), *getVectors()[3].get());
	camera.drawInWindow(renderer, *position_.get(), *getVectors()[1].get());
	camera.drawInWindow(renderer, *position_.get(), *getVectors()[2].get());
	Shape::update(renderer, camera);
}
