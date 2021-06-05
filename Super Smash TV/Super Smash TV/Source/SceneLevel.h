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

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[150] = { "\0" };

};

#endif