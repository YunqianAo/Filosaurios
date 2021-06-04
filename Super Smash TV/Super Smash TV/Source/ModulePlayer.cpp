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

	//textureDoorTop = App->textures->Load("Assets/SpritesSSTV/EditSpritesSSTV_Portes.png");

	//textureUI = App->textures->Load("Assets/SpritesSSTV/EditSpritesSSTV_UI.png");

	//textureFont = App->textures->Load("Assets/SpritesSSTV/Font.png"); //Font

	//textureMort = App->textures->Load("Assets/SpritesSSTV/Game_Over.png"); //Mort

	//texturePickups = App->textures->Load("Assets/SpritesSSTV/Entity_Projectiles_and_gift.png");

	gunFx = App->audio->LoadFx("Resources/Audio/SFX/In-Game Sounds/Weapons_Sounds/Pistol_Shot.wav");



	position.x = 121;
	position.y = 135;

	bandera_trip = false;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 15, 25 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	// Get gamepad info

	GamePad& pad = App->input->pads[0];

	// Moving the player with the camera scroll
	//App->player->position.x += 0;
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN) {
		bandera_GodMode = !bandera_GodMode;
	}

	//if (App->input->keys[SDL_SCANCODE_F9] == KEY_STATE::KEY_DOWN && App->SceneLevel->lvl1) {
	//	App->SceneLevel->sceneTimer = 3600;
	//}
	//if (App->input->keys[SDL_SCANCODE_F9] == KEY_STATE::KEY_DOWN && App->sceneLevel2->lvl2) {
	//	App->sceneLevel2->sceneTimer = 3600;
	//}


	if (bandera_GodMode == false) {
		if (((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) || pad.left_x < 0.0f || pad.left) && position.x >= 28) //LEFT
		{
			position.x -= speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) || pad.left_y < 0.0f || pad.up) { //LEFT UP
				diagonal = true;
				if (currentLegsAnimation != &legs_8)
				{
					currentLegsAnimation = &legs_8;

					if (shooting == false) {
						if (bandera_trip && cont_Tripel > 0)
						{

						}
						else
						{

							currentTopAnimation = &gun_8;
						}
					}
				}
			}

			if ((currentLegsAnimation != &legs_l) && (diagonal == false)) //ANIMACI� LEFT
			{
				currentLegsAnimation = &legs_l;

				if (shooting == false) {
					if (bandera_trip && cont_Tripel > 0)
					{

					}
					else
					{

						currentTopAnimation = &gun_l;
					}
				}
			}
		}

		if (((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) || pad.left_x > 0.0f || pad.right) && position.x <= 455) //RIGHT
		{
			position.x += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) || pad.left_y > 0.0f || pad.down) { //DOWN RIGHT
				diagonal = true;
				if (currentLegsAnimation != &legs_4)
				{
					currentLegsAnimation = &legs_4;

					if (shooting == false) {
						if (bandera_trip && cont_Tripel > 0)
						{

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
					if (bandera_trip && cont_Tripel > 0)
					{

					}
					else
					{

						currentTopAnimation = &gun_r;
					}
				}
			}
		}
		/* MANDO PROVA
		if (pad.left_y > 0.0f) {
				App->input->keys[SDL_SCANCODE_S] = (SDL_SCANCODE_S == KEY_STATE::KEY_IDLE) ? KEY_STATE::KEY_DOWN : KEY_STATE::KEY_REPEAT;
				App->input->keys[SDL_SCANCODE_S] = (SDL_SCANCODE_S == KEY_STATE::KEY_REPEAT || SDL_SCANCODE_S == KEY_STATE::KEY_DOWN) ? KEY_STATE::KEY_UP : KEY_STATE::KEY_IDLE;
		}*/

		if (((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) || pad.left_y > 0.0f || pad.down) && position.y <= 390) //DOWN
		{
			position.y += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) || pad.left_x < 0.0f || pad.left) { //DOWN LEFT
				diagonal = true;
				if (currentLegsAnimation != &legs_6)
				{
					currentLegsAnimation = &legs_6;

					if (shooting == false) {
						if (bandera_trip && cont_Tripel > 0)
						{

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
					if (bandera_trip && cont_Tripel > 0)
					{

					}
					else
					{

						currentTopAnimation = &gun_down;
					}
				}
			}
		}

		if (((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) || pad.left_y < 0.0f || pad.up) && position.y >= 60) //UP
		{
			position.y -= speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) || pad.left_x > 0.0f || pad.right) { // UP RIGHT
				diagonal = true;
				if (currentLegsAnimation != &legs_2)
				{
					currentLegsAnimation = &legs_2;

					if (shooting == false) {
						if (bandera_trip && cont_Tripel > 0)
						{

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
					if (bandera_trip && cont_Tripel > 0)
					{

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
						if (bandera_trip && cont_Tripel > 0)
						{

						}
						else
						{

							currentTopAnimation = &gun_8;
						}
					}
				}
			}

			if ((currentLegsAnimation != &legs_l) && (diagonal == false)) //ANIMACI� LEFT
			{
				currentLegsAnimation = &legs_l;

				if (shooting == false) {
					if (bandera_trip && cont_Tripel > 0)
					{

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
						if (bandera_trip && cont_Tripel > 0)
						{

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
					if (bandera_trip && cont_Tripel > 0)
					{

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
						if (bandera_trip && cont_Tripel > 0)
						{

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
					if (bandera_trip && cont_Tripel > 0)
					{

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
						if (bandera_trip && cont_Tripel > 0)
						{

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
						if (bandera_trip && cont_Tripel > 0)
						{
							cont = 0;
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

	if (bandera_trip == true)
	{
		cont_Tripel--;
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
			if (bandera_trip && cont_Tripel > 0)
			{


				App->particles->AddParticle(App->particles->shotgun_1, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_2, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_3, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
			}
			else
			{
				App->particles->AddParticle(App->particles->bullet_2, position.x + 7, position.y - 12, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_2_shoot;
			}
		}
	}
	else if ((App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) || (pad.right_x < 0.0f && pad.right_y < 0.0f)) //Esq, amunt
	{

		

		if (bandera) {
			if (bandera_trip && cont_Tripel > 0)
			{
				App->particles->AddParticle(App->particles->shotgun_7, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_8, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_1, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
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
			if (bandera_trip && cont_Tripel > 0)
			{



				App->particles->AddParticle(App->particles->shotgun_7, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_6, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_5, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
			}
			else
			{
				App->particles->AddParticle(App->particles->bullet_6, position.x - 12, position.y + 11, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_6_shoot;
			}
		}
	}
	else if ((App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) || (pad.right_x > 0.0f && pad.right_y > 0.0f)) //drt, avall
	{

		

		if (bandera) {
			if (bandera_trip && cont_Tripel > 0)
			{



				App->particles->AddParticle(App->particles->shotgun_3, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_4, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_5, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
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
			if (bandera_trip && cont_Tripel > 0)
			{
;

			App->particles->AddParticle(App->particles->shotgun_8, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shotgun_1, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shotgun_2, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(gunFx);
				cont = 0;
			}
			else
			{
				App->particles->AddParticle(App->particles->bullet_up, position.x + 14, position.y, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_up_shoot;
			}
		}

	}
	else if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || pad.right_x < 0.0f || pad.x) //Esq
	{

		

		if (bandera) {
			if (bandera_trip && cont_Tripel > 0)
			{


				App->particles->AddParticle(App->particles->shotgun_8, position.x - 4, position.y + 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_7, position.x - 4, position.y + 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_6, position.x - 4, position.y + 10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
			}
			else
			{
				App->particles->AddParticle(App->particles->bullet_l, position.x - 4, position.y + 10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_l_shoot;
			}
		}
	}
	else if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT || pad.right_y > 0.0f || pad.a) // avall
	{

		

		if (bandera) {
			if (bandera_trip && cont_Tripel > 0)
			{


				App->particles->AddParticle(App->particles->shotgun_4, position.x + 16, position.y + 20, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_5, position.x + 16, position.y + 20, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_6, position.x + 16, position.y + 20, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
			}
			else
			{
				App->particles->AddParticle(App->particles->bullet_down, position.x + 16, position.y + 20, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_down_shoot;
			}
		}
	}
	else if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || pad.right_x > 0.0f || pad.b) //drt
	{

		

		if (bandera) {
			if (bandera_trip && cont_Tripel > 0)
			{


				App->particles->AddParticle(App->particles->shotgun_2, position.x + 28, position.y + 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_3, position.x + 28, position.y + 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->shotgun_4, position.x + 28, position.y + 10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				cont = 0;
			}
			else
			{

				App->particles->AddParticle(App->particles->bullet_r, position.x + 28, position.y + 10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(gunFx);
				currentTopAnimation = &gun_r_shoot;
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
			if (bandera_trip && cont_Tripel > 0)
			{

			}
			else
			{

				currentTopAnimation = &gun_down;
			}
		}
	}

	// L6: DONE 4: Update collider position to player position
	collider->SetPos(position.x, position.y);

	currentLegsAnimation->Update();
	currentTopAnimation->Update();

	//Gesti� Array de la font
	scoreCopia = score;

	for (int i = 0; i < 8; ++i) {
		scoreN[i] = scoreCopia % 10;
		scoreCopia /= 10;
	}

	--contadorVides;
	if (contadorVides < -100) {
		contadorVides = -1;
	}

	//F6 TripleShoot
	if (App->input->keys[SDL_SCANCODE_B] == KEY_STATE::KEY_REPEAT) {
		bandera_trip = true;
		cont_Tripel = 500;
	}

	////F7 spawnea todos los objetos
	//if (App->input->keys[SDL_SCANCODE_F7] == KEY_STATE::KEY_REPEAT) {
	//	App->particles->AddParticle(App->particles->Triple, 235, 190, 6, Collider::Type::object_Triple);
	//	App->particles->AddParticle(App->particles->vidaUp, 370, 190, 6, Collider::Type::object_Vida);
	//}

	////F8 spawnea todos los enemigos
	//if (App->input->keys[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN) {
	//	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 100, 400);
	//	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 370, 400);
	//}

	////F9 Teimpo del nivel
	//if (App->input->keys[SDL_SCANCODE_F9] == KEY_STATE::KEY_DOWN && App->SceneLevel->lvl1) {
	//	App->SceneLevel->sceneTimer = 3600;
	//}
	//if (App->input->keys[SDL_SCANCODE_F9] == KEY_STATE::KEY_DOWN && App->sceneLevel2->lvl2) {
	//	App->sceneLevel2->sceneTimer = 3600;
	//}

	////F3 mas el numero de la sala pasa a aquella sala
	//if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_REPEAT && App->SceneLevel->lvl1)
	//	App->fade->FadeToBlack((Module*)App->SceneLevel, (Module*)App->SceneLevel, 20);
	//if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_REPEAT && App->SceneLevel->lvl1)
	//	App->fade->FadeToBlack((Module*)App->SceneLevel, (Module*)App->sceneLevel2, 20);
	///*if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_REPEAT && App->SceneLevel->lvl1)
	//App->fade->FadeToBlack((Module*)App->SceneLevel, (Module*)App->BOSS, 20);		//Escena del boss per implementar  */

	//if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_REPEAT && App->sceneLevel2->lvl2)
	//	App->fade->FadeToBlack((Module*)App->sceneLevel2, (Module*)App->SceneLevel, 20);
	//if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_REPEAT && App->sceneLevel2->lvl2)
	//	App->fade->FadeToBlack((Module*)App->sceneLevel2, (Module*)App->sceneLevel2, 20);
	/*if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_REPEAT && App->SceneLevel->lvl1)
	App->fade->FadeToBlack((Module*)App->SceneLevel, (Module*)App->BOSS, 20);		//Escena del boss per implementar  */

	/*//Escen del boss per implementar
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_REPEAT && App->SceneLevel->lvl1)
		App->fade->FadeToBlack((Module*)App->SceneLevel, (Module*)App->SceneLevel, 20);
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_REPEAT && App->SceneLevel->lvl1)
		App->fade->FadeToBlack((Module*)App->SceneLevel, (Module*)App->sceneLevel2, 20);
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_REPEAT && App->SceneLevel->lvl1)
	App->fade->FadeToBlack((Module*)App->SceneLevel, (Module*)App->BOSS, 20); */



	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) { //necessita col�lidir amb un enemic al final per morir
		vides--;
	}

	//if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN && App->SceneLevel->lvl1)
	//	App->fade->FadeToBlack((Module*)App->SceneLevel, (Module*)App->sceneWin, 20);

	//if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN && App->sceneLevel2->lvl2)
	//	App->fade->FadeToBlack((Module*)App->sceneLevel2, (Module*)App->sceneWin, 20);
	/*if (pad.enabled)
	{
		if (pad.left_x == 0.0f && pad.left_y == 0.0f) currentLegsAnimation = &idleAnim;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) currentLegsAnimation = &idleAnim;*/

	collider->SetPos(position.x, position.y);

	currentLegsAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{

	SDL_Rect rect = currentLegsAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x-2, position.y+10, &rect, 1.5f);

	SDL_Rect rectTop = currentTopAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x - 10, position.y - 7, &rectTop, 1.5f);

	//Render Portes
	if (ImprimirPortes)
		App->render->Blit(textureDoorTop, -512 * topDoor, 0, nullptr);
	//Si no li enviem rectangle (li enviem un 'nullptr'), es posa la mateixa mida que la pantalla.

	//Render UI
	App->render->Blit(textureUI, 0, 0, nullptr);

	//Render Vides
	SDL_Rect rect0v = { 0, 16, 10, 14 };
	SDL_Rect rect1v = { 10, 16, 10, 14 };
	SDL_Rect rect2v = { 20, 16, 10, 14 };
	SDL_Rect rect3v = { 30, 16, 10, 14 };
	SDL_Rect rect4v = { 40, 16, 10, 14 };
	SDL_Rect rect5v = { 50, 16, 10, 14 };
	SDL_Rect rect6v = { 60, 16, 10, 14 };
	SDL_Rect rect7v = { 70, 16, 10, 14 };
	SDL_Rect rect8v = { 80, 16, 10, 14 };
	SDL_Rect rect9v = { 90, 16, 10, 14 };
	SDL_Rect rect10v = { 0, 0, 512, 512 };

	switch (vides) {
	case 0:
		App->render->Blit(textureFont, 43, 54, &rect0v, 1.5f);
		break;
	case 1:
		App->render->Blit(textureFont, 43, 54, &rect1v, 1.5f);
		break;
	case 2:
		App->render->Blit(textureFont, 43, 54, &rect2v, 1.5f);
		break;
	case 3:
		App->render->Blit(textureFont, 43, 54, &rect3v, 1.5f);
		break;
	case 4:
		App->render->Blit(textureFont, 43, 54, &rect4v, 1.5f);
		break;
	case 5:
		App->render->Blit(textureFont, 43, 54, &rect5v, 1.5f);
		break;
	case 6:
		App->render->Blit(textureFont, 43, 54, &rect6v, 1.5f);
		break;
	case 7:
		App->render->Blit(textureFont, 43, 54, &rect7v, 1.5f);
		break;
	case 8:
		App->render->Blit(textureFont, 43, 54, &rect8v, 1.5f);
		break;
	case 9:
		App->render->Blit(textureFont, 43, 54, &rect9v, 1.5f);
		break;
	}


	if (vides <= 0)
	{
		App->render->Blit(textureMort, 0, 0, &rect10v, 1);
		//App->pause = true;
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{		//Falta cambiar el sumatori de punts segons el tipus de objecte que agafes

	//if (c2->type == c2->object_Triple)
	//{
	//	bandera_trip = true;
	//	cont_Tripel = 500;
	//}

	//if (c2->type == c2->object_Vida)
	//{
	//	vides++;
	//}

	//if (c2->type == c2->Door && App->SceneLevel->sceneTimer >= 3600 && App->enemies->enemyNum == 0) {
	//	//	WIN CONDITION
	//	App->fade->FadeToBlack((Module*)App->SceneLevel, (Module*)App->sceneSwap, 0); //sceneWin, sceneSwap
	//}

	//GESTIONAR LES VIDES I LA MORT
	if ((c2->type == c2->ENEMY) && (contadorVides < 0) && (bandera_GodMode == false) && (destroyed == false)) {

		if (vides > 0) {
			--vides;
		}
		else if (vides <= 0) {		//FALTA PULIR MOLTISSIM!!!!!
			App->audio->PlayFx(explosionFx);

			App->fade->FadeToBlack((Module*)App->sceneLevel, (Module*)App->sceneLose, 90);
			destroyed = true;

			destroyed = false;
		}
		contadorVides = 50; //50 frames de delay
	}
}

bool ModulePlayer::CleanUp() {

	LOG("Freeing player");

	//desinicialitzar tots els sprites
	App->textures->Unload(texture);
	App->textures->Unload(textureDoorTop);
	App->textures->Unload(textureUI);
	App->textures->Unload(textureFont);
	App->textures->Unload(textureMort);
	App->textures->Unload(texturePickups);

	//App->audio->CleanFX(laserFx);

	return true;
}