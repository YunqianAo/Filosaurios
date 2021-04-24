#include "ModulePlayer_Legs.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer_Leg::ModulePlayer_Leg()
{
	position.x = 121;
	position.y = 137;

	// LEGS
	legs_idle.PushBack({ 128, 16, 16, 16 });

	// move upwards
	legs_up.PushBack({ 0, 16, 16, 16 });//    1	
	legs_up.PushBack({ 16, 16, 16, 16 });//   2	
	legs_up.PushBack({ 32, 16, 16, 16 });//   3	
	legs_up.PushBack({ 48, 16, 16, 16 });//   4	
	legs_up.PushBack({ 64, 16, 16, 16 });//   5	
	legs_up.PushBack({ 80, 16, 16, 16 });//   6	

	legs_up.loop = true;
	legs_up.speed = 0.2f;

	// Move down
	legs_down.PushBack({ 0, 0, 16, 16 });//    1	
	legs_down.PushBack({ 16, 0, 16, 16 });//   2	
	legs_down.PushBack({ 32, 0, 16, 16 });//   3	
	legs_down.PushBack({ 48, 0, 16, 16 });//   4	
	legs_down.PushBack({ 64, 0, 16, 16 });//   5	
	legs_down.PushBack({ 80, 0, 16, 16 });//   6
	legs_down.PushBack({ 96, 0, 16, 16 });//   7	
	legs_down.PushBack({ 112, 0, 16, 16 });//  8	

	legs_down.loop = true;
	legs_down.speed = 0.2f;

	// Move left
	legs_l.PushBack({ 96, 32, 16, 16 });//   7
	legs_l.PushBack({ 80, 32, 16, 16 });//   6
	legs_l.PushBack({ 64, 32, 16, 16 });//   5
	legs_l.PushBack({ 48, 32, 16, 16 });//   4
	legs_l.PushBack({ 32, 32, 16, 16 });//   3	
	legs_l.PushBack({ 16, 32, 16, 16 });//   2	
	legs_l.PushBack({ 0, 32, 16, 16 });//    1		

	legs_l.loop = true;
	legs_l.speed = 0.2f;

	// Move right
	legs_r.PushBack({ 0, 48, 16, 16 });//    1	
	legs_r.PushBack({ 16, 48, 16, 16 });//   2	
	legs_r.PushBack({ 32, 48, 16, 16 });//   3	
	legs_r.PushBack({ 48, 48, 16, 16 });//   4	
	legs_r.PushBack({ 64, 48, 16, 16 });//   5	
	legs_r.PushBack({ 80, 48, 16, 16 });//   6
	legs_r.PushBack({ 96, 48, 16, 16 });//   7
	legs_r.loop = true;
	legs_r.speed = 0.2f;

	// Shoot up
	legs_up_shoot.PushBack({ 192, 16, 16, 16 });
	// Shoot left
	legs_l_shoot.PushBack({ 208, 16, 16, 16 });
	// Shoot right
	legs_r_shoot.PushBack({ 160, 16, 16, 16 });

}


bool ModulePlayer_Leg::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Sprites/Characters/Player.png");

	currentAnimation = &legs_idle;

	return ret;
}

update_status ModulePlayer_Leg::Update()
{
	// Moving the player with the camera scroll
	App->player_leg->position.x += 0;

	// Body movent
	// Shoot bullet right
	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		currentAnimation = &legs_r_shoot;
	}

	// Shoot bullet left
	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		currentAnimation = &legs_l_shoot;
	}

	// Shoot bullet up
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{

		currentAnimation = &legs_up_shoot;
	}



	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;

		currentAnimation = &legs_down;
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;

		currentAnimation = &legs_up;
	}


	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;

		currentAnimation = &legs_l;
	}


	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;

		currentAnimation = &legs_r;
	}


	


	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE

		&& App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)

		currentAnimation = &legs_idle;

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer_Leg::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y - rect.h, &rect);

	return update_status::UPDATE_CONTINUE;
}