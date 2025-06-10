#pragma once

#include "EntityFactory.h"

class EntityCollection {
public:

	EntityCollection() = default;
	~EntityCollection() = default;

	IEntity* CreateEntity(const std::string& _name);


private:
	EntityFactory entityFactory_;
	std::vector<std::unique_ptr<IEntity>> entities_;
};

