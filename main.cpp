/// std
#include <stdio.h>
#include <memory>
#include <iostream>

#include "Polymorphism/Polymorphism.h"

int main() {

	/// ================================================
	/// 変数宣言
	/// ================================================

	Png png;
	Txt txt;
	Exe exe;

	/// ================================================
	/// 実行
	/// ================================================

	png.OpenFile();
	txt.OpenFile();
	exe.OpenFile();

	return 0;
}


