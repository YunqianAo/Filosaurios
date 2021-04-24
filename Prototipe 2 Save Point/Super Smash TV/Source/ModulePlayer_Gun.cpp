#include "ModulePlayer_Gun.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer_Gun::ModulePlayer_Gun()
{
	position.x = 113;
	position.y = 137;

	// move down and idle
	gun_idle.PushBack({ 0, 64, 32, 32 });

	// move upwards
	gun_up.PushBack({ 96, 64, 32, 32 });	

	// Move left
	gun_l.PushBack({ 32, 64, 32, 32 });

	// Move right
	gun_r.PushBack({ 64, 64, 32, 32 });	

	// Shoot up
	gun_up_shoot.PushBack({ 192, 64, 32, 32 });
	gun_up_shoot.PushBack({ 224, 64, 32, 32 });
	gun_up_shoot.loop = true;
	gun_up_shoot.speed = 0.1f;

	// Shoot down
	gun_down_shoot.PushBack({ 128, 64, 32, 32 });
	gun_down_shoot.PushBack({ 160, 64, 32, 32 });
	gun_down_shoot.loop = true;
	gun_down_shoot.speed = 0.1f;

	// Shoot left
	gun_l_shoot.PushBack({ 64, 128, 32, 32 });
	gun_l_shoot.PushBack({ 96, 128, 32, 32 });
	gun_l_shoot.loop = true;
	gun_l_shoot.speed = 0.1f;

	// Shoot right
	gun_r_shoot.PushBack({ 64, 96, 32, 32 });
	gun_r_shoot.PushBack({ 96, 96, 32, 32 });
	gun_r_shoot.loop = true;
	gun_r_shoot.speed = 0.1f;


}

bool ModulePlayer_Gun::Start()
{
	LOG("Loading GUN GUN GUN");

	bool ret = true;

	texture = App->textures->Load("Sprites/Characters/Player2.png");

	currentAnimation = &gun_idle;

	return ret;
}

update_status ModulePlayer_Gun::Update()
{

	
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;

		currentAnimation = &gun_idle;
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;

		currentAnimation = &gun_up;
	}


	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;

		currentAnimation = &gun_l;
	}


	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;

		currentAnimation = &gun_r;
	}


	// Shoot bullet right
	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		App->particles->AddParticle(App->particles->bullet_r, position.x+28 , position.y - 22, 0);
		currentAnimation = &gun_r_shoot;
	}

	// Shoot bullet left
	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		App->particles->AddParticle(App->particles->bullet_l, position.x - 4, position.y-22, 0);
		currentAnimation = &gun_l_shoot;
	}

	// Shoot bullet up
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		App->particles->AddParticle(App->particles->bullet_up, position.x+14, position.y - 34, 0);
		currentAnimation = &gun_up_shoot;
				
	}

	// Shoot bullet down
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		App->particles->AddParticle(App->particles->bullet_down, position.x+16, position.y - 13, 0);
		currentAnimation = &gun_down_shoot;
	}



	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)

		currentAnimation = &gun_idle;

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;

}

update_status ModulePlayer_Gun::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y - rect.h, &rect);

	return update_status::UPDATE_CONTINUE;
}