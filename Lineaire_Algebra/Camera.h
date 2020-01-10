#pragma once
#include "Matrix.h"
#include "Vector.h"
#include "Shape.h"

class Vector;
class Matrix;
class Shape;


class Camera : public Shape
{
public:
	Camera();
	Matrix lookatMatrix();

	void drawInWindow(SDL_Renderer& renderer, Vector& vector1, Vector& vector2);

	void moveX(float amount);

	void moveY(float amount);

	void moveZ(float amount);
	Shape* lookAt;
	void setLookat(Shape* lookat) { lookAt = lookat; }

private:
	Matrix projectionMatrix_;
	Vector position_;
	double far_;
	double near_;
	double fovy_;
};

