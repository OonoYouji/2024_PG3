/// std
#include <iostream>
#include <string>

#include "Shape/Shape.h"

int main() {

	/// ================================================
	/// 変数宣言
	/// ================================================

	std::string inputString = "";


	/// ================================================
	/// 実行
	/// ================================================

	while(true) {
		std::cout << "input -> circle || rectangle" << std::endl;

		std::getline(std::cin, inputString);

		/// 入力がなかったら終了
		if(inputString.empty()) {
			break;
		}


		if(inputString == "circle" || inputString == "Circle") {
			std::cout << "    args -> radius" << std::endl;
			std::cout << "    ";

			std::string inputNum{};
			std::getline(std::cin, inputNum);

			if(!inputNum.empty()) {
				Circle circle(
					static_cast<float>(std::stoi(inputNum)) /// width
				);

				std::cout << "    ";
				circle.Size();
				circle.Draw();

			}
		}

		if(inputString == "rectangle" || inputString == "Rectangle") {
			std::cout << "    args -> width, height" << std::endl;
			std::cout << "    ";

			std::string inputNum{};
			std::getline(std::cin, inputNum);

			size_t spacePos = inputNum.find(",");

			if(spacePos != std::string::npos) {
				std::string beforeSpace = inputNum.substr(0, spacePos);
				std::string afterSpace  = inputNum.substr(spacePos + 1);

				Rectangle rectangle(
					static_cast<float>(std::stoi(beforeSpace)), /// width
					static_cast<float>(std::stoi(afterSpace))   /// height
				);

				std::cout << "    ";
				rectangle.Size();
				rectangle.Draw();

			}

		}



		std::cout << std::endl;

	}

	return 0;
}


