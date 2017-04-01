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

private:
	ParticleSystem* particleSystem_;
};

