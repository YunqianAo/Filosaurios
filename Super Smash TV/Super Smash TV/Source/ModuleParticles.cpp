#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Sprites/effects/particles.png");

	// Bullet Default
	bullet_r.anim.PushBack({ 32, 82, 8, 3 });
	bullet_r.speed = iPoint(2, 0);
	bullet_r.lifetime = 180;

	bullet_l.anim.PushBack({ 0, 82, 8, 3 });
	bullet_l.speed = iPoint(-2, 0);
	bullet_l.lifetime = 180;

	bullet_up.anim.PushBack({ 18, 80, 3, 8 });
	bullet_up.speed = iPoint(0, -2);
	bullet_up.lifetime = 180;

	bullet_down.anim.PushBack({ 51, 80, 3, 8 });
	bullet_down.speed = iPoint(0, 2);
	bullet_down.lifetime = 180;

	// shotgun bullet
	shotgun_1.anim.PushBack({ 9, 113, 5, 5 });
	shotgun_1.speed = iPoint(0, -2);
	shotgun_1.lifetime = 180;

	shotgun_2.anim.PushBack({ 9, 113, 5, 5 });
	shotgun_2.speed = iPoint(2, -2);
	shotgun_2.lifetime = 180;

	shotgun_3.anim.PushBack({ 9, 113, 5, 5 });
	shotgun_3.speed = iPoint(2, 0);
	shotgun_3.lifetime = 180;

	shotgun_4.anim.PushBack({ 9, 113, 5, 5 });
	shotgun_4.speed = iPoint(2, 2);
	shotgun_4.lifetime = 180;

	shotgun_5.anim.PushBack({ 9, 113, 5, 5 });
	shotgun_5.speed = iPoint(0, 2);
	shotgun_5.lifetime = 180;

	shotgun_6.anim.PushBack({ 9, 113, 5, 5 });
	shotgun_6.speed = iPoint(-2, 2);
	shotgun_6.lifetime = 180;

	shotgun_7.anim.PushBack({ 9, 113, 5, 5 });
	shotgun_7.speed = iPoint(-2, 0);
	shotgun_7.lifetime = 180;

	shotgun_8.anim.PushBack({ 9, 113, 5, 5 });
	shotgun_8.speed = iPoint(-2, -2);
	shotgun_8.lifetime = 180;


	

	inv.anim.PushBack({ 0, 49, 32, 30 });
	inv.lifetime = 180;


	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}



update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}


void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}