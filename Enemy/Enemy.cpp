#include "Enemy.h"

/// std
#include <iostream>

void (Enemy::* Enemy::spFunctionTable[ENEMY_BEHAVIOR_COUNT])() = {
	&Enemy::Approach,
	&Enemy::Shoot,
	&Enemy::Withdrawal
};


void Enemy::Initialize() {
	behavior_ = ENEMY_BEHAVIOR_APPROACH;
}

void Enemy::Update() {
	(this->*spFunctionTable[behavior_])();
}


void Enemy::Approach() {
	std::cout << "change behavior approach" << std::endl;
	behavior_ = ENEMY_BEHAVIOR_SHOOT;
}

void Enemy::Shoot() {
	std::cout << "change behavior shoot" << std::endl;
	behavior_ = ENEMY_BEHAVIOR_WITHDRAWAL;
}

void Enemy::Withdrawal() {
	std::cout << "change behavior withdrawal" << std::endl;
	isFinish_ = true;
}
