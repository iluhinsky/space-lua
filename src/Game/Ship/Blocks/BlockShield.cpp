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

	isWorking_      = block.isWorking_;
	shieldPower_    = block.shieldPower_;
	shieldPowerMax_ = block.shieldPowerMax_;
	recoveryRate_   = block.recoveryRate_;
}


BlockShield::~BlockShield()
{
}

const std::string& BlockShield::GetName()
{
	return name_;
}

void BlockShield::Switch(const bool mode, const float time)
{
	assert(time >= 0.0);

	isWorking_ = mode; // mode == true means that shields should be switched on

	//TODO work with time
}

Block* BlockShield::Clone() const
{
	return new BlockShield(*this);
}