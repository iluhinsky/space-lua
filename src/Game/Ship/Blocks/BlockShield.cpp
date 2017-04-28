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


Block* BlockShield::Clone() const
{
	return new BlockShield(*this);
}

void BlockShield::SetComand(BlockShieldCommand command)
{
	switch (command)
	{
	case EnableShieldCommand:
		(this->Command_) = (void (Block::*)()) &BlockShield::EnableShield;
		break;
	case DisableShieldCommand:
		(this->Command_) = (void (Block::*)()) &BlockShield::DisableShield;
		break;
	default:
		break;
	}
}

void BlockShield::EnableShield()
{
//	if (!isWorking_) std::cout << "Enable Shield '" << name_ << "'. Now it is working.\n"; // for testing
	isWorking_ = true;
}

void BlockShield::DisableShield()
{
//	if (isWorking_) std::cout << "Disable Shield '" << name_ << "'. Now it isn't working.\n"; // for testing
	isWorking_ = false;
}