#pragma once
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <variant>



struct Vec3 {
	float x, y, z;
};

struct Vec2 {
	float x, y;
};

struct Color {
	float r, g, b, a;
};


/// @brief 変数
using variable = std::variant<int, double, std::string, Vec3, Vec2, Color>;


class Variables {
public:
	Variables() = default;
	~Variables() = default;

	/// @brief 変数を追加する
	/// @param name 変数名
	void Add(const std::string& _name, const variable& _value) {
		if (Has(_name)) {
			throw std::runtime_error("変数がすでに存在します");
		}
		variables_[_name] = _value;
	}

	/// @brief 変数を取得する
	/// @param name 変数名
	template<typename T>
	T Get(const std::string& _name) {
		if (Has(_name)) {
			throw std::runtime_error("変数が見つかりません");
		}
		return std::get<T>(variables_.find(_name)->second);
	}

	/// @brief 変数を設定する
	/// @param name 変数名
	void Set(const std::string& _name, const variable& _value) {
		auto it = variables_.find(_name);
		if (it == variables_.end()) {
			throw std::runtime_error("変数が見つかりません");
		}
		it->second = _value;
	}

	/// @brief 変数が存在するか
	/// @param name 変数名
	/// @return 存在するか
	bool Has(const std::string& _name) {
		return variables_.contains(_name);
	}

	/// @brief 変数を削除する
	/// @param name 変数名
	void Remove(const std::string& _name) {
		variables_.erase(_name);
	}


private:
	std::unordered_map<std::string, variable> variables_;


public:

	/// @brief 変数を取得する
	/// @return 変数
	const std::unordered_map<std::string, variable>& GetVariables() const {
		return variables_;
	}

};