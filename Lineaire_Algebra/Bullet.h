#pragma once
#include "Shape.h"
#include "Vector.h"

class Ship;

class Bullet: public Shape
{
public:
	Bullet(Ship* ship);

	void update(SDL_Renderer& renderer, Camera& camera);
	void move();
	Vector speedVector;
};

