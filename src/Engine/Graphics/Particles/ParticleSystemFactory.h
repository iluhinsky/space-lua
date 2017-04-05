#pragma once
#include "ParticleSystem.h"

struct ParticleSystemInfo
{
	std::string modelName_;
	std::string textureName_;

	ShaderNames shaderNames_;

	int			numberOfParticles_; 
	int			flowPerSecond_;
	float		lifeTime_; 
	glm::vec3	initialSpeed_;
};

class ParticleSystemFactory
{
public:
	ParticleSystemFactory();
	~ParticleSystemFactory();

	ParticleSystem* CreateParticleSystem(glm::vec3 position, ParticleSystemInfo assets);

private:

	//ShaderProgManager shaderManager_;
	TextureManager	  textureManager_;
	ModelManager	  modelManager_;
};

