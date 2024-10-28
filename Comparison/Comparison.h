#pragma once

/// std
#include <type_traits>


/// ===================================================
/// template Tの値を比較して小さいほうを返す関数を持つクラス
/// ===================================================
template<typename T1, typename T2>
class Comparison final {
public:
	/// ===================================================
	/// public : methods 
	/// ===================================================

	Comparison(T1 value1, T2 value2) : value1_(value1), value2_(value2) {}

	auto Result() {
		using Type = typename std::common_type<T1, T2>::type;
		Type min = (static_cast<Type>(value1_) < static_cast<Type>(value2_)) ? value1_ : value2_;
		return min;
	}

private:
	/// ===================================================
	/// private : objects
	/// ===================================================

	T1 value1_;
	T2 value2_;
};