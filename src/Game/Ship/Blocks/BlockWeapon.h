#pragma once

#include "Block.h"


class BlockWeapon :
	public Block
{
public:
	BlockWeapon();
	BlockWeapon(const BlockWeapon& block);

	~BlockWeapon();

	const std::string& GetName();
	virtual Block* Clone() const;

private:
	std::string name_;
};

