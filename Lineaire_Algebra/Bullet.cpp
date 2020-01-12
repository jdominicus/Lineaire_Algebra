#include "Bullet.h"
#include "Vector.h"
#include "Ship.h"

Bullet::Bullet(Ship* ship)
{
	Vector end{ ship->direction };

	addVector(std::make_unique<Vector>(ship->getVectors()[0]->getX(), ship->getVectors()[0]->getY(), ship->getVectors()[0]->getZ()));
	addVector(std::make_unique<Vector>(ship->getVectors()[0]->getX() + end.getX(), ship->getVectors()[0]->getY() + end.getY(), ship->getVectors()[0]->getZ() + end.getZ()));
	addConnection(0, 1);

	speedVector = Vector{ ship->direction };
	speedVector += (ship->speedVector);
}

void Bullet::update(SDL_Renderer& renderer, Camera& camera)
{
	SDL_SetRenderDrawColor(&renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	Shape::update(renderer, camera);

	SDL_SetRenderDrawColor(&renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void Bullet::move()
{
	*position_ += (speedVector);

	for (auto& vector : vectors)
	{
		*vector.get() += speedVector;
	}

	updatePosition();
}
