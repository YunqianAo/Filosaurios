#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 9

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModulePlayer_Leg;
class ModulePlayer_Gun;
class ModuleScene;
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

	ModulePlayer_Leg* player_leg = nullptr;
	ModulePlayer_Gun* player_gun = nullptr;
	ModuleScene* scene = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__