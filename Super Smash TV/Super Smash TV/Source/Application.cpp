#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer_Legs.h"
#include "ModulePlayer_Gun.h"
#include "ModuleAudio.h"
#include "SceneIntro.h"
//#include "ModuleEnemies.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include "SceneWin.h"
#include "SceneLevel.h"
#include "SceneLose.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);

	modules[4] = sceneIntro = new SceneIntro(true);
	modules[5] = sceneLevel = new SceneLevel(false);
	modules[6] = sceneLose = new SceneLose(false);
	modules[7] = sceneWin = new SceneWin(false);
	modules[8] = player_leg = new ModulePlayer_Leg(false);
	modules[9] = player_gun = new ModulePlayer_Gun(false);
	modules[10] = particles = new ModuleParticles(true);
	//		modules[8] =	enemies =		new ModuleEnemies(false);

	modules[11] = collisions = new ModuleCollisions(true);
	modules[12] = fade = new ModuleFadeToBlack(true);
	modules[13] = fonts = new ModuleFonts(true);
	modules[14] = render = new ModuleRender(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	//By now we will consider that all modules are always active
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : update_status::UPDATE_CONTINUE;
	
	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : update_status::UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
