#pragma once

#include <vector>

#include "IComponent.h"

class IComponentArray {
public:
	virtual ~IComponentArray() = default;
};


template <typename T>
class ComponentArray : public IComponentArray {
public:

	ComponentArray() = default;
	~ComponentArray() = default;
	
	T* AddComponent(int entityId, T component) {
		components_[entityId] = component;
		return &components_[entityId];
	}

	T* GetComponent(int entityId) {
		return &components_[entityId];
	}

	void RemoveComponent(int entityId) {
		components_.erase(entityId);
	}

private:
	std::vector<T> components_;
};

