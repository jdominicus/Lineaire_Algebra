#pragma once
#include <memory>
class Shape;
class Graphics;
class Planet
{
public:
	Planet();
	~Planet();
	void update(float time);
	void draw(Graphics& graphics);
private:
	std::unique_ptr<Shape> shape_;
	bool growing_;
	double time_;
	double growingFactor_;
	double radius_;

	const double pi = 3.14159265359;
};

