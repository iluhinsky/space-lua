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
	BlockShield(const BlockShield& block);

	~BlockShield();

	const std::string& GetName();
	void Switch(const bool mode, const float time = 0.0f);
	virtual Block* Clone() const;

	void SetComand(BlockShieldCommand command);

private:
	void EnableShield();
	void DisableShield();

	std::string name_;

	bool isWorking_;
	float shieldPower_;
	float shieldPowerMax_;
	float recoveryRate_;
};

