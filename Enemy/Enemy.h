#pragma once

/// ===================================================
/// 敵の振る舞いのenum
/// ===================================================
enum ENEMY_BEHAVIOR : size_t {
	ENEMY_BEHAVIOR_APPROACH,   /// 接近
	ENEMY_BEHAVIOR_SHOOT,	   /// 発射
	ENEMY_BEHAVIOR_WITHDRAWAL, /// 離脱
	ENEMY_BEHAVIOR_COUNT       /// enumの要素カウント用
};


/// ===================================================
/// 敵のクラス
/// ===================================================
class Enemy final {
public:
	/// ===================================================
	/// public : methods
	/// ===================================================

	void Initialize();
	void Update();


	/// <summary>
	/// 接近関数
	/// </summary>
	void Approach();

	/// <summary>
	/// 発射関数
	/// </summary>
	void Shoot();

	/// <summary>
	/// 離脱関数
	/// </summary>
	void Withdrawal();


	/// <summary>
	/// 終了したかのフラグのゲッタ
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() const { return isFinish_; }


private:
	/// ===================================================
	/// private : objects
	/// ===================================================

	size_t behavior_;

	static void (Enemy::*spFunctionTable[ENEMY_BEHAVIOR_COUNT])();


	/// 振る舞いが最後まで終了したらtrueにする
	bool isFinish_;

};