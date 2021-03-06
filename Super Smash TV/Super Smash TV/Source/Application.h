#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 18

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class SceneIntroUPC;
class SceneIntroLogo;
class SceneIntro;
class ModuleFonts;
class ModulePlayer;
class SceneLevel; 
class SceneLevel2;
class SceneLose;
class SceneWin;
class ModuleParticles;
class ModuleCollisions;
class ModuleFadeToBlack;
class ModuleRender;
class ModuleEnemies;
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
	ModuleAudio* audio = nullptr;
	ModulePlayer* player = nullptr;
	SceneIntroUPC* sceneIntroUPC = nullptr;
	SceneIntroLogo* sceneIntroLogo = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneLevel* sceneLevel = nullptr;
	SceneLevel2* sceneLevel2 = nullptr;
	SceneLose* sceneLose = nullptr;
	SceneWin* sceneWin = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleFonts* fonts = nullptr;	
	ModuleFadeToBlack* fade = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__