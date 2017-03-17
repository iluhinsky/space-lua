#pragma once

class Ship;

class ShipController
{
public:
	ShipController(Ship* ship);
	~ShipController();

private:
	Ship* ship_;
};

