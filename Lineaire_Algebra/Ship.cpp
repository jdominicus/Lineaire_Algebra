#include "Ship.h"
#include "Shape.h"
#include "Vector.h"
#include "Camera.h"
#include <memory>

Ship::Ship() : accelerate_{ false }, barrelRollLeft_{ false }, barrelRollRight_{ false }, moveUp_{ false }, moveDown_{false}
{
	addVector(std::make_unique<Vector>(0, 0, -15)); // 0 - Tip
	addVector(std::make_unique<Vector>(-2.5, 0, -5)); // 1 - Back-left
	addVector(std::make_unique<Vector>(2.5, 0, -5)); // 2 - Back-right
	addVector(std::make_unique<Vector>(0, 2.5, -5)); // 3 - Up
	addVector(std::make_unique<Vector>(0, 0, -5)); // 4 - Down (NC)

	addConnection(0, 1);
	addConnection(0, 2);
	addConnection(0, 3);
	addConnection(1, 2);
	addConnection(1, 3);
	addConnection(2, 3);

	updatePosition();
	updateColor(255, 255, 255);
}

Ship::~Ship()
{

}

void Ship::accelerate()
{
	if (speed < 1)
		speed += 0.1;
}

void Ship::deccelerate()
{
	if (speed > 0)
		speed -= 0.1;
}

void Ship::barrelRollLeft(float time)
{
	rotateAroundAxis(time / 500, *vectors.at(0), *vectors.at(4));
}

void Ship::barrelRollRight(float time)
{
	rotateAroundAxis(-time / 500, *vectors.at(0), *vectors.at(4));
}

void Ship::turnLeft(float time)
{
	rotateAroundAxis(time / 500, *vectors.at(3), *vectors.at(4));
}

void Ship::turnRight(float time)
{
	rotateAroundAxis(-time / 500, *vectors.at(3), *vectors.at(4));
}

void Ship::moveUp(float time)
{
	rotateAroundAxis(time / 500, *vectors.at(1), *vectors.at(2));
}

void Ship::moveDown(float time)
{
	rotateAroundAxis(-time / 500, *vectors.at(1), *vectors.at(2));
}

void Ship::shoot(float time)
{

}

void Ship::update(float time)
{
	if (barrelRollLeft_)
		barrelRollLeft(time);
	if (barrelRollRight_)
		barrelRollRight(time);
	if (turnLeft_)
		turnLeft(time);
	if (turnRight_)
		turnRight(time);
	if (moveUp_)
		moveUp(time);
	if (moveDown_)
		moveDown(time);

	updatePosition();
}

void Ship::move()
{
	Vector v1 = { *vectors.at(0) };
	Vector v2 = { *vectors.at(4) };

	v1 -= v2;
	v1.normalize();
	direction = v1;

	v1 *= (0.1 * speed);
	speedVector = v1;

	*position_.get() += speedVector;

	for (auto& vector : vectors)
	{
		*vector.get() += speedVector;
	}

	if (speed > 0)
		speed -= 0.0001;
}

void Ship::update(SDL_Renderer& renderer, Camera& camera)
{
	/*camera.drawInWindow(renderer, *position_.get(), *getVectors()[3].get(), 255, 255, 255);
	camera.drawInWindow(renderer, *position_.get(), *getVectors()[1].get(), 255, 255, 255);
	camera.drawInWindow(renderer, *position_.get(), *getVectors()[2].get(), 255, 255, 255);*/
	Shape::update(renderer, camera);
}