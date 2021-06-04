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

	// The enemy is going to perform a sinusoidal movement
	bool Start() override;
	void Update() override;

private:

	Path path;



	// The enemy animation
	Animation pink_up;
	Animation pink_down;
	Animation pink_l;
	Animation pink_r;

	Collider* colliderPink = nullptr;
};

#endif // __ENEMY_PINK_H__