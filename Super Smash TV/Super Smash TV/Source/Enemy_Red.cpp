#include "Enemy_Red.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Red::Enemy_Red(int x, int y) : Enemy(x, y)
{
	red_up.PushBack({ 16,16,16,16 });
	red_up.PushBack({ 32,16,16,16 });
	red_up.PushBack({ 48,16,16,16 });
	red_up.speed = 0.2f;

	red_down.PushBack({ 64,16,16,16 });
	red_down.PushBack({ 80,16,16,16 });
	red_down.speed = 0.2f;

	red_r.PushBack({ 16,0,16,16 });
	red_r.PushBack({ 32,0,16,16 });
	red_r.PushBack({ 48,0,16,16 });
	red_r.speed = 0.2f;

	red_l.PushBack({ 16,16,16,16 });
	red_l.PushBack({ 32,16,16,16 });
	red_l.PushBack({ 48,16,16,16 });
	red_l.speed = 0.2f;

	path.PushBack({ -0.3f, 0.0f }, 150, &red_r);
	path.PushBack({ 0.0f, -0.3f }, 150, &red_down);
	path.PushBack({ 1.2f, 0.0f }, 150, &red_l);
	path.PushBack({ 0.0f, 1.2f }, 150, &red_up);

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);
}
bool Enemy_Red::Start() {

}
void Enemy_Red::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}