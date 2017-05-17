#include "BlockMain.h"



BlockMain::BlockMain()
{
}

BlockMain::~BlockMain()
{
}

Block* BlockMain::Clone() const
{
	return new BlockMain(*this);
}
