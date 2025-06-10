
#include "project/ecs/ECS.h"

class Player : public IEntity {};
class Enemy : public IEntity {};

class Transform : IComponent {};
class Collider : IComponent {};

int main() {
	ECS ecs;

	Player* player = ecs.generateEntity<Player>();
	Enemy* enemy = ecs.generateEntity<Enemy>();

	player->AddComponent<Transform>();
	enemy->AddComponent<Transform>();
	player->AddComponent<Collider>();

	return 0;
}