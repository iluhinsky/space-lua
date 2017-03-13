#pragma once

#include "Block.h"
#include "BlockMain.h"
#include "BlockShield.h"
#include "..\..\..\Engine\Graphics\GraphicsObjectManager.h"


struct BlockInfo 
{
	BlockType blockType;
	GraphicsObjectInfo graphicsInfo;
};


class ObjectDataBase
{
public:
	ObjectDataBase();
	~ObjectDataBase();

	void Fill(std::string name);

	Block*    GetCopyOf(BlockType blockType);
	BlockType GetTypeOf(std::string blockTypeName);

private:
	std::map<BlockType, Block*> db_;
	std::map<std::string, BlockType> dictionary_;

	GraphicsObjectManager manager_;
};


class BlockFactory
{
public:
	BlockFactory();
	~BlockFactory();

	void Init();

	Block* GetBlock(FILE* file);

private:
	ObjectDataBase dataBase_;
};

