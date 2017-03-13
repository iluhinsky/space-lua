#include "BlockShield.h"



BlockShield::BlockShield()
{
}


BlockShield::BlockShield(const BlockShield& block)
{
	graphicsAsset_ = block.graphicsAsset_;

	blockType_ = block.blockType_;

	hits_ = block.hits_;
	mass_ = block.mass_;

	name_ = block.name_;

	shieldPower_    = block.shieldPower_;
	shieldPowerMax_ = block.shieldPowerMax_;
	recoveryRate_   = block.recoveryRate_;
}


BlockShield::~BlockShield()
{
}


Block* BlockShield::Clone() const
{
	return new BlockShield(*this);
}