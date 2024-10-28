#include "Shape.h"

#include <iostream>

void IShape::Draw() {
	std::cout << "shape size : " << size_ << std::endl;
}
