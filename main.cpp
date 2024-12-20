/// std
#include <thread>
#include <iostream>





int main() {

	/// ================================================
	/// 変数宣言
	/// ================================================

	std::thread th1([]() { printf("Thread 1\n"); });
	th1.join();

	std::thread th2([]() { printf("Thread 2\n"); });
	th2.join();

	std::thread th3([]() { printf("Thread 3\n"); });
	th3.join();

	return 0;
}
