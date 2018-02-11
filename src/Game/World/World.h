#pragma once

#include "../../Engine/Math/Camera.h"
#include "../Ship/Ship.h"
#include "Effects/Bullet.h"
#include "WorldLoader.h"



struct ShipStatistics
{
	int teamNumber;

	int shipCount;
	int maxShipCount;

	glm::vec3 color_;
};


class World
{
	friend class WorldLoader;

	friend class Application; //! remove

public:
	World();
	~World();

	void Init();
	void FillStatistics();
	void Load(std::string worldName);
	void UpdateShipsIDVector(); //! Call after every death of any ship
	void UpdateAfterPhysicsStep();
	void BorderCheck();

	void Draw(Camera* camera);
	void ReduceTime(int dt);

	void CreateBullet(glm::vec3 direction, glm::vec3 startingPosition);
	void ClearUnexisingObjects();

	void RunLUA();
	void ExecuteLogic();

	Ship* GetShipByID(int shipID);
	int GetIDByShip(Ship* ship);
	const std::vector<int>& GetShipsID();

private:
	std::list   <std::shared_ptr<Bullet>> bullets_;
	std::map    <int, Ship*>              shipsDataBase_;
	std::vector <int>                     shipsID_;

	WorldLoader* worldLoader_;

	std::map<std::string, ShipStatistics> statistics;
};
