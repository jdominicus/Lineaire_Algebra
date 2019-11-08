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
		void updateReferencePoint();
		void scaleFromOrigin(T x, T y, T z);
		void scaleInPlace(T x, T y, T z);
		void translate(T x, T y, T z);
		void rotateX(T radians);
		void rotateY(T radians);
		void rotateZ(T radians);
		void rotateFromOrigin(T radians);
		void rotateInPlace(T x, T y, T z);
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
	updateReferencePoint();
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
void Shape<T>::updateReferencePoint()
{
	if (!vectors.empty())
	{
		std::vector<T> limits;

		for (auto it = vectors.begin(); it != vectors.end(); ++it)
		{
			if (it == vectors.begin())
			{
				limits.emplace_back((*it)->getX());
				limits.emplace_back((*it)->getX());
				limits.emplace_back((*it)->getY());
				limits.emplace_back((*it)->getY());
				limits.emplace_back((*it)->getZ());
				limits.emplace_back((*it)->getZ());
			}
			else
			{
				if ((*it)->getX() < limits.at(0))
					limits.at(0) = (*it)->getX(); 
				if ((*it)->getX() > limits.at(1))
					limits.at(1) = (*it)->getX();
				if ((*it)->getY() < limits.at(2))
					limits.at(2) = (*it)->getY();
				if ((*it)->getY() > limits.at(3))
					limits.at(3) = (*it)->getY();
				if ((*it)->getZ() < limits.at(4))
					limits.at(4) = (*it)->getZ();
				if ((*it)->getZ() > limits.at(5))
					limits.at(5) = (*it)->getZ();
			}
		}

		T x_reference = (limits.at(1) - limits.at(0)) / 2 + limits.at(0);
		T y_reference = (limits.at(3) - limits.at(2)) / 2 + limits.at(2);
		T z_reference = (limits.at(5) - limits.at(4)) / 2 + limits.at(4);

		referencePoint = std::make_unique<Vector<T>>(x_reference, y_reference, z_reference);
	}
}

template <typename T>
void Shape<T>::scaleFromOrigin(T x, T y, T z)
{
	ScalingMatrix<T> s(4, 4, x, y, x);

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = s * *(it->get());

	updateReferencePoint();
}

template <typename T>
void Shape<T>::scaleInPlace(T x, T y, T z)
{
	TranslationMatrix<T> t1(4, 4, -referencePoint->getX(), -referencePoint->getY(), -referencePoint->getZ());
	ScalingMatrix<T> s(4, 4, x, y, x);
	TranslationMatrix<T> t2(4, 4, referencePoint->getX(), referencePoint->getY(), referencePoint->getZ());

	Matrix<T> p = t2 * s * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = p * *(it->get());
		
	updateReferencePoint();
}

template <typename T>
void Shape<T>::translate(T x, T y, T z)
{
	TranslationMatrix<T> t1(4, 4, x, y, z);

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = t1 * *(it->get());

	updateReferencePoint();
}

template <typename T>
void Shape<T>::rotateX(T radians)
{
	RotationMatrix<T> r1(4, 4, radians, 'X');

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = r1 * *(it->get());

	updateReferencePoint();
}

template <typename T>
void Shape<T>::rotateY(T radians)
{
	RotationMatrix<T> r1(4, 4, radians, 'Y');

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = r1 * *(it->get());

	updateReferencePoint();
}

template <typename T>
void Shape<T>::rotateZ(T radians)
{
	RotationMatrix<T> r1(4, 4, radians, 'Z');

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = r1 * *(it->get());

	updateReferencePoint();
}

template <typename T>
void Shape<T>::rotateFromOrigin(T radians)
{
	Vector<T> v(*vectors.at(4).get());

	T length = sqrt(pow(v.getZ(), 2) + pow(v.getX(), 2));

	T angleA = atan2(v.getZ(), v.getX());
	T angleB = (-atan2(v.getY(), length));

	RotationMatrix<T> r1(4, 4, angleA, 'Y');
	RotationMatrix<T> r2(4, 4, angleB, 'Z');
	RotationMatrix<T> r3(4, 4, radians, 'X');
	RotationMatrix<T> r4(4, 4, -angleB, 'Z');
	RotationMatrix<T> r5(4, 4, -angleA, 'Y');

	Matrix<T> r = r5 * r4 * r3 * r2 * r1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = r * *(it->get());

	updateReferencePoint();
}

template <typename T>
void Shape<T>::rotateInPlace(T x, T y, T z)
{
	TranslationMatrix<T> r1(4, 4, -referencePoint->getX(), -referencePoint->getY(), -referencePoint->getZ());
	//RotationMatrix<T> r2(4, 4, x, 'X');
	RotationMatrix<T> r3(4, 4, x, 'Z');
	//RotationMatrix<T> r4(4, 4, z, 'Z');
	TranslationMatrix<T> r5(4, 4, referencePoint->getX(), referencePoint->getY(), referencePoint->getZ());

	Matrix<T> r = r5 * r3 * r1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = r * *(it->get());

	updateReferencePoint();
}

template <typename T>
void Shape<T>::draw(Graphics& graphics)
{
	for (auto it = connections.begin(); it != connections.end(); ++it)
		graphics.drawLine(it->first->getX(), it->first->getY(), it->first->getZ(), it->second->getX(), it->second->getY(), it->second->getZ());
}

