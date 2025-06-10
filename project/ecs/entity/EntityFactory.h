#pragma once

#include <string>
#include <functional>
#include <memory>
#include <unordered_map>

#include "IEntity.h"

using Generater = std::function<std::unique_ptr<IEntity>()>;

class EntityFactory {
public:
	EntityFactory();

	void Register(const std::string& _name, Generater _generateFunc);

	std::unique_ptr<IEntity> Create(const std::string& _name);

private:
	std::unordered_map<std::string, Generater> generators_;
};

