/// std
#include <stdio.h>
#include <memory>
#include <iostream>

#include "Comparison/Comparison.h"

int main() {

	/// ================================================
	/// 変数宣言
	/// ================================================

	Comparison com1 = Comparison<int,    float> (1, 1.2f);
	Comparison com2 = Comparison<double, float> (3.145654, 2135.0f);
	Comparison com3 = Comparison<double, int>   (3.145654, 2);
	Comparison com4 = Comparison<int,    int>   (1, 5);
	Comparison com5 = Comparison<float,  float> (2.45f, 1.2f);
	Comparison com6 = Comparison<double, double>(165.565, 265.16546);

	/// ================================================
	/// 実行
	/// ================================================

	std::cout << "result : " << com1.Min() << std::endl;
	std::cout << "result : " << com2.Min() << std::endl;
	std::cout << "result : " << com3.Min() << std::endl;
	std::cout << "result : " << com4.Min() << std::endl;
	std::cout << "result : " << com5.Min() << std::endl;
	std::cout << "result : " << com6.Min() << std::endl;

	return 0;
}


