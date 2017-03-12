#pragma once
#include "Block.h"


class BlockShield :
	public Block
{
	friend class ObjectDataBase;
	friend class BlockFactory;

public:
	BlockShield();
	~BlockShield();

private:
	std::string name_;

	int shieldPower_;
	int shieldPowerMax_;
	int recoveryRate_;
};

