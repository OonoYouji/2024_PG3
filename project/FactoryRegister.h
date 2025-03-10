#pragma once

#include <unordered_map>
#include <string>
#include <typeindex>
#include <functional>
#include <memory>


class Factory {
public:
	template<typename T>
	void Register() {
		std::string&& key = typeid(T).name();
		classRegistry_.emplace(key, std::type_index(typeid(T)));
		instanceRegistry_[key] = []() -> std::shared_ptr<void> {
			return std::make_shared<T>();
			};
	}

	std::shared_ptr<void> Create(const std::string& className) {
		auto it = instanceRegistry_.find(className);
		if (it != instanceRegistry_.end()) {
			return it->second();
		}
		return nullptr;
	}

private:
	std::unordered_map<std::string, std::type_index> classRegistry_;
	std::unordered_map<std::string, std::function<std::shared_ptr<void>()>> instanceRegistry_;
};


class FactoryRegister {
public:

	void Registers();
	
private:
	Factory factory_;
};

