#include "Enemy_Red.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Red::Enemy_Red(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({ 0,0,13,15 });
	flyAnim.PushBack({ 17,0,13,15 });
	flyAnim.PushBack({ 32,0,14,15 });

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Red::Update()
{
	waveRatio += waveRatioSpeed;

	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));
	position.x -= 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
