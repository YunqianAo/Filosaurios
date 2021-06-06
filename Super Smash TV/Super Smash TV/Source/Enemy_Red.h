#pragma once
#ifndef __ENEMY_RED_H__
#define __ENEMY_RED_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Red : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	SDL_Texture* redTexture = nullptr;
	Enemy_Red(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

	// Delay entre els moviments de l'enemic
	int movementDelay = 0;

private:

	int spawntimer = 0;

	int randomMove = 0;

	int movedelay = 0;

	// The enemy animation
	Animation red_up;
	Animation red_down;
	Animation red_l;
	Animation red_r;

	int movementDirections = 0;

};

#endif // __ENEMY_RED_H__