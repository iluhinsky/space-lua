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


void Block::Draw(Camera* camera, glm::vec4& globalCoord, glm::mat4& rotation) const
{
	graphicsAsset_->Draw(camera, globalCoord + rotation * glm::vec4(relatedCoords_, 1.0f), rotation);
}

float Block::GetMass()
{
	return mass_;
}

glm::vec3 Block::GetRelatedCoords()
{
	return relatedCoords_;
}