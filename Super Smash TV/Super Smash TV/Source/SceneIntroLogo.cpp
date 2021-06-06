#include "SceneIntroLogo.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntroLogo::SceneIntroLogo(bool startEnabled) : Module(startEnabled)
{

}

SceneIntroLogo::~SceneIntroLogo()
{

}

// Load assets 
bool SceneIntroLogo::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Resources/Sprites/Intro/IntroLogo.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneIntroLogo::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneIntroLogo::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}