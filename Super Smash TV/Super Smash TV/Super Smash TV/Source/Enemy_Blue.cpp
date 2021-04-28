#include "Enemy_Blue.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Blue::Enemy_Blue(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,0,13,15 });
	fly.PushBack({ 17,0,13,15 });
	fly.PushBack({ 32,0,14,15 });

	currentAnim = &fly;

	path.PushBack({ -1.0f, -0.5f }, 30);
	path.PushBack({ -1.0f, 0.5f }, 10);
	path.PushBack({ -1.0f, 1.0f }, 10);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Blue::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
