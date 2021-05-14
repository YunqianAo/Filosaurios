#include "Enemy_Pink.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Pink::Enemy_Pink(int x, int y) : Enemy(x, y)
{
	pink_up.PushBack({ 16,16,16,16 });
	pink_up.PushBack({ 32,16,16,16 });
	pink_up.PushBack({ 48,16,16,16 });
	pink_up.speed = 0.2f;

	pink_down.PushBack({ 64,16,16,16 });
	pink_down.PushBack({ 80,16,16,16 });	
	pink_down.speed = 0.2f;

	pink_r.PushBack({ 16,0,16,16 });
	pink_r.PushBack({ 32,0,16,16 });
	pink_r.PushBack({ 48,0,16,16 });
	pink_r.speed = 0.2f;

	pink_l.PushBack({ 16,16,16,16 });
	pink_l.PushBack({ 32,16,16,16 });
	pink_l.PushBack({ 48,16,16,16 });
	pink_l .speed = 0.2f;

	path.PushBack({ -0.3f, 0.0f }, 150, &pink_r);
	path.PushBack({ 0.0f, -0.3f }, 150, &pink_down);
	path.PushBack({ 1.2f, 0.0f }, 150, &pink_l);
	path.PushBack({ 0.0f, 1.2f }, 150, &pink_up);

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Pink::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
