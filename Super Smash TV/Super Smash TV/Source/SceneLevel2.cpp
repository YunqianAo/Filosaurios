#include "SceneLevel2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer_Gun.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"


#include <stdio.h>


SceneLevel2::SceneLevel2(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel2::~SceneLevel2()
{

}

// Load assets
bool SceneLevel2::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	Level_2 = true;	//detecta que estas a Level_1

	levelcont++;	//mira quants cops pases per el Level_1

	App->enemies->Enable();
	App->particles->Enable();
	App->collisions->Enable();
	App->player->Enable();

	bgTexture = App->textures->Load("Resources/Sprites/Mapa/Map2.png");
	App->audio->PlayMusic("Resources/Audio/Music/Circuit_Theme 01.ogg", 1.0f);


	//Map 1b
	// X colliders
	App->collisions->AddCollider({ 0, 215, 256, 75 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 0, -39, 104, 75 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 104, -39, 48, 75 }, Collider::Type::DOOR);
	App->collisions->AddCollider({ 104 + 48, -39, 104, 75 }, Collider::Type::WALL);
	// Y colliders
	App->collisions->AddCollider({ 238, 36, 37, 69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 238, 105, 37, 41 }, Collider::Type::DOOR);
	App->collisions->AddCollider({ 238, 146, 37, 69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -18, 36, 37, 69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -18, 105, 37, 41 }, Collider::Type::DOOR);
	App->collisions->AddCollider({ -18, 146, 37, 69 }, Collider::Type::WALL);

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz", };
	scoreFont = App->fonts->Load("Resources/Sprites/Characters/Font.png", lookupTable, 0);

	return ret;
}

update_status SceneLevel2::Update()
{

	++num;
	if (sceneTimer < 3601)	++sceneTimer;

	if (sceneTimer == 240)
	{
		App->particles->AddParticle(App->particles->ShootGun_PowerUp, 60, 171, Collider::Type::SHOOTGUN_POWERUP);
	}

	if (sceneTimer == 1200)
	{
		App->particles->AddParticle(App->particles->Orv_PowerUp, 185, 170, Collider::Type::ORV_POWERUP);
	}

	if (sceneTimer == 2000)
	{
		App->particles->AddParticle(App->particles->Orv_PowerUp, 164, 75, Collider::Type::ORV_POWERUP);
	}

	if (sceneTimer == 2800)
	{
		App->particles->AddParticle(App->particles->ShootGun_PowerUp, 56, 121, Collider::Type::SHOOTGUN_POWERUP);
	}

	if (sceneTimer % 70 == 0 && sceneTimer <= 3600) {
		randomEnemySpawn = (rand() % 10);

		if (i == 0) { //up door
			for (int j = 0; j < 9; ++j) {
				SpawnEnemies[i][j][0] = (rand() % 42 + 107); //porta adalt X
				SpawnEnemies[i][j][1] = (rand() % 10 + 26); //porta adalt Y
			}
		}

		if (i == 1) { //left door
			for (int j = 0; j < 9; ++j) {
				SpawnEnemies[i][j][0] = (rand() % 6 + 15);
				SpawnEnemies[i][j][1] = (rand() % 41 + 105);
			}
		}

		if (i == 2) { //right door
			for (int j = 0; j < 9; ++j) {
				SpawnEnemies[i][j][0] = (rand() % 6 + 238);
				SpawnEnemies[i][j][1] = (rand() % 41 + 105);
			}
		}

		if (i == 3) { //down door
			for (int j = 0; j < 9; ++j) {
				SpawnEnemies[i][j][0] = (rand() % 48 + 104); //porta abaix X
				SpawnEnemies[i][j][1] = (rand() % 5 + 210); //porta abaix Y
			}
		}
		switch (randomEnemySpawn) {
		case 9:
			App->enemies->AddEnemy(Enemy_Type::PINK, SpawnEnemies[i][0][0], SpawnEnemies[i][0][1]);
			App->enemies->AddEnemy(Enemy_Type::PINK, SpawnEnemies[i][1][0], SpawnEnemies[i][1][1]);
			App->enemies->AddEnemy(Enemy_Type::PINK, SpawnEnemies[i][2][0], SpawnEnemies[i][2][1]);
		case 8:
		case 7:
			App->enemies->AddEnemy(Enemy_Type::GREEN, SpawnEnemies[i][3][0], SpawnEnemies[i][3][1]);
			App->enemies->AddEnemy(Enemy_Type::PINK, SpawnEnemies[i][4][0], SpawnEnemies[i][4][1]);
		case 6:
			App->enemies->AddEnemy(Enemy_Type::PINK, SpawnEnemies[i][5][0], SpawnEnemies[i][5][1]);
		case 5:
		case 4:
		case 3:
		case 2:
			App->enemies->AddEnemy(Enemy_Type::GREEN, SpawnEnemies[i][6][0], SpawnEnemies[i][6][1]);
		case 1:
			App->enemies->AddEnemy(Enemy_Type::PINK, SpawnEnemies[i][7][0], SpawnEnemies[i][7][1]);
		case 0:
			App->enemies->AddEnemy(Enemy_Type::PINK, SpawnEnemies[i][8][0], SpawnEnemies[i][8][1]);
			break;
		}

		++i;
		if (i == 4) i = 0;

	}
	if (i == 1) mapaActual = 7;
	else mapaActual = 0;

	++exitTimer;
	if (exitTimer > 40)
		exitTimer = 0;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, -256, -255, NULL);

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);
	App->fonts->BlitText(23, 49, scoreFont, scoreText);


	if (sceneTimer > 3600 && App->enemies->enemyNum == 0) {
		App->particles->AddParticle(App->particles->exit_arow, 140, 119, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->exit_words, 127, 122, Collider::Type::NONE);
	}

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel2::CleanUp()
{
	Level_2 = false;

	App->textures->Unload(bgTexture);
	App->player->Disable();
	App->enemies->Disable();
	App->particles->Disable();
	App->collisions->Disable();

	return true;
}