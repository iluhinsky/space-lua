#include "Particle.h"



Particle::Particle()
{
}


Particle::~Particle()
{
}

glm::vec3 Particle::GetPosition()
{
	return position_;
}

void Particle::Update(float dt, int flowPerSecond_, int numberOfParticles_, bool isRepeat)
{
	if (estimatedTime_ < 0 && isRepeat == false)
	{
		Disable();
		return;
	}

	if (!isEnabled)
	{
		Enable(dt, flowPerSecond_, numberOfParticles_);
		return;
	}

	if (estimatedTime_ < 0 && isRepeat)
	{
		estimatedTime_ = lifeTime_;
		position_.x = 0;
		position_.y = 0;
		position_.z = 0;
	}

	position_.x += velocity_.x * dt;
	position_.y += velocity_.y * dt;
	position_.z += velocity_.z * dt;

	estimatedTime_ -= dt;
}

glm::vec3 Particle::GenRandVector()
{
	int A = rand() + 1;
	float coneCoef = 3;

	glm::vec3 addedVelocity = {}; 
	addedVelocity.x = coneCoef * (rand() % A) / float(A);
	if (rand() % 2) { addedVelocity.x *= -1.0f; }
	addedVelocity.y = coneCoef * (rand() % A) / float(A);
	if (rand() % 2) { addedVelocity.y *= -1.0f; }
	addedVelocity.z = coneCoef * (rand() % A) / float(A);
	if (rand() % 2) { addedVelocity.z *= -1.0f; } 

	return addedVelocity;
}

void Particle::SetVelocity(glm::vec3 initialSpeed)
{
	velocity_ = initialSpeed + GenRandVector();
}

void Particle::SetLifeTime(float lifeTime)
{
	lifeTime_		= lifeTime;
	estimatedTime_	= lifeTime;
}

