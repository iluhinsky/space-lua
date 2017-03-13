#include "BlockMain.h"



BlockMain::BlockMain()
{
}


BlockMain::BlockMain(const BlockMain& block)
{
	graphicsAsset_ = block.graphicsAsset_;

	blockType_ = block.blockType_;

	hits_ = block.hits_;
	mass_ = block.mass_;
}


BlockMain::~BlockMain()
{
}


Block* BlockMain::Clone() const
{
	return new BlockMain(*this);
}