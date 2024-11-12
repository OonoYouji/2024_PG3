#include "Shape.h"

#include <numbers>
#include <iostream>
//
//void IShape::Draw() {
//	std::cout << "shape size : " << size_ << std::endl;
//}

void Circle::Size() {
	size_ = radius_ * radius_ * std::numbers::pi_v<float>;
}

void Circle::Draw() {
	std::cout << "shape size : " << size_ << std::endl;
}



void Rectangle::Size() {
	size_ = width_ * height_;
}

void Rectangle::Draw() {
	std::cout << "shape size : " << size_ << std::endl;
}
