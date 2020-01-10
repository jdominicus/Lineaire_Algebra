#include "Ship.h"
#include "Shape.h"
#include "Vector.h"
#include "Camera.h"
#include <memory>

Ship::Ship() : accelerate_{ false }, barrelRollLeft_{ false }, barrelRollRight_{ false }, moveUp_{ false }, moveDown_{false}
{
	shape_ = std::make_unique<Shape>();
	/*shape_->addVector(std::make_unique<Vector>(50, 50, 50)); // 0 - Tip
	shape_->addVector(std::make_unique<Vector>(25, 50, 100)); // 1 - Back-left
	shape_->addVector(std::make_unique<Vector>(75, 50, 100)); // 2 - Back-right
	shape_->addVector(std::make_unique<Vector>(50, 75, 100)); // 3 - Up
	shape_->addVector(std::make_unique<Vector>(50, 50, 100)); // 4 - Down (NC)

	shape_->addConnection(0, 1);
	shape_->addConnection(0, 2);
	shape_->addConnection(0, 3);
	shape_->addConnection(1, 2);
	shape_->addConnection(1, 3);
	shape_->addConnection(2, 3);*/

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

Ship::~Ship()
{

}

void Ship::update(float time)
{
	if (accelerate_)
		accelerate(time);
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
}

void Ship::accelerate(float time)
{
	auto vector_1 = *shape_->getVectors().at(0);
	auto vector_2 = *shape_->getVectors().at(4);
	
	auto newVector = std::make_unique<Vector>(vector_1.getX() - vector_2.getX(), vector_1.getY() - vector_2.getY(), vector_1.getZ() - vector_2.getZ());
	double speedFactor = time / 250;

	shape_->translate(speedFactor * newVector->getX(), speedFactor * newVector->getY(), speedFactor * newVector->getZ());
}

void Ship::barrelRollLeft(float time)
{
	shape_->rotateAroundAxis(time / 250, *shape_->getVectors().at(0), *shape_->getVectors().at(4));
}

void Ship::barrelRollRight(float time)
{
	shape_->rotateAroundAxis(-time / 250, *shape_->getVectors().at(0), *shape_->getVectors().at(4));
}

void Ship::turnLeft(float time)
{
	shape_->rotateAroundAxis(time / 250, *shape_->getVectors().at(3), *shape_->getVectors().at(4));
}

void Ship::turnRight(float time)
{
	shape_->rotateAroundAxis(-time / 250, *shape_->getVectors().at(3), *shape_->getVectors().at(4));
}

void Ship::moveUp(float time)
{
	shape_->rotateAroundAxis(time / 250, *shape_->getVectors().at(1), *shape_->getVectors().at(2));
}

void Ship::moveDown(float time)
{
	shape_->rotateAroundAxis(-time / 250, *shape_->getVectors().at(1), *shape_->getVectors().at(2));
}

void Ship::shoot(float time)
{

}

void Ship::draw(Graphics& graphics)
{
	shape_->draw(graphics);
}

void Ship::update(SDL_Renderer& renderer, Camera& camera)
{
	camera.drawInWindow(renderer, *position_.get(), *getVectors()[3].get());
	camera.drawInWindow(renderer, *position_.get(), *getVectors()[1].get());
	camera.drawInWindow(renderer, *position_.get(), *getVectors()[2].get());
	Shape::update(renderer, camera);
}