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

void Block::hit(int damage)
{
	hits_ -= damage;
}

bool Block::isExist()
{
	return (hits_ > 0);
}

bool Block::isLinked()
{
	return isLinked_;
}


void Block::Draw(Camera* camera) const
{
	graphicsAsset_->Draw(camera, currGlobalCoords_, currRotation_);
}

float Block::GetMass()
{
	return mass_;
}

glm::vec3 Block::GetRelatedCoords()
{
	return relatedCoords_;
}

glm::vec3 Block::GetGlobalCoords()
{
	return currGlobalCoords_;
}

void Block::SetShip(Ship* ship)
{
	ship_ = ship;
}

const std::string& Block::GetName()
{
	return name_;
}

void Block::UpdateAfterPhysicsStep(glm::vec3& shipGlobalCoords, glm::mat3& currRotation)
{
	currGlobalCoords_ = shipGlobalCoords + currRotation * relatedCoords_;
	currRotation_     = currRotation;
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