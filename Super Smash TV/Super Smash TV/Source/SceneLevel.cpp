#include "SceneLevel.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer_Gun.h"
#include "ModulePlayer_Legs.h"
#include "ModuleFadeToBlack.h"



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

	bgTexture = App->textures->Load("Sprites/Mapa/Map.png");

	//Map 1b
	// X colliders
	App->collisions->AddCollider({ 0, 215, 256, 75 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 0, -39, 104, 75 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 104, -39, 48, 75 }, Collider::Type::DOOR);
	App->collisions->AddCollider({ 104 + 48, -39, 104, 75 }, Collider::Type::WALL);
	// Y colliders
	App->collisions->AddCollider({ 238, 36, 37, 69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 238, 146, 37, 69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -18, 36, 37, 69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -18, 146, 37, 69 }, Collider::Type::WALL);

	//Map 2b
	// X colliders
	App->collisions->AddCollider({ 0 + 256, 215, 104, 75 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 152 + 256, 215, 104, 75 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 0 + 256, -39, 104, 75 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 152 + 256, -39, 104, 75 }, Collider::Type::WALL);
	// Y colliders
	App->collisions->AddCollider({ 238 + 256, 36, 37, 69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 238 + 256, 146, 37, 69 }, Collider::Type::WALL);

	//Map 3b
	// X colliders
	App->collisions->AddCollider({ 0 + 256 + 256, 215, 104, 75 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 152 + 256 + 256, 215, 104, 75 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 0 + 256 + 256, -39, 104, 75 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 152 + 256 + 256, -39, 104, 75 }, Collider::Type::WALL);
	// Y colliders
	App->collisions->AddCollider({ 238 + 256 + 256, 36, 37, 69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 238 + 256 + 256, 146, 37, 69 }, Collider::Type::WALL);

	//Map Boss
	// X colliders
	App->collisions->AddCollider({ 0 + 256 + 256 + 256, 215, 256, 75 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 0 + 256 + 256 + 256, -39, 80, 75 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 80 + 256 + 256 + 256, -39, 96, 75 }, Collider::Type::DOOR);
	App->collisions->AddCollider({ 176 + 256 + 256 + 256, -39, 80, 75 }, Collider::Type::WALL);
	// Y colliders
	App->collisions->AddCollider({ 238 + 256 + 256 + 256, 36, 37, 175 }, Collider::Type::WALL);

	//Map c
	// X colliders
	App->collisions->AddCollider({ 0 + 256, 175 + 290, 256 + 256, 15 }, Collider::Type::WALL);

	// Y colliders
	App->collisions->AddCollider({ 238 + 256, 290, 37, 69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 238 + 256, 290 + 106, 37, 69 }, Collider::Type::WALL);

	App->collisions->AddCollider({ -18 + 256, 290, 37, 69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -18 + 256, 290 + 69, 37, 37 }, Collider::Type::DOOR);
	App->collisions->AddCollider({ -18 + 256, 290 + 106, 37, 69 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 238 + 256 + 256, 290, 37,69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 238 + 256 + 256, 290 + 69, 37, 37 }, Collider::Type::DOOR);
	App->collisions->AddCollider({ 238 + 256 + 256, 290 + 106, 37, 69 }, Collider::Type::WALL);


	//Map a
	// X colliders

	App->collisions->AddCollider({ 0 + 256, -256, 104, 39 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 104 + 256, -256, 48, 39 }, Collider::Type::DOOR);
	App->collisions->AddCollider({ 152 + 256, -256, 104, 39 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 0 + 256 + 256, -256, 104, 39 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 104 + 256 + 256, -256, 48, 39 }, Collider::Type::DOOR);
	App->collisions->AddCollider({ 152 + 256 + 256, -256, 104, 39 }, Collider::Type::WALL);

	// Y colliders

	// Y colliders  -217
	App->collisions->AddCollider({ 238 + 256, -217, 37, 69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 238 + 256, -217 + 106, 37, 72 }, Collider::Type::WALL);

	App->collisions->AddCollider({ -18 + 256, -217, 37, 69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -18 + 256, -217 + 69, 37, 37 }, Collider::Type::DOOR);
	App->collisions->AddCollider({ -18 + 256, -217 + 106, 37, 72 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 238 + 256 + 256, -217, 37,69 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 238 + 256 + 256, -217 + 69, 37, 37 }, Collider::Type::DOOR);
	App->collisions->AddCollider({ 238 + 256 + 256, -217 + 106, 37, 72 }, Collider::Type::WALL);

	//Enemies ---
	App->player_gun->Enable();
	App->player_leg->Enable();

	return ret;
}

update_status SceneLevel::Update()
{
	App->render->camera.x += 0;

	if (App->player_gun->destroyed == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLose, 90);
	}
	
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, -256, -255, NULL);

	return update_status::UPDATE_CONTINUE;
}