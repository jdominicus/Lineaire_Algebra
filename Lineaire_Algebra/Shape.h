#pragma once

#include <vector>
#include <map>
#include <cmath>
#include <memory>
#include <utility>
#include <iostream>

#include "Vector.h"
#include "Matrix.h"
#include "TranslationMatrix.h"
#include "ScalingMatrix.h"
#include "RotationMatrix.h"

template <typename>
class Vector;
class Graphics;

template <typename T>
class Shape
{
	public:
		Shape();
		~Shape();

		void addVector(std::unique_ptr<Vector<T>> vector);
		void addConnection(int index_1, int index_2);

		Vector<T>* getReferencePoint();
		void setReferencePoint();
		void updateReferencePoint();

		void scaleInPlace(T x, T y, T z);
		void scaleFromPoint(T x, T y, T z, const Vector<T>& point);
			
		void rotateInPlace(T radians, char axis);
		void rotateAroundPoint(T radians, char axis, const Vector<T>& point);
		void rotateAroundAxis(T radians, const Vector<T>& point_1, const Vector<T>& point_2);
		
		void draw(Graphics& graphics);

	private:
		std::vector<std::unique_ptr<Vector<T>>> vectors;
		std::multimap<Vector<T>*, Vector<T>*> connections;
		std::unique_ptr<Vector<T>> referencePoint;

		const double pi = 3.14159265359;
};

template <typename T>
Shape<T>::Shape() : referencePoint(nullptr)
{
}

template <typename T>
Shape<T>::~Shape()
{
}

template <typename T>
void Shape<T>::addVector(std::unique_ptr<Vector<T>> vector)
{
	vectors.emplace_back(std::move(vector));
}

template <typename T>
void Shape<T>::addConnection(int index_1, int index_2)
{
	auto pair = std::make_pair(vectors.at(index_1).get(), vectors.at(index_2).get());
	connections.insert(pair);
}

template <typename T>
Vector<T>* Shape<T>::getReferencePoint()
{
	return referencePoint.get();
}

template <typename T>
void Shape<T>::setReferencePoint()
{
	updateReferencePoint();
}

template <typename T>
void Shape<T>::updateReferencePoint()
{
	T reference[3] = { 0,0,0 };

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
	{
		reference[0] += (*it)->getX();
		reference[1] += (*it)->getY();
		reference[2] += (*it)->getZ();
	}
	
	referencePoint = std::make_unique<Vector<T>>(reference[0] / 8, reference[1] / 8, reference[2] / 8);
}

template <typename T>
void Shape<T>::scaleInPlace(T x, T y, T z)
{
	TranslationMatrix<T> t1(4, 4, -referencePoint->getX(), -referencePoint->getY(), -referencePoint->getZ());
	ScalingMatrix<T> s1(4, 4, x, y, x);
	TranslationMatrix<T> t2(4, 4, referencePoint->getX(), referencePoint->getY(), referencePoint->getZ());

	Matrix<T> m = t2 * s1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		**it = m * **it;
		
	updateReferencePoint();
}

template <typename T>
void Shape<T>::scaleFromPoint(T x, T y, T z, const Vector<T>& point)
{
	TranslationMatrix<T> t1(4, 4, -point.getX(), -point.getY(), -point.getZ());
	ScalingMatrix<T> s1(4, 4, x, y, x);
	TranslationMatrix<T> t2(4, 4, point.getX(), point.getY(), point.getZ());

	Matrix<T> m = t2 * s1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		**it = m * **it;

	updateReferencePoint();
}

template <typename T>
void Shape<T>::rotateInPlace(T radians, char axis)
{
	TranslationMatrix<T> t1(4, 4, -referencePoint->getX(), -referencePoint->getY(), -referencePoint->getZ());
	RotationMatrix<T> r1(4, 4, radians, axis);
	TranslationMatrix<T> t2(4, 4, referencePoint->getX(), referencePoint->getY(), referencePoint->getZ());

	Matrix<T> m = t2 * r1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

template <typename T>
void Shape<T>::rotateAroundPoint(T radians, char axis, const Vector<T>& point)
{
	TranslationMatrix<T> t1(4, 4, -point.getX(), -point.getY(), -point.getZ());
	RotationMatrix<T> r1(4, 4, radians, axis);
	TranslationMatrix<T> t2(4, 4, point.getX(), point.getY(), point.getZ());

	Matrix<T> m = t2 * r1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

template <typename T>
void Shape<T>::rotateAroundAxis(T radians, const Vector<T>& point_1, const Vector<T>& point_2)
{
	auto newVector = std::make_unique<Vector<T>>(point_2.getX() - point_1.getX(), point_2.getY() - point_1.getY(), point_2.getZ() - point_1.getZ());
	T length = sqrt(pow(newVector->getX(), 2) + pow(newVector->getY(), 2) + pow(newVector->getZ(), 2)); // Lenght of vector

	T angle_1 = atan((point_2.getX() - point_1.getX()) / point_2.getY() - point_1.getY()); // Rotation to ZY Surface
	T angle_2 = asin((point_2.getZ() - point_1.getZ()) / length); // Rotation to Y Axis

	TranslationMatrix<T> t1(4, 4, -newVector->getX(), -newVector->getY(), -newVector->getZ());
	RotationMatrix<T> r1(4, 4, angle_1, 'Z');
	RotationMatrix<T> r2(4, 4, angle_2, 'X');
	RotationMatrix<T> r3(4, 4, radians, 'Y');
	RotationMatrix<T> r4(4, 4, -angle_2, 'X');
	RotationMatrix<T> r5(4, 4, -angle_1, 'Z');
	TranslationMatrix<T> t2(4, 4, newVector->getX(), newVector->getY(), newVector->getZ());

	//T length = sqrt(pow(v, 2) + pow(v.getX(), 2));
	//T angleA = atan2(v.getZ(), v.getX());
	//T angleB = (-atan2(v.getY(), length));

	Matrix<T> m = t2 * r5 * r4 * r3 * r2 * r1 * t1;
	//Matrix<T> m = t2 * r3 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

template <typename T>
void Shape<T>::draw(Graphics& graphics)
{
	for (auto it = connections.begin(); it != connections.end(); ++it)
		graphics.drawLine(it->first->getX(), it->first->getY(), it->first->getZ(), it->second->getX(), it->second->getY(), it->second->getZ());
}

