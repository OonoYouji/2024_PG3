#include "ECS.h"

IEntity* ECS::generateEntity(const std::string& name) {
	return entityCollection.CreateEntity(name);
}
