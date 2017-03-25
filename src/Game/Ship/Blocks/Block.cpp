#include "Block.h"



Block::Block()
{
}


Block::~Block()
{
}


void Block::Draw(Camera* camera, btTransform& transform_) const
{
	//! TODO: Correct drawing

	btVector3 globalCoord = transform_.getOrigin();

	float x = globalCoord.getX();
	float y = globalCoord.getY();
	float z = globalCoord.getZ();;

	glm::vec3 newCoord = glm::vec3(x, y, z);

	graphicsAsset_->Draw(camera, newCoord + relatedCoords_);
}

float Block::GetMass()
{
	return mass_;
}

glm::vec3 Block::GetRelatedCoords()
{
	return relatedCoords_;
}