
/// std
#include <iostream>
#include <string>
#include <chrono>




int main() {

	/// 10万文字の文字列を生成
	std::string srcString(100000, 'a');

	/// copyにかかる時間をchrono(マイクロ秒)で計測
	auto          copyStartTime = std::chrono::high_resolution_clock::now();
	std::string   copyStr       = srcString;
	auto          copyEndTime   = std::chrono::high_resolution_clock::now();

	/// moveにかかる時間
	auto          moveStartTime = std::chrono::high_resolution_clock::now();
	std::string&& moveStr       = std::move(srcString);
	auto          moveEndTime   = std::chrono::high_resolution_clock::now();



	/// consoleに結果をマイクロ秒で出力
	float copyDuration = std::chrono::duration<float, std::micro>(copyEndTime - copyStartTime).count();
	float moveDuration = std::chrono::duration<float, std::micro>(moveEndTime - moveStartTime).count();

	std::cout << "100000文字のcopyにかかる時間とmoveにかかる時間を計測" << std::endl;
	std::cout << "copy time: " << copyDuration << " μs" << std::endl;
	std::cout << "move time: " << moveDuration << " μs" << std::endl;

	return 0;
}
