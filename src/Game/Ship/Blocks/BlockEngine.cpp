#include "BlockEngine.h"

#include "../../../Application/Application.h"


BlockEngine::BlockEngine()
{
}


BlockEngine::~BlockEngine()
{
}

Block* BlockEngine::Clone() const
{
	return new BlockEngine(*this);
}

void BlockEngine::SetCommand(BlockEngineCommand command)
{
	switch (command)
	{
	case GasCommand:
		(this->Command_) = (void (Block::*)()) &BlockEngine::Gas;
		break;
	default:
		break;
	}
}

void BlockEngine::ReduceTime(int dt)
{
	estimatedTime_ -= dt;

	if (estimatedTime_ < 0)
		estimatedTime_ = -1;
}

void BlockEngine::SetPower(int power)
{
	assert(power >= 0 && power <= 10);

	power_ = power;
}

void BlockEngine::Gas()
{
	if (estimatedTime_ > 0)
		return;

	if (!IsDirectionAllowed(currDirection_))
		return;

	btVector3 currDirection = btVector3(
		currDirection_.x,
		currDirection_.y,
		currDirection_.z);

	btVector3 currGlobalCoords = btVector3(
		currGlobalCoords_.x,
		currGlobalCoords_.y,
		currGlobalCoords_.z);

	ship_->ApplyForce(currDirection * power_, currGlobalCoords);
}