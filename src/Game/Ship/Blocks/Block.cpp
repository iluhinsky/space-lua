#include "Block.h"



Block::Block()
{
}


Block::~Block()
{
}

BlockType Block::GetType()
{
	return blockType_;
}


void Block::Draw(Camera* camera, btTransform& transform_) const
{
	//! TODO: Simplify drawing
	glm::vec3 globalCoord = toGLM(transform_.getOrigin());
	glm::mat4 rotation = toGLM(transform_.getBasis());

	glm::mat4 rotation_inv = glm::inverse(rotation);

	graphicsAsset_->Draw(camera, glm::vec4(globalCoord, 1.0f) + 
		rotation_inv * glm::vec4(relatedCoords_, 1.0f), rotation_inv);
}

float Block::GetMass()
{
	return mass_;
}

glm::vec3 Block::GetRelatedCoords()
{
	return relatedCoords_;
}