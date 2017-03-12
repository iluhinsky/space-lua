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


class ObjectDataBase
{
public:
	ObjectDataBase();
	~ObjectDataBase();

	void Fill(std::string name);

	Block*    GetCopyOf(BlockType blockType);
	BlockType GetTypeOf(std::string blockTypeName);

private:
	std::unordered_map<BlockType, Block*> db_;
	std::unordered_map<std::string, BlockType> dictionary_;
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

