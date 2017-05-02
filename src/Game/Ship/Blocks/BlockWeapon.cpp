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

	//! Create the bullet
	btTransform shipTransform = ship_->GetTransform();

	glm::mat3 rotation     = toGLM_M3x3(shipTransform.getBasis());
	glm::mat3 rotation_inv = glm::inverse(rotation);
	glm::vec3 shipCoords   = toGLM(shipTransform.getOrigin());

	glm::vec3 globalCoords = shipCoords + rotation_inv * relatedCoords_;

	WORLD->CreateBullet(currDirection_, globalCoords + currDirection_ * 2.0f);

	estimatedTime_ = coolDownTime_;
}
