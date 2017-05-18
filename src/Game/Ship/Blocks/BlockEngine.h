#pragma once

#include "OrientedBlock.h"
#include "../../../Engine/Graphics/Particles/ParticleSystem.h"

enum BlockEngineCommand
{
	GasCommand = 0
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

	void UpdateFire();

	void SetPower(int power); //! from 1 to 10
	void SetFire(ParticleSystem* fire) {
		fire_ = fire;
	}


private:
	void Gas();

	float power_;
	ParticleSystem* fire_;

	int estimatedTime_;
	int coolDownTime_;
};

