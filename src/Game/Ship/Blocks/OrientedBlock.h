#pragma once

#include "Block.h"

class OrientedBlock :
	public Block
{
	friend class BlockFactory;

public:
	OrientedBlock();
	~OrientedBlock();

	bool IsDirectionAllowed(glm::vec3 direction);
	void SetDirection(glm::vec3 direction);

	virtual const std::string& GetName() = 0;

protected:
	glm::vec3 orientation_;
	glm::vec3 currDirection_;
};
