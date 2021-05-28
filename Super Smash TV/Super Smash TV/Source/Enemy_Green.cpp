#include "Enemy_Green.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Green::Enemy_Green(int x, int y) : Enemy(x, y)
{
	green_up.PushBack({ 2,48,11,15 });
	green_up.PushBack({ 17,48,13,15 });
	green_up.speed = 0.2f;

	green_down.PushBack({ 2,48,11,15 });
	green_down.PushBack({ 17,48,13,15 });
	green_down.speed = 0.2f;

	green_r.PushBack({ 1,17,14,14 });
	green_r.PushBack({ 16,16,15,14 });
	green_r.speed = 0.2f;

	green_l.PushBack({ 0,80,15,95 });
	green_l.PushBack({ 16,81,14,14 });
	green_l.speed = 0.2f;

	path.PushBack({ -0.3f, 0.0f }, 150, &green_r);
	path.PushBack({ 0.0f, -0.3f }, 150, &green_down);
	path.PushBack({ 1.2f, 0.0f }, 150, &green_l);
	path.PushBack({ 0.0f, 1.2f }, 150, &green_up);

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Green::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

