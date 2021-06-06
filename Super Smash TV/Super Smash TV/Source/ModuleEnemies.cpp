#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleInput.h"

#include "Enemy.h"
#include "Enemy_Pink.h"
#include "Enemy_Green.h"
#include "Enemy_Red.h"

#include "SceneLevel.h"
#include "SceneLevel2.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>


#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("Resources/Sprites/Characters/Enemies.png");

	textureFont = App->textures->Load("Resources/Sprites/Characters/Font.png");

	enemyNum = 0;

	srand(time(NULL));

	return true;
}

update_status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Update();
	}



	HandleEnemiesDespawn();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	App->textures->Unload(texture);

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;
	
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			enemyNum++;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			case Enemy_Type::GREEN:
				enemies[i] = new Enemy_Green(info.x, info.y);
				break;
			case Enemy_Type::PINK:
				enemies[i] = new Enemy_Pink(info.x, info.y);
				break;
			case Enemy_Type::RED:
				enemies[i] = new Enemy_Red(info.x, info.y);
				break;
			}
			enemies[i]->texture = texture;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{

	if (App->sceneLevel->Level_1 == true /*&& App->sceneLevel2->lvl2 == false*/) {
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && ((c2->type == c2->PLAYER_SHOT)))
			{
				enemies[i]->OnCollision(c2); //Notify the enemy of a collision
				enemyNum--;

				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}

	else if (App->sceneLevel2->Level_2 == true && App->sceneLevel->Level_1 == false)
	{
		
		//Enemy_Type::RED:;
		//cout << Red_Hits;
		if (Red_Hits > 0 && c2->type == c2->PLAYER_SHOT)
			Red_Hits--;

		if (Red_Hits == 0)
		{
			for (uint i = 0; i < MAX_ENEMIES; ++i)
			{
				if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && c2->type == c2->PLAYER_SHOT)
				{
					enemies[i]->OnCollision(c2); //Notify the enemy of a collision

					enemyNum--;

					delete enemies[i];
					enemies[i] = nullptr;
					break;
				}
			}
		}
	}
}
