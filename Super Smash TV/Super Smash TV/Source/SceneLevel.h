#ifndef __SCENE_LEVEL_H__
#define __SCENE_LEVEL_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel : public Module
{
public:
	//Constructor
	SceneLevel(bool startEnabled);

	//Destructor
	~SceneLevel();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	bool Level_1;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;

	int mapaActual = 2;
	int randomcont = 50;
	int num = 0;
	int sceneTimer = 0; //3601 si vols veure el final directe, 0 per default.
	int randomEnemySpawn = 0;
	short portesSpawn[4][9][2];
	int i = 0;
	int exitTimer = 0;
	int levelcont = 0;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[150] = { "\0" };

};

#endif