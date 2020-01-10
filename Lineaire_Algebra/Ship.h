#pragma once
#include "Shape.h"

class Ship: public Shape
{
public:
	Ship();
	void update(SDL_Renderer& renderer, Camera& camera) override;
};

