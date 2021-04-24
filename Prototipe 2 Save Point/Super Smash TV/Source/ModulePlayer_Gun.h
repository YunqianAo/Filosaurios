#ifndef __MODULE_PLAYER_GUN__
#define __MODULE_PLAYER_GUN__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer_Gun : public Module
{
public:
	// Constructor
	ModulePlayer_Gun();

	// Destructor
	~ModulePlayer_Gun();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

public:

	//Posision of the body
	iPoint position;


	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation gun_idle;
	Animation gun_up;
	Animation gun_l;
	Animation gun_r;
	Animation gun_up_shoot;
	Animation gun_down_shoot;
	Animation gun_l_shoot;
	Animation gun_r_shoot;
};

#endif //!__MODULE_PLAYER_GUN__#pragma once

