#pragma once
#include "Block.h"


class BlockShield :
	public Block
{
	friend class ObjectDataBase;
	friend class BlockFactory;

public:
	BlockShield();
	BlockShield(const BlockShield& block);

	~BlockShield();

	virtual Block* Clone() const;

private:
	std::string name_;

	float shieldPower_;
	float shieldPowerMax_;
	float recoveryRate_;
};

