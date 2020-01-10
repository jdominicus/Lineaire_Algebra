#include "Shape.h"
#include "Vector.h"
#include "Matrix.h"
#include "TranslationMatrix.h"
#include "ScalingMatrix.h"
#include "RotationMatrix.h"
#include <corecrt_math_defines.h>

Shape::Shape() : referencePoint(nullptr)
{
}

Shape::~Shape()
{
}

void Shape::addVector(std::unique_ptr<Vector> vector)
{
	vectors.emplace_back(std::move(vector));
}

void Shape::addConnection(int index_1, int index_2)
{
	auto pair = std::make_pair(vectors.at(index_1).get(), vectors.at(index_2).get());
	connections.insert(pair);
}

std::vector<std::unique_ptr<Vector>>& Shape::getVectors()
{
	return vectors;
}

Vector* Shape::getReferencePoint()
{
	return referencePoint.get();
}

void Shape::setReferencePoint()
{
	updateReferencePoint();
}

void Shape::updateReferencePoint()
{
	double reference[3] = { 0,0,0 };

	for (int i = 0; i < vectors.size(); i++)
	{
		reference[0] += vectors.at(i)->getX();
		reference[1] += vectors.at(i)->getY();
		reference[2] += vectors.at(i)->getZ();
	}

	referencePoint = std::make_unique<Vector>(reference[0] / vectors.size(), reference[1] / vectors.size(), reference[2] / vectors.size());
}

void Shape::translate(double x, double y, double z)
{
	TranslationMatrix t1(4, 4, x, y, z);
	
	Matrix m = t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

void Shape::scaleInPlace(double x, double y, double z)
{
	TranslationMatrix t1(4, 4, -referencePoint->getX(), -referencePoint->getY(), -referencePoint->getZ());
	ScalingMatrix s1(4, 4, x, y, x);
	TranslationMatrix t2(4, 4, referencePoint->getX(), referencePoint->getY(), referencePoint->getZ());

	Matrix m = t2 * s1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

void Shape::scaleFromPoint(double x, double y, double z, const Vector& point)
{
	TranslationMatrix t1(4, 4, -point.getX(), -point.getY(), -point.getZ());
	ScalingMatrix s1(4, 4, x, y, x);
	TranslationMatrix t2(4, 4, point.getX(), point.getY(), point.getZ());

	Matrix m = t2 * s1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

void Shape::rotateInPlace(double radians, char axis)
{
	TranslationMatrix t1(4, 4, -referencePoint->getX(), -referencePoint->getY(), -referencePoint->getZ());
	RotationMatrix r1(4, 4, radians, axis);
	TranslationMatrix t2(4, 4, referencePoint->getX(), referencePoint->getY(), referencePoint->getZ());

	Matrix m = t2 * r1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

void Shape::rotateAroundPoint(double radians, char axis, const Vector& point)
{
	TranslationMatrix t1(4, 4, -point.getX(), -point.getY(), -point.getZ());
	RotationMatrix r1(4, 4, radians, axis);
	TranslationMatrix t2(4, 4, point.getX(), point.getY(), point.getZ());

	Matrix m = t2 * r1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

void Shape::rotateAroundAxis(double radians, const Vector& point_1, const Vector& point_2) // point_1 = translatedPoint, point_2 is rotatedPoint
{
	auto newVector = std::make_unique<Vector>(point_2.getX() - point_1.getX(), point_2.getY() - point_1.getY(), point_2.getZ() - point_1.getZ());
	
	double angle_1 = newVector->getX() != 0 ? atan(newVector->getZ() / newVector->getX()) : 0;
	double angle_2 = acos(sqrt(pow(newVector->getX(), 2) + pow(newVector->getZ(), 2)) / sqrt(pow(newVector->getX(), 2) + pow(newVector->getY(), 2) + pow(newVector->getZ(), 2)));

	TranslationMatrix t1(4, 4, -point_1.getX(), -point_1.getY(), -point_1.getZ());
	RotationMatrix r1(4, 4, angle_1, 'Y');
	RotationMatrix r2(4, 4, -angle_2, 'Z');
	RotationMatrix r3(4, 4, radians, 'X');
	RotationMatrix r4(4, 4, angle_2, 'Z');
	RotationMatrix r5(4, 4, -angle_1, 'Y');
	TranslationMatrix t2(4, 4, point_1.getX(), point_1.getY(), point_1.getZ());

	Matrix m = t2 * r5 * r4 * r3 * r2 * r1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

void Shape::draw(Graphics& graphics)
{
	for (auto it = connections.begin(); it != connections.end(); ++it)
		graphics.drawLine(it->first->getX(), it->first->getY(), it->first->getZ(), it->second->getX(), it->second->getY(), it->second->getZ());
}