#pragma once
#include "Block.h"

class BlockMain :
	public Block
{
public:
	BlockMain();
	~BlockMain();

	virtual Block* Clone() const;
};

