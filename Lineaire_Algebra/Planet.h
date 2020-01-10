#pragma once
#include "Shape.h"
#include <memory>

class Graphics;

class Planet : public Shape
{
	public:
		Planet();
		~Planet();
		void update(float time);
		void update(SDL_Renderer& renderer, Camera& camera);
	
private:
		bool growing_;
		double time_;
		double growingFactor_;
		double radius_;

		const double pi = 3.14159265359;
};

