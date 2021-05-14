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
	Enemy_Red(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:

	Path path;



	// The enemy animation
	Animation red_up;
	Animation red_down;
	Animation red_l;
	Animation red_r;

};

#endif // __ENEMY_RED_H__