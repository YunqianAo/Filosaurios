#include "SceneLevel.h"

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


SceneLevel::SceneLevel(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel::~SceneLevel()
{

}

// Load assets
bool SceneLevel::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	Level_1 = true;	//detecta que estas a Level_1

	levelcont++;	//mira quants cops pases per el Level_1

	App->enemies->Enable();
	App->particles->Enable();
	App->collisions->Enable();
	App->player->Enable();

	bgTexture = App->textures->Load("Resources/Sprites/Mapa/Map.png");
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
	scoreFont = App->fonts->Load("Resources/Sprites/Characters/Font.png", lookupTable, 1);

	return ret;
}

update_status SceneLevel::Update()
{

	++num;
	if (sceneTimer < 3601)	++sceneTimer;

	if (sceneTimer % 80 == 0 && sceneTimer <= 3600) {//3600frames, 6 rounds, 24 aparicions random (sceneTimer % 150)
		randomEnemySpawn = (rand() % 5);


		if (i == 0) { //up door
			for (int j = 0; j < 9; ++j) {
				portesSpawn[i][j][0] = (rand() % 42 + 107); //porta adalt X
				portesSpawn[i][j][1] = (rand() % 10 + 26); //porta adalt Y
			}
		}

		if (i == 1) { //left door
			for (int j = 0; j < 9; ++j) {
				portesSpawn[i][j][0] = (rand() % 6 + 15);
				portesSpawn[i][j][1] = (rand() % 41 + 105);
			}
		}

		if (i == 2) { //right door
			for (int j = 0; j <9; ++j) {
				portesSpawn[i][j][0] = (rand() % 6 + 238);
				portesSpawn[i][j][1] = (rand() % 41 + 105);
			}
		}

		if (i == 3) { //down door
			for (int j = 0; j < 9; ++j) {
				portesSpawn[i][j][0] = (rand() % 48 + 104); //porta abaix X
				portesSpawn[i][j][1] = (rand() % 5 + 210); //porta abaix Y
			}
		}


		switch (randomEnemySpawn) {
		case 9:
			App->enemies->AddEnemy(Enemy_Type::GREEN, portesSpawn[i][0][0], portesSpawn[i][0][1]);
			App->enemies->AddEnemy(Enemy_Type::GREEN, portesSpawn[i][1][0], portesSpawn[i][1][1]);
			App->enemies->AddEnemy(Enemy_Type::GREEN, portesSpawn[i][2][0], portesSpawn[i][2][1]);
		case 8:
		case 7:
			App->enemies->AddEnemy(Enemy_Type::GREEN, portesSpawn[i][3][0], portesSpawn[i][3][1]);
			App->enemies->AddEnemy(Enemy_Type::PINK, portesSpawn[i][4][0], portesSpawn[i][4][1]);
		case 6:
			App->enemies->AddEnemy(Enemy_Type::GREEN, portesSpawn[i][5][0], portesSpawn[i][5][1]);
		case 5:
		case 4:
		case 3:
		case 2:
			App->enemies->AddEnemy(Enemy_Type::GREEN, portesSpawn[i][6][0], portesSpawn[i][6][1]);
		case 1:
			App->enemies->AddEnemy(Enemy_Type::PINK, portesSpawn[i][7][0], portesSpawn[i][7][1]);
		case 0:
			App->enemies->AddEnemy(Enemy_Type::PINK, portesSpawn[i][8][0], portesSpawn[i][8][1]);
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
update_status SceneLevel::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, -256, -255, NULL);

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);
	App->fonts->BlitText(23, 49, scoreFont, scoreText);


	if (sceneTimer > 3600 && exitTimer < 20 && App->enemies->enemyNum == 0) {	//La textura va fent pampallugues.
		App->particles->AddParticle(App->particles->exit_arow, 140, 119, Collider::Type::PLAYER_SHOT);
		App->particles->AddParticle(App->particles->exit_words, 15, 10, Collider::Type::PLAYER_SHOT);
	}
	else if (sceneTimer > 3600 && App->enemies->enemyNum == 0) {
		App->particles->AddParticle(App->particles->exit_arow, 15, 10, Collider::Type::PLAYER_SHOT);
		App->particles->AddParticle(App->particles->exit_words, 15, 10, Collider::Type::PLAYER_SHOT);
	}

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel::CleanUp()
{
	Level_1 = false;

	App->textures->Unload(bgTexture);
	App->player->Disable();
	App->enemies->Disable();
	App->particles->Disable();
	App->collisions->Disable();

	return true;
}