#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "Enemy_Pink.h"
#include "Enemy_Green.h"
#include "Enemy_Red.h"


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
	texture = App->textures->Load("pink_e.png");
	texture = App->textures->Load("green_e.png");
	texture = App->textures->Load("red.png");

	textureFont = App->textures->Load("Assets/SpritesSSTV/Font.png");

	return true;
}


update_status ModuleEnemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
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
	/*
	//Render Font
	SDL_Rect rect0 = { 0, 0, 10, 16 };
	SDL_Rect rect1 = { 10, 0, 10, 16 };
	SDL_Rect rect2 = { 20, 0, 10, 16 };
	SDL_Rect rect3 = { 30, 0, 10, 16 };
	SDL_Rect rect4 = { 40, 0, 10, 16 };
	SDL_Rect rect5 = { 50, 0, 10, 16 };
	SDL_Rect rect6 = { 60, 0, 10, 16 };
	SDL_Rect rect7 = { 70, 0, 10, 16 };
	SDL_Rect rect8 = { 80, 0, 10, 16 };
	SDL_Rect rect9 = { 90, 0, 10, 16 };


	for (int i = 0; i < 8; ++i) {

		switch (App->player->scoreN[i]) {
		case 0:
			App->render->Blit(textureFont, posicioFont, 100, &rect0, 1.5f);
			break;
		case 1:
			App->render->Blit(textureFont, posicioFont, 100, &rect1, 1.5f);
			break;
		case 2:
			App->render->Blit(textureFont, posicioFont, 100, &rect2, 1.5f);
			break;
		case 3:
			App->render->Blit(textureFont, posicioFont, 100, &rect3, 1.5f);
			break;
		case 4:
			App->render->Blit(textureFont, posicioFont, 100, &rect4, 1.5f);
			break;
		case 5:
			App->render->Blit(textureFont, posicioFont, 100, &rect5, 1.5f);
			break;
		case 6:
			App->render->Blit(textureFont, posicioFont, 100, &rect6, 1.5f);
			break;
		case 7:
			App->render->Blit(textureFont, posicioFont, 100, &rect7, 1.5f);
			break;
		case 8:
			App->render->Blit(textureFont, posicioFont, 100, &rect8, 1.5f);
			break;
		case 9:
			App->render->Blit(textureFont, posicioFont, 100, &rect9, 1.5f);
			break;
		}

		posicioFont -= 15; //Separaci� entre nombres
	}
	posicioFont = 160; //Posici� del primer element de la dreta
	*/
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
			break;
		}
	}

	return ret;
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

				enemies[i]->SetToDelete();
			}
		}
	}
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
			case Enemy_Type::PINK:
				enemies[i] = new Enemy_Pink(info.x, info.y);
				break;
			case Enemy_Type::GREEN:
				enemies[i] = new Enemy_Green(info.x, info.y);
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

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			break;
		}
	}
}
