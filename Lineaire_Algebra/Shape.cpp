#include "Shape.h"
#include "Vector.h"
#include "Matrix.h"
#include "TranslationMatrix.h"
#include "ScalingMatrix.h"
#include "RotationMatrix.h"

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
	float reference[3] = { 0,0,0 };

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
	{
		reference[0] += (*it)->getX();
		reference[1] += (*it)->getY();
		reference[2] += (*it)->getZ();
	}

	referencePoint = std::make_unique<Vector>(reference[0] / 8, reference[1] / 8, reference[2] / 8);
}

void Shape::scaleInPlace(float x, float y, float z)
{
	TranslationMatrix t1(4, 4, -referencePoint->getX(), -referencePoint->getY(), -referencePoint->getZ());
	ScalingMatrix s1(4, 4, x, y, x);
	TranslationMatrix t2(4, 4, referencePoint->getX(), referencePoint->getY(), referencePoint->getZ());

	Matrix m = t2 * s1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

void Shape::scaleFromPoint(float x, float y, float z, const Vector& point)
{
	TranslationMatrix t1(4, 4, -point.getX(), -point.getY(), -point.getZ());
	ScalingMatrix s1(4, 4, x, y, x);
	TranslationMatrix t2(4, 4, point.getX(), point.getY(), point.getZ());

	Matrix m = t2 * s1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

void Shape::rotateInPlace(float radians, char axis)
{
	TranslationMatrix t1(4, 4, -referencePoint->getX(), -referencePoint->getY(), -referencePoint->getZ());
	RotationMatrix r1(4, 4, radians, axis);
	TranslationMatrix t2(4, 4, referencePoint->getX(), referencePoint->getY(), referencePoint->getZ());

	Matrix m = t2 * r1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

void Shape::rotateAroundPoint(float radians, char axis, const Vector& point)
{
	TranslationMatrix t1(4, 4, -point.getX(), -point.getY(), -point.getZ());
	RotationMatrix r1(4, 4, radians, axis);
	TranslationMatrix t2(4, 4, point.getX(), point.getY(), point.getZ());

	Matrix m = t2 * r1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

void Shape::rotateAroundAxis(float radians, const Vector& point_1, const Vector& point_2)
{
	auto newVector = std::make_unique<Vector>(point_2.getX() - point_1.getX(), point_2.getY() - point_1.getY(), point_2.getZ() - point_1.getZ());
	float length = sqrt(pow(newVector->getX(), 2) + pow(newVector->getY(), 2) + pow(newVector->getZ(), 2)); // Lenght of vector

	float angle_1 = atan((point_2.getZ() - point_1.getZ()) / (point_2.getX() - point_1.getX())); // Rotation to XY Surface
	float angle_2 = -asin((point_2.getY() - point_1.getY()) / length); // Rotation to X Axis

	//T angle_1 = 0.78539816339744828;
	//T angle_2 = -0.78539816339744828;

	TranslationMatrix t1(4, 4, -point_1.getX(), -point_1.getY(), -point_1.getZ());
	RotationMatrix r1(4, 4, angle_1, 'Y');
	RotationMatrix r2(4, 4, angle_2, 'Z');
	RotationMatrix r3(4, 4, radians, 'X');
	RotationMatrix r4(4, 4, -angle_2, 'Z');
	RotationMatrix r5(4, 4, -angle_1, 'Y');
	TranslationMatrix t2(4, 4, point_1.getX(), point_1.getY(), point_1.getZ());

	Matrix m = t2 * r5 * r4 * r3 * r2 * r1 * t1;
	//Matrix<T> m = r2 * r1 * t1;

	for (auto it = vectors.begin(); it != vectors.end(); ++it)
		** it = m * **it;

	updateReferencePoint();
}

void Shape::draw(Graphics& graphics)
{
	for (auto it = connections.begin(); it != connections.end(); ++it)
		graphics.drawLine(it->first->getX(), it->first->getY(), it->first->getZ(), it->second->getX(), it->second->getY(), it->second->getZ());
}