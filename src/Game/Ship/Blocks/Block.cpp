#include "Block.h"

#include "..\..\..\Application\Application.h"

Block::Block()
{
}


Block::~Block()
{
	std::cout << "Block " << blockType_ << " was punished!" << std::endl;

	for (auto link : links_)
		if (link.second != nullptr)                        // Cost ill
			link.second->Unlink(oppositeTo(link.first));

	//GRAPHICSWORLD->GetExplosionParticleSystem(currGlobalCoords_);
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

void Block::Draw(Camera* camera, glm::vec3& color) const
{
	graphicsAsset_->Draw(camera, currGlobalCoords_, currRotation_, color);
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