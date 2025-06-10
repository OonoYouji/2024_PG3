#pragma once

#include <string>

#include "../component/ComponentCollection.h"

class IEntity {
public:

	std::string name;
	int id;

	ComponentCollection* componentCollection;


	template <typename T>
	T* AddComponent();

};

template<typename T>
inline T* IEntity::AddComponent() {
	return componentCollection->GetComponentArray<T>()->AddComponent(id, T{});
}
