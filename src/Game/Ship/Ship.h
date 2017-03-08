#pragma once


#include "..\..\Include.h"
#include "Blocks\Block.h"

class Ship
{
public:
	Ship();
	~Ship();

private:
	std::vector<Block> blocks_;
};