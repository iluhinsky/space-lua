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
	void SetDirectionFromAngles(int theta, int psi);

protected:
	glm::vec3 target_;
	glm::vec3 up_;

	glm::vec3 currDirection_;
};

