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
	BlockWeapon(const BlockWeapon& block);

	~BlockWeapon();

	void   ReduceTime(int dt);
	const  std::string& GetName();
	virtual Block* Clone() const;

	void SetCommand(BlockWeaponCommand);

private:
	void Shoot();

	int coolDownTime_; //! in milliseconds

	std::string name_;
};

