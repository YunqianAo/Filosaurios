#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer_Gun.h"
#include "ModuleAudio.h"
#include "SceneIntroUPC.h"
#include "SceneIntroLogo.h"
#include "SceneIntro.h"
#include "ModuleEnemies.h"
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

	modules[4] = sceneIntroUPC = new SceneIntroUPC(true);
	modules[5] = sceneIntroLogo = new SceneIntroLogo(true);
	modules[6] = sceneIntro = new SceneIntro(true);
	modules[7] = sceneLevel = new SceneLevel(false);
	modules[8] = sceneLose = new SceneLose(false);
	modules[9] = sceneWin = new SceneWin(false);
	modules[10] = player = new ModulePlayer(false);
	modules[11] = particles = new ModuleParticles(true);
	modules[12] =	enemies = new ModuleEnemies(true);

	modules[13] = collisions = new ModuleCollisions(true);
	modules[14] = fade = new ModuleFadeToBlack(true);
	modules[15] = fonts = new ModuleFonts(true);
	modules[16] = render = new ModuleRender(true);
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
