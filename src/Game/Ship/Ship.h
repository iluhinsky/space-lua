#pragma once

#include "..\..\Include.h"
#include "Blocks\Block.h"
#include "ShipController.h"


class Ship
{
	friend class ShipFactory;
	friend class ShipController;

public:
	Ship();
	~Ship();

	void Draw(Camera* camera);

private:
	std::string shipName_;
	glm::vec3 coord_;

	std::vector<Block*> blocks_;

	ShipController controller_;
};