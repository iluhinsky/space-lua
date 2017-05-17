#include "BlockWeapon.h"

#include "../../../Application/Application.h"


BlockWeapon::BlockWeapon()
{
}

BlockWeapon::~BlockWeapon()
{
}

void BlockWeapon::ReduceTime(int dt)
{
	estimatedTime_ -= dt;

	if (estimatedTime_ < 0)
		estimatedTime_ = -1;
}

Block* BlockWeapon::Clone() const
{
	return new BlockWeapon(*this);
}

void BlockWeapon::SetCommand(BlockWeaponCommand command)
{
	switch (command)
	{
	case ShootCommand:
		(this->Command_) = (void (Block::*)()) &BlockWeapon::Shoot;
		break;
	default:
		break;
	}
}

void BlockWeapon::Shoot()
{
	if (estimatedTime_ > 0)
		return;

	if (!IsDirectionAllowed(currDirection_))
		return;

	WORLD->CreateBullet(currDirection_, currGlobalCoords_ + currDirection_ * 2.0f);

	estimatedTime_ = coolDownTime_;
}
