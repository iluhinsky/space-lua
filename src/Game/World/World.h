#pragma once

#include "../../Engine/Math/Camera.h"
#include "../Ship/Ship.h"
#include "Effects\Bullet.h"
#include "WorldLoader.h"


class World
{
	friend class WorldLoader;

	friend class Application; //! remove

public:
	World();
	~World();

	void Init();
	void Load(std::string worldName);

	void Draw(Camera* camera);
	void ReduceTime(int dt);

	void CreateBullet(glm::vec3 velocity, glm::vec3 startingPosition);

	void ClearUnexisingBullets();

	void RunLUA();
	void ExecuteLogic();

private:
	std::vector <Ship*>                   ships_;
	std::list   <std::shared_ptr<Bullet>> bullets_;

	WorldLoader* worldLoader_;
};