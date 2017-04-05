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

void Particle::Update(float dt)
{
	if (!isEnabled)
	{
		return;
	}
	
	position_.x += velocity_.x * dt;
	position_.y += velocity_.y * dt;
	position_.z += velocity_.z * dt;

	estimatedTime_ -= dt;

	if (estimatedTime_ < 0)
	{
		estimatedTime_ = lifeTime_;
		position_.x = 0;
		position_.y = 0;
		position_.z = 0;
	}

}

glm::vec3 Particle::GenRandVector()
{
	int A = rand();

	return glm::vec3{ (rand() % A) / float(A), (rand() % A) / float(A), (rand() % A) / float(A)};
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

