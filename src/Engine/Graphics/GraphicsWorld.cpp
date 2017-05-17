#include "GraphicsWorld.h"

GraphicsWorld::GraphicsWorld()
{
	manager_ = new GraphicsObjectManager;
	particleSystemFactory_ = ParticleSystemFactory();
}


GraphicsWorld::~GraphicsWorld()
{
	for (auto system : particleSystem_)
		delete system;

	delete manager_;

	printf("ENDDDDDD\n\n\n");
}

void GraphicsWorld::Init()
{
	particleSystem_.push_back(GetFireParticleSystem(glm::vec3(20, -40, 0), glm::vec3(1, 0, 0)));
}

std::vector<ParticleSystem*> GraphicsWorld::GetParticleSystem()
{
	return particleSystem_;
}

GraphicsObjectManager* GraphicsWorld::GetManager()
{
	return manager_;
}

ParticleSystem* GraphicsWorld::GetFireParticleSystem(glm::vec3 position, glm::vec3 velocity)
{
	ParticleSystemInfo assets = {};

	assets.initialSpeed_ = 10.0f*glm::normalize(velocity);
	assets.color_ = glm::vec3{ 1, 0.3f, 0 };
	assets.lifeTime_ = 1.0f;
	assets.scale_ = 0.5f;
	assets.numberOfParticles_ = 400;
	assets.flowPerSecond_ = 400;
	assets.isRepeat_ = true;
	assets.modelName_ = "particle.3ds";
	assets.textureName_ = "face.png";
	assets.shaderNames_ = ShaderNames{ "particle_vertex.glsl", "particle_fragment.glsl", "" };

	return particleSystemFactory_.CreateParticleSystem(position, assets);
}

ParticleSystem* GraphicsWorld::GetExplosionParticleSystem(glm::vec3 position)
{
	ParticleSystemInfo assets = {};

	assets.initialSpeed_ = glm::vec3{ 0, 0, 0 };
	assets.color_ = glm::vec3{ 1, 1, 1 };
	assets.lifeTime_ = 1.0f;
	assets.scale_ = 0.6f;
	assets.numberOfParticles_ = 500;
	assets.flowPerSecond_ = 100000;
	assets.isRepeat_ = false;
	assets.modelName_ = "particle.3ds";
	assets.textureName_ = "face.png";
	assets.shaderNames_ = ShaderNames{ "particle_vertex.glsl", "particle_fragment.glsl", "" };

	ParticleSystem* explosion = particleSystemFactory_.CreateParticleSystem(position, assets);
	particleSystem_.push_back(explosion);

	return explosion;
}