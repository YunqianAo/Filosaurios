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

	idleDAnim.PushBack({ 128, 32, 16, 16 });
	idleURAnim.PushBack({ 144, 32, 16, 16 });
	idleLRAnim.PushBack({ 160, 32, 16, 16 });
	idleULAnim.PushBack({ 176, 32, 16, 16 });
	idleUAnim.PushBack({ 192, 32, 16, 16 });
	//nome cames

	// Move upwards
	downAnim.Empty();
	downAnim.PushBack({ 0, 32, 16, 16 });
	downAnim.PushBack({ 16, 32, 16, 16 });
	downAnim.PushBack({ 32, 32, 16, 16 });
	downAnim.PushBack({ 48, 32, 16, 16 });
	downAnim.PushBack({ 64, 32, 16, 16 });
	downAnim.PushBack({ 80, 32, 16, 16 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;


	upAnim.PushBack({ 0, 0, 16, 16 });
	upAnim.PushBack({ 16, 0, 16, 16 });
	upAnim.PushBack({ 32, 0, 16, 16 });
	upAnim.PushBack({ 48, 0, 16, 16 });
	upAnim.PushBack({ 64, 0, 16, 16 });
	upAnim.PushBack({ 80, 0, 16, 16 });
	upAnim.PushBack({ 96, 0, 16, 16 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	//Move rigth 
	rigthAnim.PushBack({ 0, 16, 16, 16 });
	rigthAnim.PushBack({ 16, 16, 16, 16 });
	rigthAnim.PushBack({ 32, 16, 16, 16 });
	rigthAnim.PushBack({ 48, 16, 16, 16 });
	rigthAnim.PushBack({ 64, 16, 16, 16 });
	rigthAnim.PushBack({ 80, 16, 16, 16 });
	rigthAnim.PushBack({ 96, 16, 16, 16 });
	rigthAnim.loop = true;
	rigthAnim.speed = 0.1f;

	//Move left

	leftAnim.PushBack({ 0, 208, 16, 16 });
	leftAnim.PushBack({ 16, 208, 16, 16 });
	leftAnim.PushBack({ 32, 208, 16, 16 });
	leftAnim.PushBack({ 48, 208, 16, 16 });
	leftAnim.PushBack({ 64, 208, 16, 16 });
	leftAnim.PushBack({ 80, 208, 16, 16 });
	leftAnim.PushBack({ 96, 208, 16, 16 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	//Diagonal Secundaria

	diagonalSAnim.PushBack({ 128, 0, 16, 16 });
	diagonalSAnim.PushBack({ 144, 0, 16, 16 });
	diagonalSAnim.PushBack({ 160, 0, 16, 16 });
	diagonalSAnim.PushBack({ 176, 0, 16, 16 });
	diagonalSAnim.PushBack({ 192, 0, 16, 16 });
	diagonalSAnim.PushBack({ 208, 0, 16, 16 });
	diagonalSAnim.loop = true;
	diagonalSAnim.speed = 0.1f;

	//Diagonal Principal

	diagonalPAnim.PushBack({ 128, 16, 16, 16 });
	diagonalPAnim.PushBack({ 144, 16, 16, 16 });
	diagonalPAnim.PushBack({ 160, 16, 16, 16 });
	diagonalPAnim.PushBack({ 176, 16, 16, 16 });
	diagonalPAnim.PushBack({ 192, 16, 16, 16 });
	diagonalPAnim.PushBack({ 208, 16, 16, 16 });
	diagonalPAnim.PushBack({ 224, 16, 16, 16 });
	diagonalPAnim.loop = true;
	diagonalPAnim.speed = 0.1f;

	//Diagonal Secundaria Reverse

	diagonalSRAnim.PushBack({ 0, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 16, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 32, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 48, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 64, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 80, 224, 16, 16 });
	diagonalSRAnim.loop = true;
	diagonalSRAnim.speed = 0.1f;

	//Diagonal Principal Reverse

	diagonalPRAnim.PushBack({ 0, 240, 16, 16 });
	diagonalPRAnim.PushBack({ 16, 240, 16, 16 });
	diagonalPRAnim.PushBack({ 32, 240, 16, 16 });
	diagonalPRAnim.PushBack({ 48, 240, 16, 16 });
	diagonalPRAnim.PushBack({ 64, 240, 16, 16 });
	diagonalPRAnim.PushBack({ 80, 240, 16, 16 });
	diagonalPRAnim.PushBack({ 96, 240, 16, 16 });
	diagonalPRAnim.loop = true;
	diagonalPRAnim.speed = 0.1f;


	//ANIMACIONS TOP HOME

	gun_down.PushBack({ 0, 64, 32, 32 });
	gun_up.PushBack({ 96, 64, 32, 32 });
	gun_l.PushBack({ 32, 64, 32, 32 });
	gun_r.PushBack({ 64, 64, 32, 32 });

	topURAnim.PushBack({ 96, 48, 32, 32 });
	topULAnim.PushBack({ 176, 208, 32, 32 });
	topDRAnim.PushBack({ 32, 48, 32, 32 });
	topDLAnim.PushBack({ 112, 208, 32, 32 });

	//ANIMACIONS DISPARANT TOP HOME

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
	shootDRAnim.PushBack({ 192, 48, 32, 32 });
	shootDLAnim.PushBack({ 256, 48, 32, 32 });
	shootURAnim.PushBack({ 0, 80, 32, 32 });
	shootULAnim.PushBack({ 256, 80, 32, 32 });
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Resources/Sprites/Characters/Player.png");
	currentAnimation = &idleUAnim;
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

	collider = App->collisions->AddCollider({ position.x, position.y, 14, -25 }, Collider::Type::PLAYER, this);

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
				if (currentAnimation != &diagonalPRAnim)
				{
					diagonalPRAnim.Reset();
					currentAnimation = &diagonalPRAnim;

					if (shooting == false) {
						topULAnim.Reset();
						currentTopAnimation = &topULAnim;
					}
				}
			}

			if ((currentAnimation != &leftAnim) && (diagonal == false)) //ANIMACIÓ LEFT
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;

				if (shooting == false) {
					gun_l.Reset();
					currentTopAnimation = &gun_l;
				}
			}
		}

		if (((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) || pad.left_x > 0.0f || pad.right) && position.x <= 455) //RIGHT
		{
			position.x += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) || pad.left_y > 0.0f || pad.down) { //DOWN RIGHT
				diagonal = true;
				if (currentAnimation != &diagonalPAnim)
				{
					diagonalPAnim.Reset();
					currentAnimation = &diagonalPAnim;

					if (shooting == false) {
						topDRAnim.Reset();
						currentTopAnimation = &topDRAnim;
					}
				}
			}

			if (currentAnimation != &rigthAnim && (diagonal == false))
			{
				rigthAnim.Reset();
				currentAnimation = &rigthAnim;

				if (shooting == false) {
					gun_r.Reset();
					currentTopAnimation = &gun_r;
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
				if (currentAnimation != &diagonalSRAnim)
				{
					diagonalSRAnim.Reset();
					currentAnimation = &diagonalSRAnim;

					if (shooting == false) {
						topDLAnim.Reset();
						currentTopAnimation = &topDLAnim;
					}
				}
			}

			if (currentAnimation != &downAnim && (diagonal == false))
			{
				downAnim.Reset();
				currentAnimation = &downAnim;

				if (shooting == false) {
					gun_down.Reset();
					currentTopAnimation = &gun_down;
				}
			}
		}

		if (((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) || pad.left_y < 0.0f || pad.up) && position.y >= 60) //UP
		{
			position.y -= speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) || pad.left_x > 0.0f || pad.right) { // UP RIGHT
				diagonal = true;
				if (currentAnimation != &diagonalSAnim)
				{
					diagonalSAnim.Reset();
					currentAnimation = &diagonalSAnim;

					if (shooting == false) {
						topURAnim.Reset();
						currentTopAnimation = &topURAnim;
					}
				}
			}

			if (currentAnimation != &upAnim && (diagonal == false))
			{
				upAnim.Reset();
				currentAnimation = &upAnim;

				if (shooting == false) {
					gun_up.Reset();
					currentTopAnimation = &gun_up;
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
				if (currentAnimation != &diagonalPRAnim)
				{
					diagonalPRAnim.Reset();
					currentAnimation = &diagonalPRAnim;

					if (shooting == false) {
						topULAnim.Reset();
						currentTopAnimation = &topULAnim;
					}
				}
			}

			if ((currentAnimation != &leftAnim) && (diagonal == false)) //ANIMACIÓ LEFT
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;

				if (shooting == false) {
					gun_l.Reset();
					currentTopAnimation = &gun_l;
				}
			}
		}

		if ((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) || pad.left_x > 0.0f) //RIGHT
		{
			position.x += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) || pad.left_y > 0.0f) { //DOWN RIGHT
				diagonal = true;
				if (currentAnimation != &diagonalPAnim)
				{
					diagonalPAnim.Reset();
					currentAnimation = &diagonalPAnim;

					if (shooting == false) {
						topDRAnim.Reset();
						currentTopAnimation = &topDRAnim;
					}
				}
			}

			if (currentAnimation != &rigthAnim && (diagonal == false))
			{
				rigthAnim.Reset();
				currentAnimation = &rigthAnim;

				if (shooting == false) {
					gun_r.Reset();
					currentTopAnimation = &gun_r;
				}
			}
		}

		if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) || pad.left_y > 0.0f) //DOWN
		{
			position.y += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) || pad.left_x < 0.0f) { //DOWN LEFT
				diagonal = true;
				if (currentAnimation != &diagonalSRAnim)
				{
					diagonalSRAnim.Reset();
					currentAnimation = &diagonalSRAnim;

					if (shooting == false) {
						topDLAnim.Reset();
						currentTopAnimation = &topDLAnim;
					}
				}
			}

			if (currentAnimation != &downAnim && (diagonal == false))
			{
				downAnim.Reset();
				currentAnimation = &downAnim;

				if (shooting == false) {
					gun_down.Reset();
					currentTopAnimation = &gun_down;
				}
			}
		}

		if ((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) || pad.left_y < 0.0f) //UP
		{
			position.y -= speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) || pad.left_x > 0.0f) { // UP RIGHT
				diagonal = true;
				if (currentAnimation != &diagonalSAnim)
				{
					diagonalSAnim.Reset();
					currentAnimation = &diagonalSAnim;

					if (shooting == false) {
						topURAnim.Reset();
						currentTopAnimation = &topURAnim;
					}
				}
			}

			if (currentAnimation != &upAnim && (diagonal == false))
			{
				upAnim.Reset();
				currentAnimation = &upAnim;

				if (shooting == false) {
					gun_up.Reset();
					currentTopAnimation = &gun_up;
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

		currentTopAnimation = &shootURAnim;

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
			}
		}
	}
	else if ((App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) || (pad.right_x < 0.0f && pad.right_y < 0.0f)) //Esq, amunt
	{

		currentTopAnimation = &shootULAnim;

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
			}
		}
	}
	else if ((App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) || (pad.right_x < 0.0f && pad.right_y > 0.0f)) //Esq, avall
	{

		currentTopAnimation = &shootDLAnim;

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
			}
		}
	}
	else if ((App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) || (pad.right_x > 0.0f && pad.right_y > 0.0f)) //drt, avall
	{

		currentTopAnimation = &shootDRAnim;

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
			}
		}
	}
	//RECTES
	else if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT || pad.right_y < 0.0f || pad.y) //amunt
	{
		currentTopAnimation = &gun_up_shoot;

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
				cont = 0;
			}
		}

	}
	else if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || pad.right_x < 0.0f || pad.x) //Esq
	{

		currentTopAnimation = &gun_l_shoot;

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
			}
		}
	}
	else if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT || pad.right_y > 0.0f || pad.a) // avall
	{

		currentTopAnimation = &gun_down_shoot;

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
			}
		}
	}
	else if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || pad.right_x > 0.0f || pad.b) //drt
	{

		currentTopAnimation = &gun_r_shoot;

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
			}
		}
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {

		currentAnimation = &idleUAnim;
		if (!shooting) {
			currentTopAnimation = &gun_down;
		}
	}

	// L6: DONE 4: Update collider position to player position
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();
	currentTopAnimation->Update();

	//Gestió Array de la font
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
	//	App->particles->AddParticle(App->particles->Gold, 100, 140, 6, Collider::Type::object_gold);
	//	App->particles->AddParticle(App->particles->Silver, 235, 140, 6, Collider::Type::object_silver);
	//	App->particles->AddParticle(App->particles->Cash, 370, 140, 6, Collider::Type::object_money);
	//	App->particles->AddParticle(App->particles->SilverGold, 100, 190, 6, Collider::Type::object_silver_gold);
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



	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) { //necessita col·lidir amb un enemic al final per morir
		vides--;
	}

	//if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN && App->SceneLevel->lvl1)
	//	App->fade->FadeToBlack((Module*)App->SceneLevel, (Module*)App->sceneWin, 20);

	//if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN && App->sceneLevel2->lvl2)
	//	App->fade->FadeToBlack((Module*)App->sceneLevel2, (Module*)App->sceneWin, 20);
	/*if (pad.enabled)
	{
		if (pad.left_x == 0.0f && pad.left_y == 0.0f) currentAnimation = &idleAnim;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) currentAnimation = &idleAnim;*/

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	//TOTA L'IMPRESSIÓ D'SPRITES DE NOMBRES I IMMUNITAT S'HA PORTAT AL ModuleEnemies, ara ja estan en ordre.

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x + 2, position.y + 17, &rect, 1.5f);

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