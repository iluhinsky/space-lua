#include "ShipController.h"
#include "Ship.h"


ShipController::ShipController(Ship* ship)
{
	assert(ship);
	ship_ = ship;
}


ShipController::~ShipController()
{
}
