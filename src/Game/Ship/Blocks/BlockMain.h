#pragma once
#include "Block.h"

class BlockMain :
	public Block
{
public:
	BlockMain();
	BlockMain(const BlockMain& block);

	~BlockMain();

	virtual Block* Clone() const;
};

