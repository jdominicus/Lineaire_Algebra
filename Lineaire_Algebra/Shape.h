#pragma once
#include <vector>
#include <map>
#include <cmath>
#include <memory>
#include <utility>
#include <iostream>

class Vector;
class Graphics;

class Shape
{
	public:
		Shape();
		~Shape();

		void addVector(std::unique_ptr<Vector> vector);
		void addConnection(int index_1, int index_2);

		Vector* getReferencePoint();
		void setReferencePoint();
		void updateReferencePoint();

		void scaleInPlace(float x, float y, float z);
		void scaleFromPoint(float x, float y, float z, const Vector& point);
			
		void rotateInPlace(float radians, char axis);
		void rotateAroundPoint(float radians, char axis, const Vector& point);
		void rotateAroundAxis(float radians, const Vector& point_1, const Vector& point_2);
		
		void draw(Graphics& graphics);

	private:
		std::vector<std::unique_ptr<Vector>> vectors;
		std::multimap<Vector*, Vector*> connections;
		std::unique_ptr<Vector> referencePoint;

		const double pi = 3.14159265359;
};