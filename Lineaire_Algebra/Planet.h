#pragma once
#include "Shape.h"
#include "CollidableShape.h"
#include <memory>

class Graphics;

class Planet : public Shape, public CollidableShape
{
	public:
		Planet();
		~Planet();
		void hit();
		void update(float time);
		void update(SDL_Renderer& renderer, Camera& camera);
	
private:
		bool growing_;
		bool destroyed_;
		double time_;
		double growingFactor_;
		double radius_;
		int hits_;
};

