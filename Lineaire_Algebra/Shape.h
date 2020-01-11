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

		Vector& position();
		virtual void updatePosition();
		void updateColor(int r, int g, int b);
		std::vector<std::unique_ptr<Vector>>& getVectors();
		std::multimap<Vector*, Vector*>& getConnections();

		void translate(double x, double y, double z);
		void scaleFromPoint(double x, double y, double z, const Vector& point);
			
		void rotateInPlace(double radians, char axis);
		void rotateAroundPoint(double radians, char axis, const Vector& point);
		void rotateAroundAxis(double radians, const Vector& point_1, const Vector& point_2);

		virtual void update(SDL_Renderer& renderer, Camera& camera);
		
		std::unique_ptr<Vector> position_;

	protected:
		std::vector<std::unique_ptr<Vector>> vectors;
		std::multimap<Vector*, Vector*> connections;
		std::unique_ptr<Vector> referencePoint;

		int r_;
		int g_;
		int b_;
};