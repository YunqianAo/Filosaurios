#include "Enemy_Green.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Green::Enemy_Green(int x, int y) : Enemy(x, y)
{
	green_up.PushBack({ 16,16,16,16 });
	green_up.PushBack({ 32,16,16,16 });
	green_up.PushBack({ 48,16,16,16 });
	green_up.speed = 0.2f;

	green_down.PushBack({ 64,16,16,16 });
	green_down.PushBack({ 80,16,16,16 });
	green_down.speed = 0.2f;

	green_r.PushBack({ 16,0,16,16 });
	green_r.PushBack({ 32,0,16,16 });
	green_r.PushBack({ 48,0,16,16 });
	green_r.speed = 0.2f;

	green_l.PushBack({ 16,16,16,16 });
	green_l.PushBack({ 32,16,16,16 });
	green_l.PushBack({ 48,16,16,16 });
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

