#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;
	bool CleanUp() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;
	int cont = 25;
	bool bandera = true;

	int cont_Tripel = 0;
	bool bandera_trip = false;
	//bool bandera_GodMode = false;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* textureDoorTop = nullptr;
	SDL_Texture* textureUI = nullptr;
	SDL_Texture* textureFont = nullptr;
	SDL_Texture* textureMort = nullptr;
	SDL_Texture* texturePickups = nullptr;

	//SDL_Texture* toptexture = nullptr;

	int vides = 5;
	int contadorVides = 0;

	int money = 0;
	int score = 0;
	int scoreCopia = 0;

	int scoreN[8] = { 0 }; //arrai de digits score

	int topDoor = 0;

	bool bandera_GodMode = false;

	bool ImprimirPortes = true;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;
	Animation* currentTopAnimation = nullptr;

	// A set of animations
	Animation idleUAnim;
	Animation idleURAnim;
	Animation idleULAnim;
	Animation idleDAnim;
	Animation idleLRAnim;
	Animation upAnim;
	Animation downAnim;
	Animation leftAnim;
	Animation rigthAnim;
	Animation diagonalSAnim;
	Animation diagonalSRAnim;
	Animation diagonalPAnim;
	Animation diagonalPRAnim;

	Animation legs_down_idle;
	Animation upAnim_idle;
	Animation legs_l_idle;
	Animation legs_r_idle;
	Animation legs_up;
	Animation legs_down;
	Animation legs_l;
	Animation legs_r;

	

	bool diagonal = false;
	int MovKeyPressed = 0;

	Animation topDownAnim; //Idle i Down
	Animation topDRAnim;
	Animation topDLAnim;
	Animation topLeftAnim;
	Animation topRightAnim;
	Animation topURAnim;
	Animation topULAnim;
	Animation topUpAnim;

	Animation gun_down;
	Animation gun_up;
	Animation gun_l;
	Animation gun_r;
	Animation gun_up_shoot;
	Animation gun_down_shoot;
	Animation gun_l_shoot;
	Animation gun_r_shoot;

	bool shooting = false;

	Animation shootDownAnim;
	Animation shootDRAnim;
	Animation shootDLAnim;
	Animation shootLeftAnim;
	Animation shootRightAnim;
	Animation shootURAnim;
	Animation shootULAnim;
	Animation shootUpAnim;

	Animation ShootGun_down;
	Animation ShootGun_up;
	Animation ShootGun_l;
	Animation ShootGun_r;
	Animation ShootGun_up_shoot;
	Animation ShootGun_down_shoot;
	Animation ShootGun_l_shoot;
	Animation ShootGun_r_shoot;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint gunFx = 0;
	uint explosionFx = 0;

};

#endif // __MODULEPLAYER_H__
