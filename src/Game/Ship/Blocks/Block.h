#pragma once

#include "..\..\..\Engine\Objects\GameObject.h"
#include "BlockTypes.h"


class Block :
	public GameObject
{
	friend class BlockFactory;

public:
	Block();
	~Block();

private:
	BlockType blockTypes_;
};

