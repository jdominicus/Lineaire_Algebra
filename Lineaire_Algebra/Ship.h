#pragma once
#include <memory>
class Shape;
class Graphics;
class Ship
{
public:
	Ship();
	~Ship();
	void update(float time);
	void draw(Graphics& graphics);

	void accelerate(float time);
	void barrelRollLeft(float time);
	void barrelRollRight(float time);
	void turnLeft(float time);
	void turnRight(float time);
	void moveUp(float time);
	void moveDown(float time);
	void shoot(float time);
	void update(SDL_Renderer& renderer, Camera& camera) override;

	bool accelerate_;
	bool barrelRollLeft_;
	bool barrelRollRight_;
	bool turnLeft_;
	bool turnRight_;
	bool moveUp_;
	bool moveDown_;

private:
	std::unique_ptr<Shape> shape_;
	const double pi = 3.14159265359;
};

