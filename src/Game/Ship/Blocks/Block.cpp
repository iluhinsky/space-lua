#include "Block.h"


Block::Block()
{
}


Block::~Block()
{
	for (auto link : links_)
		link.second->Unlink(oppositeTo(link.first));
}

BlockType Block::GetType()
{
	return blockType_;
}

void Block::hit(int damage)
{
	hits_ -= damage;
}

bool Block::isExist()
{
	return (hits_ > 0);
}

bool Block::isLinkedtoMain()
{
	return isLinked_;
}

void Block::LinktoMain()
{
	isLinked_ = true;
}

void Block::UnlinkfromMain()
{
	isLinked_ = false;
}

void Block::Link(Direction direction, Block* block)
{
	links_[direction] = block;
}

void Block::Unlink(Direction direction)
{
	links_.erase(direction);
}

Block* Block::GetBlockBy(Direction direction)
{
	return links_[direction];
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

void Block::SetShip(Ship* ship)
{
	ship_ = ship;
}

void Block::ExecuteCommand()
{
	(this->*Command_)();
}

void Block::SetStandartCommand()
{
	(this->Command_) = &Block:: DoNothing;
}

void Block::DoNothing()
{
	//Do nothing
}