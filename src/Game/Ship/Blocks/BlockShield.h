#pragma once
#include "Block.h"

enum BlockShieldCommand
{
	EnableShieldCommand  = 0,
	DisableShieldCommand = 1
};


class BlockShield :
	public Block
{
	friend class ObjectDataBase;
	friend class BlockFactory;

public:
	BlockShield();
	~BlockShield();

	virtual Block* Clone() const;

	void SetComand(BlockShieldCommand command);

private:
	void EnableShield();
	void DisableShield();

	bool  isWorking_;
	float shieldPower_;
	float shieldPowerMax_;
	float recoveryRate_;
};

