#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 9

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
/*
class ModuleAudio;
class SceneIntro;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleFonts;
*/
class ModulePlayer_Leg;
class ModulePlayer_Gun;
class SceneLevel;
class ModuleParticles;
class ModuleCollisions;
class ModuleRender;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;

	/*
	ModuleAudio* audio = nullptr;
	SceneIntro* sceneIntro = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;	
	*/

	ModulePlayer_Leg* player_leg = nullptr;
	ModulePlayer_Gun* player_gun = nullptr;
	SceneLevel* scene_level = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__