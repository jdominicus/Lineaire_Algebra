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

	void drawInWindow(SDL_Renderer& renderer, Vector& vector1, Vector& vector2, int r, int g, int b);

	void moveX(float amount);
	void moveY(float amount);
	void moveZ(float amount);
	void setLookat(Shape* lookat) { lookAt = lookat; }
	void rotateHorizontal(double degrees);
	void rotateVertical(double degrees);

	Shape* lookAt;

private:
	Matrix projectionMatrix_;
	Vector position_;
	double far_;
	double near_;
	double fovy_;
};

