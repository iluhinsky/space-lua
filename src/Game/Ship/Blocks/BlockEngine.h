#pragma once

#include "OrientedBlock.h"

enum BlockEngineCommand
{
	gasCommand
};


class BlockEngine :
	public OrientedBlock
{
	friend class ObjectDataBase;
	friend class BlockFactory;

public:
	BlockEngine();
	~BlockEngine();
	virtual Block* Clone() const;

	void ReduceTime(int dt);
	void SetCommand(BlockEngineCommand);

	void SetPower(int power); //! from 1 to 10

private:
	void Gas();

	float power_;

	int estimatedTime_;
	int coolDownTime_;
};

