#pragma once

#include <vector>
#include <map>
#include <memory>
#include <utility>

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
		void scaleFromOrigin(float x, float y);
		void scaleInPlace(T x, T y);
		void translate(float x, float y);
		void rotate(T radians);
		void draw(Graphics& graphics);

	private:
		std::vector<std::unique_ptr<Vector<T>>> vectors;
		std::map<Vector<T>*, Vector<T>*> connections;
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
void Shape<T>::scaleFromOrigin(float x, float y)
{
	Matrix<T> m(2, 2);
	m(0, 0) = x;
	m(1, 1) = y;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = m * *(it->get());
}

template <typename T>
void Shape<T>::scaleInPlace(T x, T y)
{
	Matrix<T> translation(3, 3);
	translation(0, 0) = 1;
	translation(1, 1) = 1;
	translation(2, 2) = 1;
	translation(0, 2) = -75;
	translation(1, 2) = -75;

	Matrix<T> scale(3, 3);
	scale(0, 0) = x;
	scale(1, 1) = y;
	scale(2, 2) = 1;

	Matrix<T> translation2(3, 3);
	translation2(0, 0) = 1;
	translation2(1, 1) = 1;
	translation2(2, 2) = 1;
	translation2(0, 2) = 75;
	translation2(1, 2) = 75;

	Matrix<T> p = translation2 * scale * translation;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = p * *(it->get());
}

template <typename T>
void Shape<T>::translate(float x, float y)
{
	Matrix<T> m(3, 3);
	m(0, 0) = 1;
	m(1, 1) = 1;
	m(2, 2) = 1;
	m(0, 2) = x;
	m(1, 2) = y;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		*(it->get()) = m * *(it->get());
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
void Shape<T>::draw(Graphics& graphics)
{
	for (auto it = connections.begin(); it != connections.end(); ++it)
		graphics.drawLine(it->first->getLenght(), it->first->getDirection(), it->second->getLenght(), it->second->getDirection());
}

