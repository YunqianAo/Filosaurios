#include "Enemy_Green.h"
#include"ModuleTextures.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "SceneLevel.h"
#include "ModuleParticles.h"
#include <time.h>
#include <stdlib.h>


Enemy_Green::Enemy_Green(int x, int y) : Enemy(x, y)
{
	green_idle.PushBack({ 2,48,11,15 });
	
	green_up.PushBack({ 2,48,11,15 });
	green_up.PushBack({ 17,48,13,15 });
	green_up.speed = 0.05f;
	green_up.loop = true;

	green_down.PushBack({ 0,112,16,16 });
	green_down.PushBack({ 16,112,16,16 });
	green_down.speed = 0.05f;
	green_down.loop = true;

	green_r.PushBack({ 1,17,14,14 });
	green_r.PushBack({ 16,16,15,14 });
	green_r.speed = 0.05f;
	green_r.loop = true;

	green_l.PushBack({ 0,80,15,15 });
	green_l.PushBack({ 16,81,14,14 });
	green_l.speed = 0.05f;
	green_l.loop = true;

	currentAnim = &green_down;

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_Green::Update()
{
	movementDelay++;
	spawntimer++;

	if (spawntimer <= 1) {
		switch (App->sceneLevel->i) {
		case 0:
			position.y -= 1;
			currentAnim = &green_up;
			break;
		case 1:
			position.y += 1;
			currentAnim = &green_down;
			break;
		case 2:
			position.x += 1;
			currentAnim = &green_r;
			break;
		case 3:
			position.x -= 1;
			currentAnim = &green_l;
			break;
		}
	}

	if (movementDelay >= 3 && spawntimer > 1 && movedelay == 0) {
		if (position.x - App->player->position.x < 0)			//right
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &green_r) {
				currentAnim = &green_r;
			}
			position.x += 1.25;
		}
		else if (position.x - App->player->position.x > 0)		//left
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &green_l) {
				currentAnim = &green_l;
			}
			position.x -= 1.25;
		}
		else {
			movementDirections = 0;
		}

		if (position.y - App->player->position.y < 0)			//down
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &green_down) {
				currentAnim = &green_down;
			}
			position.y += 1.25;
		}
		else if (position.y - App->player->position.y > 0)		//up
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &green_up) {
				currentAnim = &green_up;
			}
			position.y -= 1.25;
		}
		else {
			movementDirections = 0;
		}

		movementDelay = 0;
	}


	if (randomMove == 37 && spawntimer > 1)		
	{
		if (position.x > 19)
			position.x -= 2.0f;
		if (position.y > 37)
			position.y -= 2.0f;
		movedelay++;
		if (movedelay == 5) {
			movedelay = 0;
			randomMove = 0;
		}
	}
	else if (randomMove == 73 && spawntimer > 1)		
	{
		if (position.x < 237-13)
			position.x += 2.0f;
		if (position.y < 214-25)
			position.y += 2.0f;
		movedelay++;
		if (movedelay == 5) {
			movedelay = 0;
			randomMove = 0;
		}
	}
	else if (randomMove == 123 && spawntimer > 1)	
	{
		if (position.x > 19)
			position.x -= 2.0f;
		if (position.y < 214-25)
			position.y += 2.0f;
		movedelay++;
		if (movedelay == 5) {
			movedelay = 0;
			randomMove = 0;
		}
	}
	else if (randomMove == 179 && spawntimer > 1)		
	{
		if (position.x < 237-13)
			position.x += 2.0f;
		if (position.y > 37)
			position.y -= 2.0f;
		movedelay++;
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






