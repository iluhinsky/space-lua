#include "BlockWeapon.h"



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

const std::string& BlockWeapon::GetName()
{
	return name_;
}

Block* BlockWeapon::Clone() const
{
	return new BlockWeapon(*this);
}