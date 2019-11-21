#pragma once
#include <memory>

template <typename>
class Vector;

template <typename>
class Matrix;

template <typename T>
class Camera
{
public:
	Camera();
	Camera(std::unique_ptr<Vector<T>> location);
	Vector<T>* getLocation() { return location_.get(); }
	void goDown() {
		*location_ += *(std::make_unique<Vector<T>>(0, 10, 0));
		(*eye_)(0, 1) += 10;
		(*lookAt_)(0, 1) += 10;
	}
	void goUp() {
		*location_ -= *(std::make_unique<Vector<T>>(0, 10, 0));
		(*eye_)(0, 1) -= 10;
		(*lookAt_)(0, 1) -= 10;
	}
	void goLeft() {
		*location_ -= *(std::make_unique<Vector<T>>(10, 0, 0));
		(*eye_)(0, 0) -= 10;
		(*lookAt_)(0, 0) -= 10;
	}
	void goRight() {
		*location_ += *(std::make_unique<Vector<T>>(10, 0, 0));
		(*eye_)(0, 0) += 10;
		(*lookAt_)(0, 0) += 10;
	}
	void update() {
		direction_ = std::make_unique<Matrix<double>>(*eye_ - *lookAt_);
		auto tempUp = std::make_unique<Matrix<double>>(1, 4);
		(*tempUp)(0, 0) = 0;
		(*tempUp)(0, 1) = 1;
		(*tempUp)(0, 2) = 0;
		(*tempUp)(0, 3) = 1;
		right_ = std::make_unique<Matrix<double>>(*up_ * *direction_);
		up_ = std::make_unique<Matrix<double>>(*direction_ * *right_);
	}
private:
	std::unique_ptr<Vector<T>> location_;
	std::unique_ptr<Matrix<T>> eye_;
	std::unique_ptr<Matrix<T>> lookAt_;
	std::unique_ptr<Matrix<T>> direction_;
	std::unique_ptr<Matrix<T>> up_;
	std::unique_ptr<Matrix<T>> right_;
};

template <typename T>
Camera<T>::Camera()
{
	eye_ = std::make_unique<Matrix<double>>(1, 4);
	(*eye_)(0, 0) = 0;
	(*eye_)(0, 1) = 0;
	(*eye_)(0, 2) = 0;
	(*eye_)(0, 3) = 1;
	lookAt_ = std::make_unique<Matrix<double>>(1, 4);
	(*lookAt_)(0, 0) = 0;
	(*lookAt_)(0, 1) = 0;
	(*lookAt_)(0, 2) = -10;
	(*lookAt_)(0, 3) = 1;
	update();
}

template <typename T>
Camera<T>::Camera(std::unique_ptr<Vector<T>> location) {
	location_ = std::move(location);
}

