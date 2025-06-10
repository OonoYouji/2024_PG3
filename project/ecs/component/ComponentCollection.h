#pragma once

#include <vector>
#include <memory>

#include "ComponentArray.h"

class ComponentCollection {
public:

	ComponentCollection() = default;
	~ComponentCollection() = default;

	template <typename T>
	void RegisterComponentArray() {
		componentArrays_.emplace_back(std::make_unique<ComponentArray<T>>());
	}

	template <typename T>
	ComponentArray<T>* GetComponentArray() {
		for (auto& array : componentArrays_) {
			if (auto* componentArray = dynamic_cast<ComponentArray<T>*>(array.get())) {
				return componentArray;
			}
		}
		return nullptr;
	}

	template <typename T>
	T* AddComponent(int entityId, const T& component) {
		auto* componentArray = GetComponentArray<T>();
		if (componentArray) {
			return componentArray->AddComponent(entityId, component);
		}
		return nullptr;
	}

private:
	std::vector<std::unique_ptr<IComponentArray>> componentArrays_;
};


