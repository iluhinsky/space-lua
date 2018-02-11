#include "WorldLoader.h"

WorldLoader::WorldLoader(std::map <int, Ship*>* shipsDataBase):
	shipsDataBase_(shipsDataBase)
{

}


WorldLoader::~WorldLoader()
{

}


void WorldLoader::Init()
{
	shipFactory_.Init();
}


void WorldLoader::Load(std::string worldName)
{
	std::string pathToWorld = "../bin/resources/worlds/";

	worldName = pathToWorld + worldName;

	FILE* file = fopen(worldName.c_str(), "r");

	char string[30] = {};
	int freeID      = 0;

	fscanf(file, "%s", string);

	while (strcmp(string, "END") != 0)
	{
		ShipInfo shipInfo;

		shipInfo.name_ = string;
		
		fscanf(file, " (%f, %f, %f)", 
			&(shipInfo.coord_.x),
			&(shipInfo.coord_.y),
			&(shipInfo.coord_.z));

		Ship* ship = shipFactory_.GenerateShip(shipInfo);

		(*shipsDataBase_)[freeID] = ship;
		freeID++;

		fscanf(file, "%s", string);
	}

	printf("World %s is loaded.\n", worldName.c_str());

	fclose(file);
}