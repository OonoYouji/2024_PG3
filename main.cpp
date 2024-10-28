/// std
#include <stdio.h>
#include <memory>

/// entity
#include "Enemy/Enemy.h"

int main() {

	/// ================================================
	/// 変数宣言
	/// ================================================

	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
	enemy->Initialize();

	/// ================================================
	/// 実行
	/// ================================================

	while(!enemy->GetIsFinish()) {

		enemy->Update();
	}

	return 0;
}


