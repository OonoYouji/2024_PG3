#include "EntityCollection.h"

IEntity* EntityCollection::CreateEntity(const std::string& _name) {
	auto entity = entityFactory_.Create(_name);
	if (entity) {
		IEntity* result = entity.get();
		entities_.push_back(std::move(entity));

		return result; // Return the raw pointer
	}

	return nullptr;
}
