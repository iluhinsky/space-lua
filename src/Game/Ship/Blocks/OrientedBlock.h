#pragma once

#include "Block.h"

class OrientedBlock :
	public Block
{
	friend class BlockFactory;

public:
	OrientedBlock();
	~OrientedBlock();

	bool isDirectionAllowed(glm::vec3 direction);

protected:
	glm::vec3 orientation_;
};

