#pragma once

#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <iostream>

#include "Vector.h"
#include "Matrix.h"
#include "TranslationMatrix.h"
#include "ScalingMatrix.h"

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
		void scaleFromOrigin(T x, T y, T z);
		void scaleInPlace(T x, T y, T z);
		void translate(T x, T y, T z);
		void rotate(T radians);
		void updateMidPoint();
		void printMidPoint() const;
		void draw(Graphics& graphics);

	private:
		std::vector<std::unique_ptr<Vector<T>>> vectors;
		std::multimap<Vector<T>*, Vector<T>*> connections;
		std::unique_ptr<Vector<T>> midPoint;
};

template <typename T>
Shape<T>::Shape()
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
void Shape<T>::scaleFromOrigin(T x, T y, T z)
{
	ScalingMatrix<T> s(4, 4, x, y, x);

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = s * *(it->get());

	updateMidPoint();
}

template <typename T>
void Shape<T>::scaleInPlace(T x, T y, T z)
{
	TranslationMatrix<T> t1(4, 4, -midPoint->getX(), -midPoint->getY(), -midPoint->getZ());
	ScalingMatrix<T> s(4, 4, x, y, x);
	TranslationMatrix<T> t2(4, 4, midPoint->getX(), midPoint->getY(), midPoint->getZ());

	Matrix<T> p = t2 * s * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = p * *(it->get());

	updateMidPoint();
}

template <typename T>
void Shape<T>::translate(T x, T y, T z)
{
	TranslationMatrix<T> t1(4, 4, x, y, z);

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = t1 * *(it->get());

	updateMidPoint();
}

template <typename T>
void Shape<T>::rotate(T radians)
{
	Matrix<T> m(2, 2);
	m(0, 0) = cos(radians);
	m(0, 1) = -sin(radians);
	m(1, 0) = sin(radians);
	m(1, 1) = cos(radians);

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = m * *(it->get());

}

template <typename T>
void Shape<T>::updateMidPoint()
{
	T y = vectors.at(4)->getY() + vectors.at(0)->getY() * 0.25;
	T x = (vectors.at(1)->getX() + vectors.at(0)->getX()) / 2;
	T z = (vectors.at(2)->getZ() + vectors.at(1)->getZ()) / 2;

	midPoint = std::make_unique<Vector<T>>(x, y, z);
}

template <typename T>
void Shape<T>::printMidPoint() const
{
	if (midPoint)
	std::cout << midPoint.get()->getX() << " " << midPoint.get()->getY() << " " << midPoint.get()->getZ() << std::endl;
}

template <typename T>
void Shape<T>::draw(Graphics& graphics)
{
	for (auto it = connections.begin(); it != connections.end(); ++it)
		graphics.drawLine(it->first->getX(), it->first->getY(), it->first->getZ(), it->second->getX(), it->second->getY(), it->second->getZ());
}

