#include "GraphicsWorld.h"
#include "Particles/ParticleSystemFactory.h"


GraphicsWorld::GraphicsWorld()
{
	manager_ = new GraphicsObjectManager;
}


GraphicsWorld::~GraphicsWorld()
{
	delete particleSystem_;
	delete manager_;

	printf("ENDDDDDD\n\n\n");
}

void GraphicsWorld::Init()
{
	ParticleSystemInfo assets = {};

	//For first design

	assets.initialSpeed_ = glm::vec3{3, 3, 0};
	assets.lifeTime_			= 20.0f;
	assets.numberOfParticles_	= 100000;
	assets.flowPerSecond_		= 10000;
	
	assets.modelName_	= "particle.3ds";
	assets.textureName_ = "face.png";
	assets.shaderNames_ = ShaderNames{"particle_vertex.glsl", "particle_fragment.glsl", ""};
	
	glm::vec3 position = glm::vec3{1, 1, -3};

	ParticleSystemFactory factory = ParticleSystemFactory();
	particleSystem_ = factory.CreateParticleSystem(position, assets);
}

ParticleSystem* GraphicsWorld::GetParticleSystem()
{
	return particleSystem_;
}

GraphicsObjectManager* GraphicsWorld::GetManager()
{
	return manager_;
}