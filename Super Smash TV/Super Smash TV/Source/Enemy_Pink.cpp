#include "Enemy_Pink.h"
#include "ModuleTextures.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "SceneLevel.h"
#include "ModuleParticles.h"
#include <time.h>
#include <stdlib.h>


Enemy_Pink::Enemy_Pink(int x, int y) : Enemy(x, y)
{
	pink_idle.PushBack({ 2+48,48,11,15 });

	pink_up.PushBack({ 2 + 48,48,11,15 });
	pink_up.PushBack({ 17 + 48,48,13,15 });
	pink_up.speed = 0.05f;
	pink_up.loop = true;

	pink_down.PushBack({ 0 + 48,112,16,16 });
	pink_down.PushBack({ 16 + 48,112,16,16 });
	pink_down.speed = 0.05f;
	pink_down.loop = true;

	pink_r.PushBack({ 1 + 48,17,14,14 });
	pink_r.PushBack({ 16 + 48,16,15,14 });
	pink_r.speed = 0.05f;
	pink_r.loop = true;

	pink_l.PushBack({ 0 + 48,80,15,15 });
	pink_l.PushBack({ 16 + 48,81,14,14 });
	pink_l.speed = 0.05f;
	pink_l.loop = true;

	currentAnim = &pink_down;

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_Pink::Update()
{
	movementDelay++;
	spawntimer++;

	if (spawntimer <= 1) {
		switch (App->sceneLevel->i) {
		case 0:
			position.y -= 0.5;
			currentAnim = &pink_up;
			break;
		case 1:
			position.y += 0.5;
			currentAnim = &pink_down;
			break;
		case 2:
			position.x += 0.5;
			currentAnim = &pink_r;
			break;
		case 3:
			position.x -= 0.5;
			currentAnim = &pink_l;
			break;
		}
	}

	if (movementDelay >= 2 && spawntimer > 1) {
		if (position.x - App->player->position.x < 0)			//right
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &pink_r) {
				currentAnim = &pink_r;
			}
			position.x += 1.25;
		}
		else if (position.x - App->player->position.x > 0)		//left
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &pink_l) {
				currentAnim = &pink_l;
			}
			position.x -= 1.25;
		}
		else {
			movementDirections = 0;
		}

		if (position.y - App->player->position.y < 0)			//down
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &pink_down) {
				currentAnim = &pink_down;
			}
			position.y += 1.25;
		}
		else if (position.y - App->player->position.y > 0)		//up
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &pink_up) {
				currentAnim = &pink_up;
			}
			position.y -= 1.25;
		}
		else {
			movementDirections = 0;
		}

		movementDelay = 0;
	}


	if (randomMove == 200 && spawntimer > 80)
	{
		if (position.x > 28)
			position.x -= 1.0f;
		if (position.y > 60)
			position.y -= 1.0f;
		movedelay++;
		currentAnim = &pink_r;
		if (movedelay == 5) {
			movedelay = 0;
			randomMove = 0;
		}
	}
	else if (randomMove == 300 && spawntimer > 80)
	{
		if (position.x < 455)
			position.x += 1.0f;
		if (position.y < 390)
			position.y += 1.0f;
		movedelay++;
		currentAnim = &pink_r;
		if (movedelay == 5) {
			movedelay = 0;
			randomMove = 0;
		}
	}
	else if (randomMove == 400 && spawntimer > 80)
	{
		if (position.x > 28)
			position.x -= 1.0f;
		if (position.y < 390)
			position.y += 1.0f;
		movedelay++;
		currentAnim = &pink_r;
		if (movedelay == 5) {
			movedelay = 0;
			randomMove = 0;
		}
	}
	else if (randomMove == 500 && spawntimer > 80)
	{
		if (position.x < 455)
			position.x += 1.0f;
		if (position.y > 60)
			position.y -= 1.0f;
		movedelay++;

		currentAnim = &pink_r;
		if (movedelay == 5) {
			movedelay = 0;
			randomMove = 0;
		}
	}
	else
	{
		randomMove = (rand() % 700);
	}

	Enemy::Update();
}