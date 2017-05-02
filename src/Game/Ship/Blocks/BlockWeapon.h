#pragma once

#include "OrientedBlock.h"

enum BlockWeaponCommand
{
	ShootCommand = 0
};


class BlockWeapon :
	public OrientedBlock
{
	friend class ObjectDataBase;
	friend class BlockFactory;

public:
	BlockWeapon();
	~BlockWeapon();

	virtual Block* Clone() const;

	void ReduceTime(int dt);
	void SetCommand(BlockWeaponCommand);

private:
	void Shoot();

	int estimatedTime_;
	int coolDownTime_; //! in milliseconds
};

