#pragma once
#include "../../Include.h"

#include "GraphicsObjectManager.h"
#include "Particles/ParticleSystem.h"
#include "Skybox/Skybox.h"
#include "Particles/ParticleSystemFactory.h"

class GraphicsWorld
{
public:
	GraphicsWorld();
	~GraphicsWorld();
	void Init();

	ParticleSystem* GetFireParticleSystem(glm::vec3 position, glm::vec3 velocity);
	ParticleSystem* GetExplosionParticleSystem(glm::vec3 position);

	std::vector<ParticleSystem*> GetParticleSystem();
	GraphicsObjectManager* GetManager();

	void Draw(Camera* camera);

private:
	std::vector<ParticleSystem*>	particleSystem_;
	GraphicsObjectManager*			manager_;

	Skybox*					skybox_;
	ParticleSystemFactory			particleSystemFactory_;
};

