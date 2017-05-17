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

	return glm::dot(rotation * orientation_, direction) > 0 ? true : false;
}

void OrientedBlock::SetDirection(glm::vec3 direction)
{
	direction = glm::normalize(direction);

	currDirection_ = direction;
}

void OrientedBlock::SetDirectionFromAngles(int theta, int psi)
{
	btTransform shipTransform = ship_->GetTransform();

	glm::mat3 rotation = toGLM_M3x3(shipTransform.getBasis());
	glm::mat3 rotation_inv = glm::inverse(rotation);

	currDirection_ = rotation_inv * orientation_;
}