#include "Enemy_Red.h"

#include"ModuleTextures.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "SceneLevel.h"
#include "SceneLevel2.h"
#include "ModuleParticles.h"
#include <time.h>
#include <stdlib.h>

Enemy_Red::Enemy_Red(int x, int y) : Enemy(x, y)
{
	red_up.PushBack({ 0,16 + 128,16,16 });
	red_up.PushBack({ 16,16 + 128,16,16 });
	red_up.PushBack({ 32,16 + 128,16,16 });
	red_up.speed = 0.05f;

	red_down.PushBack({ 48, 16+ 128,16,16 });
	red_down.PushBack({ 64, 16 + 128,16,16 });
	red_down.speed = 0.05f;

	red_r.PushBack({ 0,128,16,16 });
	red_r.PushBack({ 16,128,16,16 });
	red_r.PushBack({ 32,128,16,16 });
	red_r.speed = 0.05f;

	red_l.PushBack({ 48,128,16,16 });
	red_l.PushBack({ 64,128,16,16 });
	red_l.PushBack({ 80,128,16,16 });
	red_l.speed = 0.05f;

	path.PushBack({ -0.3f, 0.0f }, 150, &red_r);
	path.PushBack({ 1.2f, 0.0f }, 150, &red_l);

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Red::Update()
{
	
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	//if (position.y < 47)
	//{
	//	if (position.x <= 25) {
	//		position.x -= 1.0f;
	//	}
	//	position.x += 1.0f;

	//	currentAnim = &red_r;
	//}
	//else if (position.x > 230)
	//{

	//	position.y += 1.0f;
	//	
	//	currentAnim = &red_r;
	//}
	//else if (position.y > 210)
	//{
	//	if (position.x > 230) {
	//		position.x -= 2.0f;
	//	}
	//	position.x -= 1.0f;
	//	currentAnim = &red_l;
	//}
	//else if (position.x < 25)
	//{
	//	position.y -= 1.0f;
	//	currentAnim = &red_up;
	//}


	Enemy::Update();
}