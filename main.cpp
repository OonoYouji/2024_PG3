#include <stdio.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <format>
#include <functional>


/// ================================================
/// 関数のプロトタイプ宣言
/// ================================================
int ShakeDice();

void PrintRight();
void PrintWorng();

void SetTimeout(std::function<void(void)> function, int timesecond);



int main() {

	/// ================================================
	/// 変数宣言
	/// ================================================

	int diceNum  = ShakeDice();
	int inputNum = -1;

	/// 正解、不正解を表示する関数のポインタ配列
	std::function<void(void)> wrPrintFuncPtrs[2] = {
		&PrintWorng,
		&PrintRight
	};

	/// 値の入力に使うラムダ式
	std::function<int(void)> NumberInputFunc = []() -> int {
		int result = 0;
		std::cin >> result;
		return result;
	};

	/// ================================================
	/// 実行
	/// ================================================

	printf("偶数と思うなら[1]を奇数と思うなら[2]を入力し[Enter]を押してください\n");

	
	inputNum = NumberInputFunc();
	printf(std::format("入力された番号 : {}", inputNum).c_str());

	/// 3秒待つ
	SetTimeout(wrPrintFuncPtrs[diceNum % 2 == inputNum - 1], 3);

	printf(std::format("ダイスを振った結果 = {}\n", diceNum).c_str());

	return 0;
}



/// ================================================
/// プロトタイプ宣言の定義
/// ================================================

int ShakeDice() {
	return rand() % 6 + 1;
}

void PrintRight() {
	printf("正解!!\n");
}

void PrintWorng() {
	printf("不正解...\n");
}

void SetTimeout(std::function<void(void)> function, int timesecond) {
	printf("\n");
	for(uint32_t i = 0u; i < static_cast<uint32_t>(timesecond); ++i) {
		printf(".");
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	printf("\n");

	function();
}
