#pragma once
#ifndef __ENEMY_GREEN_H__
#define __ENEMY_GREEN_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Green : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Green(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:

	Path path;



	// The enemy animation
	Animation green_up;
	Animation green_down;
	Animation green_l;
	Animation green_r;

};

#endif // __ENEMY_GREEN_H__