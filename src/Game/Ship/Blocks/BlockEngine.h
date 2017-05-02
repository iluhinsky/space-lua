#pragma once

#include "OrientedBlock.h"


class BlockEngine :
	public OrientedBlock
{
	friend class ObjectDataBase;
	friend class BlockFactory;

public:
	BlockEngine();
	~BlockEngine();
};

