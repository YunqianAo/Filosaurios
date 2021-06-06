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

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Red::Update()
{
	movementDelay++;
	spawntimer++;

	if (spawntimer <= 1) {
		switch (App->sceneLevel->i) {
		case 0:
			position.y -= 1;
			currentAnim = &red_up;
			break;
		case 1:
			position.y += 1;
			currentAnim = &red_down;
			break;
		case 2:
			position.x += 1;
			currentAnim = &red_r;
			break;
		case 3:
			position.x -= 1;
			currentAnim = &red_l;
			break;
		}
	}

	else if (spawntimer <= 1) {
		switch (App->sceneLevel2->i) {
		case 0:
			position.y -= 1;
			currentAnim = &red_up;
			break;
		case 1:
			position.y += 1;
			currentAnim = &red_down;
			break;
		case 2:
			position.x += 1;
			currentAnim = &red_r;
			break;
		case 3:
			position.x -= 1;
			currentAnim = &red_l;
			break;
		}
	}

	if (movementDelay >= 3 && spawntimer > 1 && movedelay == 0) {
		if (position.x - App->player->position.x < 0)			//right
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &red_r) {
				currentAnim = &red_r;
			}
			position.x += 1.25;
		}
		else if (position.x - App->player->position.x > 0)		//left
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &red_l) {
				currentAnim = &red_l;
			}
			position.x -= 1.25;
		}
		else {
			movementDirections = 0;
		}

		if (position.y - App->player->position.y < 0)			//down
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &red_down) {
				currentAnim = &red_down;
			}
			position.y += 1.25;
		}
		else if (position.y - App->player->position.y > 0)		//up
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &red_up) {
				currentAnim = &red_up;
			}
			position.y -= 1.25;
		}
		else {
			movementDirections = 0;
		}

		movementDelay = 0;
	}

	Enemy::Update();
}