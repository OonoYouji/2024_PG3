#include "EntityFactory.h"

EntityFactory::EntityFactory() {
	// Register default entity types
	Register("Player", []() { return std::make_unique<IEntity>(); });
	Register("Enemy", []() { return std::make_unique<IEntity>(); });
}

void EntityFactory::Register(const std::string& _name, Generater _generateFunc) {
	generators_[_name] = _generateFunc;
}

std::unique_ptr<IEntity> EntityFactory::Create(const std::string& _name) {
	auto itr = generators_.find(_name);
	if (itr != generators_.end()) {
		return itr->second();
	}

	return nullptr;
}
