#pragma once

#include "Block.h"


class BlockWeapon :
	public Block
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

