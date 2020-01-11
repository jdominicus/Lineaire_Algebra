#include "Bullet.h"
#include "Vector.h"
#include "Ship.h"

Bullet::Bullet(Ship* ship)
{
	Vector end{ ship->direction };

	addVector(std::make_unique<Vector>(ship->position_->getX(), ship->position_->getY(), ship->position_->getZ()));
	addVector(std::make_unique<Vector>(end.getX(), end.getY(), end.getZ()));
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
}
