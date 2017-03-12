#pragma once

#include "..\..\..\Engine\Objects\GameObject.h"

enum BlockType
{
	
#define BLOCKTYPE(TypeOfBlock) TypeOfBlock,
#include "BlockTypes.h"
#undef BLOCKTYPE
	UndefinedType
};




class Block :
	public GameObject
{
	friend class BlockFactory;
	friend class ObjectDataBase;

public:
	Block();
	~Block();

private:
	BlockType blockTypes_;
	
	float hits_;
	float mass_;
};

