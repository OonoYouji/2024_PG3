#include <stdio.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <format>


/// ================================================
/// 関数ポインタのtypedef化
/// ================================================
typedef void (*return_void_args_none)();
typedef void (*return_void_args_funcPtr_Int)(return_void_args_none, int);


/// ================================================
/// 関数のプロトタイプ宣言
/// ================================================
void TmpFunc() {};
void SleepExe(return_void_args_none* callbackFunc,int timesecond);
int ShakeDice();

void PrintRight();
void PrintWorng();


int main() {

	/// ================================================
	/// 変数宣言
	/// ================================================

	enum RIGHT_OR_WORNG {
		RIGHT, WORNG
	};

	int diceNum  = ShakeDice();
	int inputNum = -1;

	/// 正解、不正解を表示する関数のポインタ配列
	return_void_args_none funcPtrs[2] = {
		&PrintWorng,
		&PrintRight
	};


	/// ================================================
	/// 実行
	/// ================================================

	printf("偶数と思うなら[1]を奇数と思うなら[2]を入力し[Enter]を押してください\n");

	std::cin >> inputNum;
	printf(std::format("入力された番号 : {}", inputNum).c_str());

	/// 3秒待つ
	SleepExe(&funcPtrs[diceNum % 2 == inputNum - 1], 3);

	printf(std::format("ダイスを振った結果 = {}\n", diceNum).c_str());

	return 0;
}



/// ================================================
/// プロトタイプ宣言の定義
/// ================================================

void SleepExe(return_void_args_none* callbackFunc,int timesecond) {
	printf("\n");
	for(uint32_t i = 0u; i < timesecond; ++i) {
		printf(".");
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	printf("\n");

	(*callbackFunc)();
}

int ShakeDice() {
	return rand() % 6 + 1;
}

void PrintRight() {
	printf("正解!!\n");
}

void PrintWorng() {
	printf("不正解...\n");
}
