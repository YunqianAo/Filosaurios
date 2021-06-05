#include "SceneIntroUPC.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntroUPC::SceneIntroUPC(bool startEnabled) : Module(startEnabled)
{

}

SceneIntroUPC::~SceneIntroUPC()
{

}

// Load assets
bool SceneIntroUPC::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Resources/Sprites/Intro/Intro_0.png");
	App->audio->PlayMusic("Resources/Audio/Music/Title_Screen.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneIntroUPC::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntroLogo, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneIntroUPC::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}