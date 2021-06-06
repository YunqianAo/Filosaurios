#pragma once
#ifndef __ENEMY_PINK_H__
#define __ENEMY_PINK_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Pink : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Pink(int x, int y);
	SDL_Texture* pinkTexture = nullptr;
	// The enemy is going to perform a sinusoidal movement
	void Update() override;

	// Delay entre els moviments de l'enemic
	int movementDelay = 0;

private:

	int spawntimer = 0;

	int randomMove = 0;

	int movedelay = 0;

	// The enemy animation
	Animation pink_idle;
	Animation pink_up;
	Animation pink_down;
	Animation pink_l;
	Animation pink_r;

	int movementDirections = 0;
};

#endif // __ENEMY_PINK_H__