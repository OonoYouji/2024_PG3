#include "Polymorphism.h"

#include <iostream>

void Png::OpenFile() {
	std::cout << "open file .png\ " << std::endl;
}

void Txt::OpenFile() {
	std::cout << "open file .txt\ " << std::endl;
}

void Exe::OpenFile() {
	std::cout << "open file .exe\ " << std::endl;
}
