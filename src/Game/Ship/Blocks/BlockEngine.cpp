#include "BlockEngine.h"

#include "../../../Application/Application.h"

extern const int engineMaxPower = 10;


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
	assert(0 <= power && power <= engineMaxPower);

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

	glm::vec3 relCoords = currRotation_ * relatedCoords_;

	btVector3 bt_relCoords = btVector3(
		relCoords.x,
		relCoords.y,
		relCoords.z);

	ship_->ApplyForce( - currDirection * power_, bt_relCoords);
}