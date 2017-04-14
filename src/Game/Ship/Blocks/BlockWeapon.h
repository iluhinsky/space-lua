#pragma once

#include "OrientedBlock.h"


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

private:
	void Shoot();

	int coolDownTime_; //! in milliseconds

	std::string name_;
};

