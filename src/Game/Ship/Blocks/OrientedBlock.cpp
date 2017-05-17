#include "OrientedBlock.h"

#include "../Ship.h"

OrientedBlock::OrientedBlock()
{
}


OrientedBlock::~OrientedBlock()
{
}


bool OrientedBlock::IsDirectionAllowed(glm::vec3 direction)
{
	btTransform shipTransform = ship_->GetTransform();

	glm::mat3 rotation     = toGLM_M3x3(shipTransform.getBasis());
	glm::mat3 rotation_inv = glm::inverse(rotation);

	return glm::dot(rotation * target_, direction) > 0 ? true : false;
}

void OrientedBlock::SetDirection(glm::vec3 direction)
{
	currDirection_ = direction;
}

void OrientedBlock::SetDirectionFromAngles(int theta, int psi)
{
	if (theta <= 0 || 90 <= theta)
		theta = 0;

	if (psi <= 0 || psi >= 180)
		psi = 0;

	glm::vec3 firstVector = glm::vec3(glm::rotate(glm::mat4(1.0f), (float)ToRadian(theta), up_) * 
		glm::vec4 (target_, 1.0f));

	glm::vec3 finalVector = glm::vec3(glm::rotate(glm::mat4(1.0f), (float)ToRadian(psi), target_) *
		glm::vec4(firstVector, 1.0f));

	btTransform shipTransform = ship_->GetTransform();

	glm::mat3 rotation = toGLM_M3x3(shipTransform.getBasis());
	glm::mat3 rotation_inv = glm::inverse(rotation);

	currDirection_ = rotation_inv * finalVector;
}