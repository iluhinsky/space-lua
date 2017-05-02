#include "BlockShield.h"



BlockShield::BlockShield()
{
}

BlockShield::~BlockShield()
{
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