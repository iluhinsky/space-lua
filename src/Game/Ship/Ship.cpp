#include "Ship.h"
#include "Blocks/BlockShield.h"


Ship::Ship() : controller_(this)
{
	
}


Ship::~Ship()
{

}


void Ship::Draw(Camera* camera)
{
	for (auto it = blocks_.begin(); it != blocks_.end(); ++it)
		(*it)->Draw(camera, coord_);
}