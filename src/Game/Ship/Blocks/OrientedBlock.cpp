#include "OrientedBlock.h"



OrientedBlock::OrientedBlock()
{
}


OrientedBlock::~OrientedBlock()
{
}


bool OrientedBlock::isDirectionAllowed(glm::vec3 direction)
{
	return glm::dot(orientation_, direction) > 0 ? true : false;
}