#include "Camera.h"
#include "Vector.h"
#include "Matrix.h"
#include <corecrt_math_defines.h>
#include "SDL2/SDL.h"

Camera::Camera() : Shape(), projectionMatrix_{ 4, 4 }, position_{ 0 ,0, 0 }, fovy_{ 90 }, near_{ 0.1 }, far_{ 100 }
{
	this->addVector(std::make_unique<Vector>(0, 0, 1));
	double povyRad = fovy_ / 180.0 * static_cast<double>(M_PI);
	double scale = near_ * tan(povyRad * 0.5);

	projectionMatrix_(0, 0) = scale;
	projectionMatrix_(1, 1) = scale;
	projectionMatrix_(2, 2) = -far_ / (far_ - near_);
	projectionMatrix_(2, 3) = -far_ * near_ / (far_ - near_);
	projectionMatrix_(3, 2) = -1;

	position_ = *getVectors()[0].get();
}

Matrix Camera::lookatMatrix()
{
	Vector eye_{ position_.getX(), position_.getY(), position_.getZ() };
	eye_ -= Vector{ 0,0,0 };

	Vector direction = eye_;
	direction.normalize();

	Vector up{ 0, 1, 0 };

	Vector right = up.crossProduct(direction);
	right.normalize();

	up = direction.crossProduct(right);

	up.normalize();

	Matrix m{ 4, 4 };
	m(0, 0) = right.getX();
	m(0, 1) = up.getX();
	m(0, 2) = direction.getX();
	m(1, 0) = right.getY();
	m(1, 1) = up.getY();
	m(1, 2) = direction.getY();
	m(2, 0) = right.getZ();
	m(2, 1) = up.getZ();
	m(2, 2) = direction.getZ();
	m(3, 0) = -right.dotProduct(position_);
	m(3, 1) = -up.dotProduct(position_);
	m(3, 2) = -direction.dotProduct(position_);
	m(3, 3) = 1;

		return m;
}

void Camera::drawInWindow(SDL_Renderer& renderer, Vector& vector1, Vector& vector2)
{
	Matrix vector1Matrix{ 4, 1 };
	vector1Matrix(0, 0) = vector1.getX();
	vector1Matrix(0, 1) = vector1.getY();
	vector1Matrix(0, 2) = vector1.getZ();
	vector1Matrix(0, 3) = 1;

	Matrix vector2Matrix{ 4, 1 };
	vector2Matrix(0, 0) = vector2.getX();
	vector2Matrix(0, 1) = vector2.getY();
	vector2Matrix(0, 2) = vector2.getZ();
	vector2Matrix(0, 3) = 1;

	Matrix lookatMatrix1 = lookatMatrix() * vector1Matrix;
	Matrix lookatMatrix2 = lookatMatrix() * vector2Matrix;

	Matrix projectionResultMatrix1 = projectionMatrix_ * lookatMatrix1;
	Matrix projectionResultMatrix2 = projectionMatrix_ * lookatMatrix2;

	if (projectionResultMatrix1(3,0) > 0 && projectionResultMatrix2(3,0) > 0)
	{
		double x1 = projectionResultMatrix1(0,0) / projectionResultMatrix1(3, 0);
		double y1 = projectionResultMatrix1(1,0) / projectionResultMatrix1(3, 0);

		double x2 = projectionResultMatrix2(0, 0) / projectionResultMatrix2(3, 0);
		double y2 = projectionResultMatrix2(1, 0) / projectionResultMatrix2(3, 0);

		SDL_SetRenderDrawColor(&renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(&renderer, 300 + x1 * 150, 300 + y1 * -150, 300 + x2 * 150, 300 + y2 * -150);
	}
}

void Camera::moveX(float amount)
{
	position_.setX(position_.getX() + amount);
	getVectors()[0]->setX(position_.getX());
}

void Camera::moveY(float amount)
{
	position_.setY(position_.getY() + amount);
	getVectors()[0]->setY(position_.getY());
}

void Camera::moveZ(float amount)
{
	position_.setZ(position_.getZ() + amount);
	getVectors()[0]->setZ(position_.getZ());
}

