#pragma once

#include <string>

#include "entity/EntityCollection.h"
#include "component/ComponentCollection.h"
#include "system/ISystem.h"

class ECS {
public:
	ECS() = default;
	~ECS() = default;


	IEntity* generateEntity(const std::string& name);

	template <typename T>
	T* generateEntity();


private:
	EntityCollection entityCollection;
	ComponentCollection componentCollection;

};

template<typename T>
inline T* ECS::generateEntity() {
	std::string name = typeid(T).name();
	if (name.find("class ") == 0) {
		name = name.substr(6); // Remove "class " prefix
	} else if (name.find("struct ") == 0) {
		name = name.substr(7); // Remove "struct " prefix
	}

	T* entity = static_cast<T*>(entityCollection.CreateEntity(name));
	if (!entity) {
		return nullptr; // Handle case where entity creation fails
	}

	entity->componentCollection = &componentCollection; // Set the component collection for the entity

	return entity;
}
