#pragma once

#include "Block.h"

class OrientedBlock :
	public Block
{
	friend class BlockFactory;

public:
	OrientedBlock();
	~OrientedBlock();

protected:
	glm::vec3 orientation_;
};

