#include "ModulePlayer.h"

#include <iostream>
using namespace std;

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SceneLevel.h"
#include "SceneLevel2.h"


#include "SDL/include/SDL_render.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// Idle animation - just one sprite
	legs_down_idle.PushBack({ 128, 16, 16, 16 });
	legs_up_idle.PushBack({ 192, 16, 16, 16 });
	legs_l_idle.PushBack({ 208, 16, 16, 16 });
	legs_r_idle.PushBack({ 160, 16, 16, 16 });

	//nome cames

	// Move upwards
	legs_down.PushBack({ 0, 0, 16, 16 });//    1	
	legs_down.PushBack({ 16, 0, 16, 16 });//   2	
	legs_down.PushBack({ 32, 0, 16, 16 });//   3	
	legs_down.PushBack({ 48, 0, 16, 16 });//   4	
	legs_down.PushBack({ 64, 0, 16, 16 });//   5	
	legs_down.PushBack({ 80, 0, 16, 16 });//   6
	legs_down.PushBack({ 96, 0, 16, 16 });//   7	
	legs_down.PushBack({ 112, 0, 16, 16 });//  8	

	legs_down.loop = true;
	legs_down.speed = 0.08f;

	legs_up.PushBack({ 0, 16, 16, 16 });//    1	
	legs_up.PushBack({ 16, 16, 16, 16 });//   2	
	legs_up.PushBack({ 32, 16, 16, 16 });//   3	
	legs_up.PushBack({ 48, 16, 16, 16 });//   4	
	legs_up.PushBack({ 64, 16, 16, 16 });//   5	
	legs_up.PushBack({ 80, 16, 16, 16 });//   6	
	legs_up.loop = true;
	legs_up.speed = 0.08f;

	//Move rigth 

	legs_r.PushBack({ 0, 48, 16, 16 });//    1	
	legs_r.PushBack({ 16, 48, 16, 16 });//   2	
	legs_r.PushBack({ 32, 48, 16, 16 });//   3	
	legs_r.PushBack({ 48, 48, 16, 16 });//   4	
	legs_r.PushBack({ 64, 48, 16, 16 });//   5	
	legs_r.PushBack({ 80, 48, 16, 16 });//   6
	legs_r.PushBack({ 96, 48, 16, 16 });//   7
	legs_r.loop = true;
	legs_r.speed = 0.08f;

	legs_l.PushBack({ 96, 32, 16, 16 });//   7
	legs_l.PushBack({ 80, 32, 16, 16 });//   6
	legs_l.PushBack({ 64, 32, 16, 16 });//   5
	legs_l.PushBack({ 48, 32, 16, 16 });//   4
	legs_l.PushBack({ 32, 32, 16, 16 });//   3	
	legs_l.PushBack({ 16, 32, 16, 16 });//   2	
	legs_l.PushBack({ 0, 32, 16, 16 });//    1		
	legs_l.loop = true;
	legs_l.speed = 0.08f;

	// 2
	legs_2.PushBack({ 128, 32 + 16, 16, 16 });//    1	
	legs_2.PushBack({ 128 + 16, 32 + 16, 16, 16 });//   2	
	legs_2.PushBack({ 128 + 16 + 16, 32 + 16, 16, 16 });//   3	
	legs_2.PushBack({ 128 + 16 + 16 + 16, 32 + 16, 16, 16 });//   4	
	legs_2.PushBack({ 128 + 16 + 16 + 16 + 16, 32 + 16, 16, 16 });//   5	
	legs_2.loop = true;
	legs_2.speed = 0.08f;

	// 4
	legs_4.PushBack({ 0, 48, 16, 16 });//    1	
	legs_4.PushBack({ 16, 48, 16, 16 });//   2	
	legs_4.PushBack({ 32, 48, 16, 16 });//   3	
	legs_4.PushBack({ 48, 48, 16, 16 });//   4	
	legs_4.PushBack({ 64, 48, 16, 16 });//   5	
	legs_4.PushBack({ 80, 48, 16, 16 });//   6
	legs_4.PushBack({ 96, 48, 16, 16 });//   7
	legs_4.loop = true;
	legs_4.speed = 0.08f;

	// 6
	legs_6.PushBack({ 96, 32, 16, 16 });//   7
	legs_6.PushBack({ 80, 32, 16, 16 });//   6
	legs_6.PushBack({ 64, 32, 16, 16 });//   5
	legs_6.PushBack({ 48, 32, 16, 16 });//   4
	legs_6.PushBack({ 32, 32, 16, 16 });//   3	
	legs_6.PushBack({ 16, 32, 16, 16 });//   2	
	legs_6.PushBack({ 0, 32, 16, 16 });//    1		
	legs_6.loop = true;
	legs_6.speed = 0.08f;

	// 8
	legs_8.PushBack({ 128 + 16 + 16 + 16 + 16, 32, 16, 16 });//   5	
	legs_8.PushBack({ 128 + 16 + 16 + 16, 32, 16, 16 });//   4	
	legs_8.PushBack({ 128 + 16 + 16, 32, 16, 16 });//   3
	legs_8.PushBack({ 128 + 16, 32, 16, 16 });//   2
	legs_8.PushBack({ 128, 32, 16, 16 });//    1	
	legs_8.loop = true;
	legs_8.speed = 0.08f;


	//ANIMACIONS GUN

	gun_down.PushBack({ 0, 64, 32, 32 });
	gun_up.PushBack({ 96, 64, 32, 32 });
	gun_l.PushBack({ 32, 64, 32, 32 });
	gun_r.PushBack({ 64, 64, 32, 32 });

	gun_2.PushBack({ 0, 160, 32, 32 });
	gun_4.PushBack({ 64, 160, 32, 32 });
	gun_6.PushBack({ 96, 160, 32, 32 });
	gun_8.PushBack({ 32, 160, 32, 32 });


	//ANIMACIONS GUN SHOT

	gun_down_shoot.PushBack({ 128, 64, 32, 32 });
	gun_down_shoot.PushBack({ 160, 64, 32, 32 });
	gun_down_shoot.loop = true;
	gun_down_shoot.speed = 0.1f;

	gun_l_shoot.PushBack({ 64, 128, 32, 32 });
	gun_l_shoot.PushBack({ 96, 128, 32, 32 });
	gun_l_shoot.loop = true;
	gun_l_shoot.speed = 0.1f;

	gun_r_shoot.PushBack({ 64, 96, 32, 32 });
	gun_r_shoot.PushBack({ 96, 96, 32, 32 });
	gun_r_shoot.loop = true;
	gun_r_shoot.speed = 0.1f;
	
	gun_up_shoot.PushBack({ 192, 64, 32, 32 });
	gun_up_shoot.PushBack({ 224, 64, 32, 32 });
	gun_up_shoot.loop = true;
	gun_up_shoot.speed = 0.1f;

	// Diagonals
	gun_2_shoot.PushBack({ 0, 96, 32, 32 });
	gun_2_shoot.PushBack({ 32, 96, 32, 32 });
	gun_2_shoot.loop = true;
	gun_2_shoot.speed = 0.1f;

	gun_4_shoot.PushBack({ 128, 96, 32, 32 });
	gun_4_shoot.PushBack({ 160, 96, 32, 32 });
	gun_4_shoot.loop = true;
	gun_4_shoot.speed = 0.1f;

	gun_6_shoot.PushBack({ 0, 128, 32, 32 });
	gun_6_shoot.PushBack({ 32, 128, 32, 32 });
	gun_6_shoot.loop = true;
	gun_6_shoot.speed = 0.1f;

	gun_8_shoot.PushBack({ 128, 128, 32, 32 });
	gun_8_shoot.PushBack({ 160, 128, 32, 32 });
	gun_8_shoot.loop = true;
	gun_8_shoot.speed = 0.1f;

	// Shoot Gun 
	ShootGun_down.PushBack({ 128, 64 + 96, 32, 32 });
	ShootGun_up.PushBack({ 224, 64 + 96, 32, 32 });
	ShootGun_l.PushBack({ 64, 128 + 96, 32, 32 });
	ShootGun_r.PushBack({ 64, 96 + 96, 32, 32 });
	ShootGun_2.PushBack({ 32, 192 , 32, 32 });
	ShootGun_4.PushBack({ 128, 192 , 32, 32 });
	ShootGun_6.PushBack({ 32, 224 , 32, 32 });
	ShootGun_8.PushBack({ 128, 224 , 32, 32 });


	ShootGun_up_shoot.PushBack({ 192, 64 + 96, 32, 32 });
	ShootGun_up_shoot.PushBack({ 224, 64 + 96, 32, 32 });
	ShootGun_up_shoot.loop = true;
	ShootGun_up_shoot.speed = 0.1f;

	ShootGun_down_shoot.PushBack({ 128, 64 + 96, 32, 32 });
	ShootGun_down_shoot.PushBack({ 160, 64 + 96, 32, 32 });
	ShootGun_down_shoot.loop = true;
	ShootGun_down_shoot.speed = 0.1f;

	ShootGun_l_shoot.PushBack({ 64, 128 + 96, 32, 32 });
	ShootGun_l_shoot.PushBack({ 96, 128 + 96, 32, 32 });
	ShootGun_l_shoot.loop = true;
	ShootGun_l_shoot.speed = 0.1f;

	ShootGun_r_shoot.PushBack({ 64, 96 + 96, 32, 32 });
	ShootGun_r_shoot.PushBack({ 96, 96 + 96, 32, 32 });
	ShootGun_r_shoot.loop = true;
	ShootGun_r_shoot.speed = 0.1f;

	ShootGun_2_shoot.PushBack({ 32, 192 , 32, 32 });
	ShootGun_2_shoot.PushBack({ 0, 192 , 32, 32 });
	ShootGun_2_shoot.loop = true;
	ShootGun_2_shoot.speed = 0.1f;

	ShootGun_4_shoot.PushBack({ 128, 192 , 32, 32 });
	ShootGun_4_shoot.PushBack({ 160, 192 , 32, 32 });
	ShootGun_4_shoot.loop = true;
	ShootGun_4_shoot.speed = 0.1f;

	ShootGun_6_shoot.PushBack({ 32, 224, 32, 32 });
	ShootGun_6_shoot.PushBack({ 0, 224 , 32, 32 });
	ShootGun_6_shoot.loop = true;
	ShootGun_6_shoot.speed = 0.1f;

	ShootGun_8_shoot.PushBack({ 128, 224 , 32, 32 });
	ShootGun_8_shoot.PushBack({ 160, 224 , 32, 32 });
	ShootGun_8_shoot.loop = true;
	ShootGun_8_shoot.speed = 0.1f;


	Orv_1.PushBack({ 16, 496 , 7, 7 });
	Orv_2.PushBack({ 172,440 , 1, 1 });

	//Orv_2.PushBack({ 0, 300 , 32, 30 });
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Resources/Sprites/Characters/Player.png");
	currentLegsAnimation = &legs_down_idle;
	currentTopAnimation = &gun_down;
	currentOrv = &Orv_2;

	gunFx = App->audio->LoadFx("Resources/Audio/SFX/In-Game Sounds/Weapons_Sounds/Pistol_Shot.wav");

	position.x = 121;
	position.y = 135;

	ShootGun = false;

	bandera_Orv = false;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 15, 25 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	// Get gamepad info

	GamePad& pad = App->input->pads[0];



	if (bandera_GodMode == false) {
		if (((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) || pad.left_x < 0.0f || pad.left) && position.x >= 19) //LEFT
		{
			position.x -= speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) || pad.left_y < 0.0f || pad.up) { //LEFT UP
				diagonal = true;
				if (currentLegsAnimation != &legs_8)
				{
					currentLegsAnimation = &legs_8;

					if (shooting == false) {
						if (ShootGun && ShootGun_Contador > 0)
						{
							currentTopAnimation = &ShootGun_8;
						}
						else
						{

							currentTopAnimation = &gun_8;
						}
					}
				}
			}

			if ((currentLegsAnimation != &legs_l) && (diagonal == false)) //ANIMACIÓ LEFT
			{
				currentLegsAnimation = &legs_l;

				if (shooting == false) {
					if (ShootGun && ShootGun_Contador > 0)
					{
						currentTopAnimation = &ShootGun_l;
					}
					else
					{

						currentTopAnimation = &gun_l;
					}
				}
			}
		}

		if (((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) || pad.left_x > 0.0f || pad.right) && position.x <= 237-13) //RIGHT
		{
			position.x += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) || pad.left_y > 0.0f || pad.down) { //DOWN RIGHT
				diagonal = true;
				if (currentLegsAnimation != &legs_4)
				{
					currentLegsAnimation = &legs_4;

					if (shooting == false) {
						if (ShootGun && ShootGun_Contador > 0)
						{
							currentTopAnimation = &ShootGun_4;
						}
						else
						{

							currentTopAnimation = &gun_4;
						}
					}
				}
			}

			if (currentLegsAnimation != &legs_r && (diagonal == false))
			{
				currentLegsAnimation = &legs_r;

				if (shooting == false) {
					if (ShootGun && ShootGun_Contador > 0)
					{
						currentTopAnimation = &ShootGun_r;
					}
					else
					{

						currentTopAnimation = &gun_r;
					}
				}
			}
		}


		if (((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) || pad.left_y > 0.0f || pad.down) && position.y <= 214-25) //DOWN
		{
			position.y += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) || pad.left_x < 0.0f || pad.left) { //DOWN LEFT
				diagonal = true;
				if (currentLegsAnimation != &legs_6)
				{
					currentLegsAnimation = &legs_6;

					if (shooting == false) {
						if (ShootGun && ShootGun_Contador > 0)
						{
							currentTopAnimation = &ShootGun_6;
						}
						else
						{

							currentTopAnimation = &gun_6;
						}
					}
				}
			}

			if (currentLegsAnimation != &legs_down && (diagonal == false))
			{
				currentLegsAnimation = &legs_down;

				if (shooting == false) {
					if (ShootGun && ShootGun_Contador > 0)
					{
						currentTopAnimation = &ShootGun_down;
					}
					else
					{

						currentTopAnimation = &gun_down;
					}
				}
			}
		}

		if (((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) || pad.left_y < 0.0f || pad.up) && position.y >= 37) //UP
		{
			position.y -= speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) || pad.left_x > 0.0f || pad.right) { // UP RIGHT
				diagonal = true;
				if (currentLegsAnimation != &legs_2)
				{
					currentLegsAnimation = &legs_2;

					if (shooting == false) {
						if (ShootGun && ShootGun_Contador > 0)
						{
							currentTopAnimation = &ShootGun_2;
						}
						else
						{

							currentTopAnimation = &gun_2;
						}
					}
				}
			}

			if (currentLegsAnimation != &legs_up && (diagonal == false))
			{
				currentLegsAnimation = &legs_up;

				if (shooting == false) {
					if (ShootGun && ShootGun_Contador > 0)
					{
						currentTopAnimation = &ShootGun_up;
					}
					else
					{

						currentTopAnimation = &gun_up;
					}
				}
			}
		}

		if (MovKeyPressed < 2) {
			diagonal = false;
		}
		MovKeyPressed = 0;
	}
	if (bandera_GodMode == true) {
		if ((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) || pad.left_x < 0.0f) //LEFT
		{
			position.x -= speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) || pad.left_y < 0.0f) { //LEFT UP
				diagonal = true;
				if (currentLegsAnimation != &legs_8)
				{
					currentLegsAnimation = &legs_8;

					if (shooting == false) {
						if (ShootGun && ShootGun_Contador > 0)
						{
							currentTopAnimation = &ShootGun_8;
						}
						else
						{

							currentTopAnimation = &gun_8;
						}
					}
				}
			}

			if ((currentLegsAnimation != &legs_l) && (diagonal == false)) //ANIMACIÓ LEFT
			{
				currentLegsAnimation = &legs_l;

				if (shooting == false) {
					if (ShootGun && ShootGun_Contador > 0)
					{
						currentTopAnimation = &ShootGun_l;
					}
					else
					{

						currentTopAnimation = &gun_l;
					}
				}
			}
		}

		if ((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) || pad.left_x > 0.0f) //RIGHT
		{
			position.x += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) || pad.left_y > 0.0f) { //DOWN RIGHT
				diagonal = true;
				if (currentLegsAnimation != &legs_4)
				{
					currentLegsAnimation = &legs_4;

					if (shooting == false) {
						if (ShootGun && ShootGun_Contador > 0)
						{
							currentTopAnimation = &ShootGun_4;
						}
						else
						{

							currentTopAnimation = &gun_4;
						}
					}
				}
			}

			if (currentLegsAnimation != &legs_r && (diagonal == false))
			{
				currentLegsAnimation = &legs_r;

				if (shooting == false) {
					if (ShootGun && ShootGun_Contador > 0)
					{
						currentTopAnimation = &ShootGun_r;
					}
					else
					{

						currentTopAnimation = &gun_r;
					}
				}
			}
		}

		if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) || pad.left_y > 0.0f) //DOWN
		{
			position.y += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) || pad.left_x < 0.0f) { //DOWN LEFT
				diagonal = true;
				if (currentLegsAnimation != &legs_6)
				{
					currentLegsAnimation = &legs_6;

					if (shooting == false) {
						if (ShootGun && ShootGun_Contador > 0)
						{
							currentTopAnimation = &ShootGun_6;
						}
						else
						{

							currentTopAnimation = &gun_6;
						}
					}
				}
			}

			if (currentLegsAnimation != &legs_down && (diagonal == false))
			{
				currentLegsAnimation = &legs_down;

				if (shooting == false) {
					if (ShootGun && ShootGun_Contador > 0)
					{
						currentTopAnimation = &ShootGun_down;
					}
					else
					{

						currentTopAnimation = &gun_down;
					}
				}
			}
		}

		if ((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) || pad.left_y < 0.0f) //UP
		{
			position.y -= speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) || pad.left_x > 0.0f) { // UP RIGHT
				diagonal = true;
				if (currentLegsAnimation != &legs_2)
				{
					currentLegsAnimation = &legs_2;

					if (shooting == false) {
						if (ShootGun && ShootGun_Contador > 0)
						{
							currentTopAnimation = &ShootGun_2;
						}
						else
						{

							currentTopAnimation = &gun_2;
						}
					}
				}
			}

			if (currentLegsAnimation != &legs_up && (diagonal == false))
			{
				currentLegsAnimation = &legs_up;

				if (shooting == false) {
					if (bandera) {
						if (ShootGun && ShootGun_Contador > 0)
						{
							currentTopAnimation = &ShootGun_up;
						}
						else

							currentTopAnimation = &gun_up;
						}
					
				}
			}
		}

		if (MovKeyPressed < 2) {
			diagonal = false;
		}
		MovKeyPressed = 0;
	}

	if (ShootGun == true)
	{
		ShootGun_Contador--;
	}


	//Direccion de donde va la bala
		//DIAGONALS
	cont++;
	if (cont >= 10) { //DELAY
		bandera = true;
		cont = 0;
	}
	else {
		bandera = false;
	}

	if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT
		|| App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT
		|| App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT
		|| App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT
		|| (pad.right_x > 0.0f)
		|| (pad.right_x < 0.0f)
		|| (pad.right_y > 0.0f)
		|| (pad.right_y < 0.0f))
	{
		shooting = true;
	}
	else {
		shooting = false;
	}

	if ((App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT) || (pad.right_x > 0.0f && pad.right_y < 0.0f)) //drt, amunt
	{

		

		if (bandera) {
			if (ShootGun && ShootGun_Contador > 0)
			{


				App->particles->AddParticle(App->particles->shotgun_1, position.x + 14, position.y-5, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_2, position.x + 14, position.y-5, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_3, position.x + 14, position.y-5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
				currentTopAnimation = &ShootGun_2_shoot;
			}
			else
			{
				App->particles->AddParticle(App->particles->bullet_2, position.x + 7, position.y - 5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_2_shoot;
			}
		}
	}
	else if ((App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) || (pad.right_x < 0.0f && pad.right_y < 0.0f)) //Esq, amunt
	{

		

		if (bandera) {
			if (ShootGun && ShootGun_Contador > 0)
			{
				App->particles->AddParticle(App->particles->shotgun_7, position.x - 5, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_8, position.x - 5, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_1, position.x -5, position.y-10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
				currentTopAnimation = &ShootGun_8_shoot;
			}
			else
			{
				App->particles->AddParticle(App->particles->bullet_8, position.x - 5, position.y - 10,Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_8_shoot;
			}
		}
	}
	else if ((App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) || (pad.right_x < 0.0f && pad.right_y > 0.0f)) //Esq, avall
	{
		if (bandera) {
			if (ShootGun && ShootGun_Contador > 0)
			{

				App->particles->AddParticle(App->particles->shotgun_7, position.x - 8, position.y + 11, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_6, position.x - 8, position.y + 11, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_5, position.x - 8, position.y + 11, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
				currentTopAnimation = &ShootGun_6_shoot;
			}
			else
			{
				App->particles->AddParticle(App->particles->bullet_6, position.x - 8, position.y + 11, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_6_shoot;
			}
		}
	}
	else if ((App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) || (pad.right_x > 0.0f && pad.right_y > 0.0f)) //drt, avall
	{

		

		if (bandera) {
			if (ShootGun && ShootGun_Contador > 0)
			{
				App->particles->AddParticle(App->particles->shotgun_3, position.x + 15, position.y + 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_4, position.x + 15, position.y + 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_5, position.x + 15, position.y + 10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
				currentTopAnimation = &ShootGun_4_shoot;
			}
			else
			{
				App->particles->AddParticle(App->particles->bullet_4, position.x + 8, position.y + 8, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_4_shoot;
			}
		}
	}
	//RECTES
	else if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT || pad.right_y < 0.0f || pad.y) //amunt
	{
		

		if (bandera) {
			if (ShootGun && ShootGun_Contador > 0)
			{
				App->particles->AddParticle(App->particles->shotgun_8, position.x + 5, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_1, position.x + 5, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_2, position.x + 5, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
				currentTopAnimation = &ShootGun_up_shoot;
			}
			else
			{
				App->particles->AddParticle(App->particles->bullet_up, position.x + 5, position.y-10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_up_shoot;
			}
		}

	}
	else if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || pad.right_x < 0.0f || pad.x) //Esq
	{

		

		if (bandera) {
			if (ShootGun && ShootGun_Contador > 0)
			{
				App->particles->AddParticle(App->particles->shotgun_8, position.x - 18, position.y + 4, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_7, position.x - 18, position.y + 4, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_6, position.x - 18, position.y + 4, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
				currentTopAnimation = &ShootGun_l_shoot;
			}
			else
			{
				App->particles->AddParticle(App->particles->bullet_l, position.x-18, position.y + 4, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_l_shoot;
			}
		}
	}
	else if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT || pad.right_y > 0.0f || pad.a) // avall
	{

		

		if (bandera) {
			if (ShootGun && ShootGun_Contador > 0)
			{
				App->particles->AddParticle(App->particles->shotgun_4, position.x + 5, position.y + 8, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_5, position.x + 5, position.y + 12, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_6, position.x + 5, position.y + 12, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
				currentTopAnimation = &ShootGun_down_shoot;
			}
			else
			{
				App->particles->AddParticle(App->particles->bullet_down, position.x + 5, position.y + 12, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_down_shoot;
			}
		}
	}
	else if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || pad.right_x > 0.0f || pad.b) //drt
	{

		

		if (bandera) {
			if (ShootGun && ShootGun_Contador > 0)
			{
				App->particles->AddParticle(App->particles->shotgun_2, position.x + 20, position.y + 4, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_3, position.x + 20, position.y + 4, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_4, position.x + 20, position.y + 4, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
				currentTopAnimation = &ShootGun_r_shoot;
			}
			else
			{

				App->particles->AddParticle(App->particles->bullet_r, position.x + 20, position.y + 4, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_r_shoot;
			}
		}
	}

	if (bandera_Orv == true)
	{
		Orv_Contador--;
		currentOrv = &Orv_1;
	}

	if (bandera_Orv ==false)
	{
		currentOrv = &Orv_2;
	}

	if ( bandera_Orv = true && Orv_Contador > 0 )
	{
		if ((App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT) || (pad.right_x > 0.0f && pad.right_y < 0.0f)) //drt, amunt
		{
			if (bandera) {
				if (ShootGun && ShootGun_Contador > 0)
				{
					App->particles->AddParticle(App->particles->shotgun_1, position.x -12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_2, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_3, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
				}
				else
				{
					App->particles->AddParticle(App->particles->bullet_2, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
				}
			}
		}
		else if ((App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) || (pad.right_x < 0.0f && pad.right_y < 0.0f)) //Esq, amunt
		{
			if (bandera) {
				if (ShootGun && ShootGun_Contador > 0)
				{
					App->particles->AddParticle(App->particles->shotgun_7, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_8, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_1, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);

				}
				else
				{
					App->particles->AddParticle(App->particles->bullet_8, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);

				}
			}
		}
		else if ((App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) || (pad.right_x < 0.0f && pad.right_y > 0.0f)) //Esq, avall
		{
			if (bandera) {
				if (ShootGun && ShootGun_Contador > 0)
				{

					App->particles->AddParticle(App->particles->shotgun_7, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_6, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_5, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(gunFx);

				}
				else
				{
					App->particles->AddParticle(App->particles->bullet_6, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
				}
			}
		}
		else if ((App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) || (pad.right_x > 0.0f && pad.right_y > 0.0f)) //drt, avall
		{
			if (bandera) {
				if (ShootGun && ShootGun_Contador > 0)
				{
					App->particles->AddParticle(App->particles->shotgun_3, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_4, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_5, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
				}
				else
				{
					App->particles->AddParticle(App->particles->bullet_4, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);

				}
			}
		}
		//RECTES
		else if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT || pad.right_y < 0.0f || pad.y) //amunt
		{


			if (bandera) {
				if (ShootGun && ShootGun_Contador > 0)
				{
					App->particles->AddParticle(App->particles->shotgun_8, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_1, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_2, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
				}
				else
				{
					App->particles->AddParticle(App->particles->bullet_up, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);

				}
			}

		}
		else if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || pad.right_x < 0.0f || pad.x) //Esq
		{



			if (bandera) {
				if (ShootGun && ShootGun_Contador > 0)
				{
					App->particles->AddParticle(App->particles->shotgun_8, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_7, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_6, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);

				}
				else
				{
					App->particles->AddParticle(App->particles->bullet_l, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);

				}
			}
		}
		else if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT || pad.right_y > 0.0f || pad.a) // avall
		{
			if (bandera) {
				if (ShootGun && ShootGun_Contador > 0)
				{
					App->particles->AddParticle(App->particles->shotgun_4, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_5, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_6, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
				}
				else
				{
					App->particles->AddParticle(App->particles->bullet_down, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
				}
			}
		}
		else if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || pad.right_x > 0.0f || pad.b) //drt
		{



			if (bandera) {
				if (ShootGun && ShootGun_Contador > 0)
				{
					App->particles->AddParticle(App->particles->shotgun_2, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_3, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->shotgun_4, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
				}
				else
				{

					App->particles->AddParticle(App->particles->bullet_r, position.x - 12, position.y - 7, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(gunFx);
				}
			}
		}
	}





	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {

		currentLegsAnimation = &legs_down_idle;
		if (!shooting) {
			if (ShootGun && ShootGun_Contador > 0)
			{
				currentTopAnimation = &ShootGun_down;
			}
			else
			{

				currentTopAnimation = &gun_down;
			}
		}
	}

	collider->SetPos(position.x, position.y);

	currentLegsAnimation->Update();
	currentTopAnimation->Update();

	if (App->input->keys[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN) {
		bandera_GodMode = !bandera_GodMode;
	}

	//
	if (App->input->keys[SDL_SCANCODE_B] == KEY_STATE::KEY_REPEAT) {
		ShootGun = true;
		ShootGun_Contador = 500;
	}



	if (App->input->keys[SDL_SCANCODE_V] == KEY_STATE::KEY_REPEAT) {
		bandera_Orv = true;
		Orv_Contador = 500;

	}
	
	// F3 Direct Win
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN && App->sceneLevel->Level_1) {
		App->fade->FadeToBlack((Module*)App->sceneLevel, (Module*)App->sceneWin, 0);
	}
	else if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN && App->sceneLevel2->Level_2) {
		App->fade->FadeToBlack((Module*)App->sceneLevel2, (Module*)App->sceneWin, 0);
	}

	// F4 Direct Lose
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN && App->sceneLevel->Level_1) {
		App->fade->FadeToBlack((Module*)App->sceneLevel, (Module*)App->sceneLose, 0);
	}
	else if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN && App->sceneLevel2->Level_2) {
		App->fade->FadeToBlack((Module*)App->sceneLevel2, (Module*)App->sceneLose, 0);
	}

	//F7 spawnea todos los objetos
	if (App->input->keys[SDL_SCANCODE_F7] == KEY_STATE::KEY_REPEAT) {
		App->particles->AddParticle(App->particles->ShootGun_PowerUp, 58, 126, Collider::Type::SHOOTGUN_POWERUP);
		App->particles->AddParticle(App->particles->Orv_PowerUp, 200, 126, Collider::Type::ORV_POWERUP);
	}

	//F6 spawnea todos los enemigos
	if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
		App->enemies->AddEnemy(Enemy_Type::GREEN, 26, 63);
		App->enemies->AddEnemy(Enemy_Type::PINK, 231, 45);
	}

	// F5 Pasar segundo nivel
	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN && App->sceneLevel->Level_1) {
		App->fade->FadeToBlack((Module*)App->sceneLevel, (Module*)App->sceneLevel2, 0);
	}



	collider->SetPos(position.x, position.y);

	currentLegsAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect Orv = currentOrv->GetCurrentFrame();
	App->render->Blit(texture, position.x -15, position.y - 10, &Orv, 1.5f);


	SDL_Rect rect = currentLegsAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x-2, position.y+10, &rect, 1.5f);

	SDL_Rect rectTop = currentTopAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x - 10, position.y - 7, &rectTop, 1.5f);

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{	

	if (c2->type == c2->DOOR && App->sceneLevel->sceneTimer >= 3600 && App->enemies->enemyNum == 0) {

		App->fade->FadeToBlack((Module*)App->sceneLevel, (Module*)App->sceneLevel2, 0);
	}

	if (c2->type == c2->SHOOTGUN_POWERUP) {

		ShootGun = true;
		ShootGun_Contador = 500;
	}

	if (c2->type == c2->ORV_POWERUP) {

		bandera_Orv = true;
		Orv_Contador = 500;
	}


	if (c2->type == c2->ENEMY && bandera_GodMode == false && destroyed == false) {

		if (vides > 0) {
			destroyed = false;
			--vides;
		}
		else if (vides == 0) {

			App->fade->FadeToBlack((Module*)App->sceneLevel, (Module*)App->sceneLose, 0);
			destroyed = true;

		}
		contadorVides = 50; //50 frames de delay
	}
}

bool ModulePlayer::CleanUp() {

	LOG("Freeing player");

	//desinicialitzar tots els sprites
	App->textures->Unload(texture);
	
	App->textures->Unload(textureUI);
	App->textures->Unload(textureFont);



	//App->audio->CleanFX(laserFx);

	return true;
}