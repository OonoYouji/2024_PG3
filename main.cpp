#include <stdio.h>
#include <format>



template <typename T>
T Min(T a, T b) {
	return a < b ? a : b;
}

template<>
char Min(char a, char b) {
	printf("数字以外は代入できません\n");
	return 0;
}


int main() {

	printf(std::format("int    min = {}\n", Min<int>(4, 5)).c_str());
	printf(std::format("float  min = {}\n", Min<float>(2.0f, 0.4f)).c_str());
	printf(std::format("double min = {}\n", Min<double>(3.14, 0.35)).c_str());

	Min<char>('a', 'b');

	return 0;
}


