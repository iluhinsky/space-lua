#pragma once
#include "Block.h"

class BlockMain :
	public Block
{
public:
	BlockMain();
	BlockMain(const BlockMain& block);

	~BlockMain();

	virtual const std::string& GetName();
	virtual Block* Clone() const;

private:
	std::string name_;
};

