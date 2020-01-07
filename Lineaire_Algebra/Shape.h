#pragma once
#include <vector>
#include <map>
#include <cmath>
#include <memory>
#include <utility>
#include <iostream>
#include "SDL2/SDL.h"

class Vector;
class Camera;
class Graphics;

class Shape
{
	public:
		Shape();
		~Shape();

		void addVector(std::unique_ptr<Vector> vector);
		void addConnection(int index_1, int index_2);

		Vector* getReferencePoint();
		std::vector<std::unique_ptr<Vector>>& getVectors();
		void setReferencePoint();
		void updateReferencePoint();

		void scaleInPlace(double x, double y, double z);
		void scaleFromPoint(double x, double y, double z, const Vector& point);
			
		void rotateInPlace(double radians, char axis);
		void rotateAroundPoint(double radians, char axis, const Vector& point);
		void rotateAroundAxis(double radians, const Vector& point_1, const Vector& point_2);

		void update(SDL_Renderer& renderer, Camera& camera);
		
		void draw(Graphics& graphics);

	private:
		std::vector<std::unique_ptr<Vector>> vectors;
		std::multimap<Vector*, Vector*> connections;
		std::unique_ptr<Vector> referencePoint;

		const double pi = 3.14159265359;
};