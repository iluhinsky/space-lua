#include "BlockWeapon.h"

#include "..\..\..\Application\Application.h"

BlockWeapon::BlockWeapon()
{
}

BlockWeapon::BlockWeapon(const BlockWeapon& block)
{
	graphicsAsset_ = block.graphicsAsset_;

	blockType_ = block.blockType_;

	hits_ = block.hits_;
	mass_ = block.mass_;
}

BlockWeapon::~BlockWeapon()
{
}

void BlockWeapon::ReduceTime(int dt)
{
	coolDownTime_ -= dt;

	if (coolDownTime_ < 0)
		coolDownTime_ = 0;
}

const std::string& BlockWeapon::GetName()
{
	return name_;
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
	if (coolDownTime_ > 0)
		return;

	if (!isDirectionAllowed(currDirection_))
		return;

	//! Create the bullet
	//std::cout << "Shooting from " << name_ << " !\n";
	WORLD->CreateBullet(currDirection_, glm::vec3(-20.0f, 5.0f, 0.0f));
}
