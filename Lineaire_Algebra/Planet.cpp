#include "Planet.h"
#include "Shape.h"
#include "Vector.h"

Planet::Planet() : growing_{ true }, radius_{ 50 }
{
	shape_ = std::make_unique<Shape>();
	shape_->addVector(std::make_unique<Vector>(50, 50, -50));
	shape_->addVector(std::make_unique<Vector>(50, 50, -100));
	shape_->addVector(std::make_unique<Vector>(100, 50, -100));
	shape_->addVector(std::make_unique<Vector>(100, 50, -50));
	shape_->addVector(std::make_unique<Vector>(50, 100, -50));
	shape_->addVector(std::make_unique<Vector>(50, 100, -100));
	shape_->addVector(std::make_unique<Vector>(100, 100, -100));
	shape_->addVector(std::make_unique<Vector>(100, 100, -50));

	shape_->addConnection(0, 1);
	shape_->addConnection(1, 2);
	shape_->addConnection(2, 3);
	shape_->addConnection(3, 0);
	shape_->addConnection(4, 5);
	shape_->addConnection(5, 6);
	shape_->addConnection(6, 7);
	shape_->addConnection(7, 4);
	shape_->addConnection(0, 4);
	shape_->addConnection(1, 5);
	shape_->addConnection(2, 6);
	shape_->addConnection(3, 7);
	
	shape_->setReferencePoint();
}

Planet::~Planet()
{

}

void Planet::update(float time)
{
	time_ += time;

	if (time_ >= 1000)
	{
		time_ = 0;
		growing_ = !growing_;
	}

	if (growing_)
		shape_->scaleInPlace(1 + time / 1000, 1 + time / 1000, 1 + time / 1000);

	if (!growing_)
		shape_->scaleInPlace(1 - time / 1000, 1 - time / 1000, 1 - time / 1000);
}

void Planet::draw(Graphics& graphics)
{
	shape_->draw(graphics);
}