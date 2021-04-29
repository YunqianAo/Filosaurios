#include "ModulePlayer_Gun.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer_Gun::ModulePlayer_Gun(bool startEnabled) : Module(startEnabled)
{
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

	// Shoot Gun 
	ShootGun_down.PushBack({ 128, 64 + 96, 32, 32 });

	ShootGun_up.PushBack({ 224, 64 + 96, 32, 32 });

	ShootGun_l.PushBack({ 64, 128 + 96, 32, 32 });

	ShootGun_r.PushBack({ 64, 96 + 96, 32, 32 });

	ShootGun_up_shoot.PushBack({ 192, 64 + 96, 32, 32 });
	ShootGun_up_shoot.PushBack({ 224, 64 + 96, 32, 32 });
	ShootGun_up_shoot.loop = true;
	ShootGun_up_shoot.speed = 0.1f;

	ShootGun_down_shoot.PushBack({ 128, 64 + 96, 32, 32 });
	ShootGun_down_shoot.PushBack({ 160, 64 + 96, 32, 32 });
	ShootGun_down_shoot.loop = true;
	ShootGun_down_shoot.speed = 0.1f;

	// Shoot left
	ShootGun_l_shoot.PushBack({ 64, 128 + 96, 32, 32 });
	ShootGun_l_shoot.PushBack({ 96, 128 + 96, 32, 32 });
	ShootGun_l_shoot.loop = true;
	ShootGun_l_shoot.speed = 0.1f;

	// Shoot right
	ShootGun_r_shoot.PushBack({ 64, 96 + 96, 32, 32 });
	ShootGun_r_shoot.PushBack({ 96, 96 + 96, 32, 32 });
	ShootGun_r_shoot.loop = true;
	ShootGun_r_shoot.speed = 0.1f;


}

bool ModulePlayer_Gun::Start()
{
	LOG("Loading GUN GUN GUN");

	bool ret = true;
	texture = App->textures->Load("Resources/Sprites/Characters/Player.png");
	currentAnimation = &gun_idle;

	gunFx = App->audio->LoadFx("Resources/Audio/SFX/In-Game Sounds/Weapons_Sounds/Pistol_Shot.wav");

	position.x = 113;
	position.y = 118;

	destroyed = false;

	ShootGun = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 14, -25 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer_Gun::Update()
{

	if (ShootGun == false)
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
		if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN)
		{
			App->particles->AddParticle(App->particles->bullet_r, position.x+28 , position.y+10, Collider::Type::PLAYER_SHOT);
			currentAnimation = &gun_r_shoot;
			App->audio->PlayFx(gunFx);
		}

		// Shoot bullet left
		if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN)
		{
			App->particles->AddParticle(App->particles->bullet_l, position.x - 4, position.y+10, Collider::Type::PLAYER_SHOT);
			currentAnimation = &gun_l_shoot;
			App->audio->PlayFx(gunFx);
		}

		// Shoot bullet up
		if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN)
		{
			App->particles->AddParticle(App->particles->bullet_up, position.x+14, position.y, Collider::Type::PLAYER_SHOT);
			currentAnimation = &gun_up_shoot;
			App->audio->PlayFx(gunFx);
				
		}

		// Shoot bullet down
		if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN)
		{
			App->particles->AddParticle(App->particles->bullet_down, position.x+16, position.y+20, Collider::Type::PLAYER_SHOT);
			currentAnimation = &gun_down_shoot;
			App->audio->PlayFx(gunFx);
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

	}

	if (ShootGun == true)
	{
		if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			position.y += speed;

			currentAnimation = &ShootGun_down;
		}

		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			position.y -= speed;

			currentAnimation = &ShootGun_up;
		}


		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			position.x -= speed;

			currentAnimation = &ShootGun_l;
		}


		if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			position.x += speed;

			currentAnimation = &ShootGun_r;
		}


		// Shoot bullet right
		if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN)
		{
			App->particles->AddParticle(App->particles->shotgun_2, position.x + 28, position.y + 10, Collider::Type::PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shotgun_3, position.x + 28, position.y + 10, Collider::Type::PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shotgun_4, position.x + 28, position.y + 10, Collider::Type::PLAYER_SHOT);
			currentAnimation = &ShootGun_r_shoot;
			App->audio->PlayFx(gunFx);
		}

		// Shoot bullet left
		if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN)
		{
			App->particles->AddParticle(App->particles->shotgun_8, position.x - 4, position.y + 10, Collider::Type::PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shotgun_7, position.x - 4, position.y + 10, Collider::Type::PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shotgun_6, position.x - 4, position.y + 10, Collider::Type::PLAYER_SHOT);
			currentAnimation = &ShootGun_l_shoot;
			App->audio->PlayFx(gunFx);
		}

		// Shoot bullet up
		if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN)
		{
			App->particles->AddParticle(App->particles->shotgun_8, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shotgun_1, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shotgun_2, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
			currentAnimation = &ShootGun_up_shoot;
			App->audio->PlayFx(gunFx);

		}

		// Shoot bullet down
		if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN)
		{
			App->particles->AddParticle(App->particles->shotgun_4, position.x + 16, position.y + 20, Collider::Type::PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shotgun_5, position.x + 16, position.y + 20, Collider::Type::PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shotgun_6, position.x + 16, position.y + 20, Collider::Type::PLAYER_SHOT);
			currentAnimation = &ShootGun_down_shoot;
			App->audio->PlayFx(gunFx);
		}

		if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)

			currentAnimation = &ShootGun_down;

	}
	

	if (App->input->keys[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		if (GodMode == false) {
				GodMode = true;
		}
		else if(GodMode == true) {
				GodMode = false;
		}

	}

	if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
	{
		if (destroyed == false) {
			App->fade->FadeToBlack((Module*)App->sceneLevel, (Module*)App->sceneLose, 90);
			destroyed = true;
		}
	}

	if (App->input->keys[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN)
	{
		if (ShootGun == false) {
			ShootGun = true;
		}
		else if (ShootGun == true) {
			ShootGun = false;
		}

	}


	

	collider->SetPos(position.x + 9, position.y +30);

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;

}

update_status ModulePlayer_Gun::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}


	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer_Gun::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::WALL && destroyed == false && GodMode == false)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel, (Module*)App->sceneLose, 90);
		destroyed = true;

	}

	if (c2->type == Collider::Type::DOOR && destroyed == false)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel, (Module*)App->sceneWin, 90);
		destroyed = true;
	}

}