#include "WorldLoader.h"

WorldLoader::WorldLoader(std::vector<Ship*>* ships):
	ships_ (ships)
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

	fscanf(file, "%s", string);

	while (strcmp(string, "END") != 0)
	{
		ShipInfo shipInfo;

		shipInfo.name_ = string;
		
		fscanf(file, "(%f, %f, %f)", &(shipInfo.coord_.x),
		                             &(shipInfo.coord_.y),
		                             &(shipInfo.coord_.z));

		Ship* ship = shipFactory_.GenerateShip(shipInfo);

		ships_->push_back(ship);

		fscanf(file, "%s", string);
	}

	printf("World %s is loaded.\n", worldName.c_str());

	fclose(file);
}