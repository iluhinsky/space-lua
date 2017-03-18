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


void Block::Draw(Camera* camera, glm::vec3 coords_) const
{
	graphicsAsset_->Draw(camera, coords_ + relatedCoords_);
}