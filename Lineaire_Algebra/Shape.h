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
	auto midPointSquare = std::make_unique<Vector<T>>((vectors.at(0)->getX() + vectors.at(2)->getX()) / 2, (vectors.at(0)->getY() + vectors.at(2)->getY()) / 2, (vectors.at(0)->getZ() + vectors.at(2)->getZ()) / 2); // Middle of piramid square
	auto midPointHeight = std::make_unique<Vector<T>>((midPointSquare->getX() + vectors.at(4)->getX()) / 2, (midPointSquare->getY() + vectors.at(4)->getY()) / 2, (midPointSquare->getZ() + vectors.at(4)->getZ()) / 2); // Middle of pirmaid height

	referencePoint = std::make_unique<Vector<T>>(midPointHeight->getX(), midPointHeight->getY(), midPointHeight->getZ());
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
void rotateAroundAxis(T radians, const Vector<T>& point_1, const Vector<T>& point_2)
{
	/*TranslationMatrix<T> t1(4, 4, -point.getX(), -point.getY(), -point.getZ());
	RotationMatrix<T> r1(4, 4, radians, axis);
	TranslationMatrix<T> t2(4, 4, point.getX(), point.getY(), point.getZ());

	Matrix<T> m = t2 * r1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();*/
}

template <typename T>
void Shape<T>::draw(Graphics& graphics)
{
	for (auto it = connections.begin(); it != connections.end(); ++it)
		graphics.drawLine(it->first->getX(), it->first->getY(), it->first->getZ(), it->second->getX(), it->second->getY(), it->second->getZ());
}

