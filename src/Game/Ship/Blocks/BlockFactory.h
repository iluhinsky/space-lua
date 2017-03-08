#pragma once

#include "Block.h"
#include "BlockMain.h"
#include "BlockShield.h"

#include "..\..\..\Engine\Graphics\GraphicsObject\GraphicsObjectFactory.h"

struct BlockInfo 
{
	BlockType blockType;
	GraphicsObjectInfo graphicsInfo;
};

class BlockFactory
{
public:
	BlockFactory();
	~BlockFactory();

	Block* GetBlock(BlockInfo blockInfo);


};

