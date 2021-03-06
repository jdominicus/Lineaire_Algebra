#pragma once
#include <memory>
#include "Shape.h"
#include "Vector.h"

class Shape;
class Graphics;

class Ship : public Shape
{
public:
	Ship();
	~Ship();
	void accelerate();
	void deccelerate();
	void update(float time);

	void barrelRollLeft(float time);
	void barrelRollRight(float time);
	void turnLeft(float time);
	void turnRight(float time);
	void moveUp(float time);
	void moveDown(float time);
	void shoot(float time);
	void update(SDL_Renderer& renderer, Camera& camera) override;
	void move();

	bool accelerate_;
	bool barrelRollLeft_;
	bool barrelRollRight_;
	bool turnLeft_;
	bool turnRight_;
	bool moveUp_;
	bool moveDown_;
	bool guideLine_;
	Vector direction;
	Vector speedVector;
	double speed;
};

