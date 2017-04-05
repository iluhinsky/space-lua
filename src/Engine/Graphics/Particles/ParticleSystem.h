#pragma once

#include "Particle.h"


class ParticleSystem
{
public:
	friend class ParticleSystemFactory;

	ParticleSystem(int numberOfParticles, float lifeTime, float initialSpeed);
	~ParticleSystem();

	void Draw(Camera* camera);

private:

	float		scale_;
	float		lifeTime_;
	float		initialSpeed_;
	int			numberOfParticles_;

	Model*      model_;
	GLuint      texture_;
	ShaderProg* shaderProg_;
	
	Particle*	particles_;

	void SetUniforms	(Camera* camera, glm::vec4& worldPos);
	void SetTranslation	(Pipeline* p, Camera* camera, glm::vec4& worldPos);
};

