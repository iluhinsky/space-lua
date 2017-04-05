#pragma once
#include "..\..\Include.h"

#include "GraphicsObjectManager.h"
#include "Particles\ParticleSystem.h"

class GraphicsWorld
{
public:
	GraphicsWorld();
	~GraphicsWorld();
	void Init();

	ParticleSystem* GetParticleSystem();
	GraphicsObjectManager* GetManager();

private:
	ParticleSystem*			particleSystem_;
	GraphicsObjectManager*	manager_;
};

