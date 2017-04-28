#pragma once

#include "Window.h"
#include "..\Engine\Graphics\GraphicsWorld.h"
#include "..\Engine\Physics\PhysicsWorld.h"
#include "..\Game\World\World.h"
//#include "Manager.h"

#include "../Engine/Logic/Controllers/Players/Player.h"

enum AppState
{
	Game = 1,
	Menu = 2
};

#define APPLICATION	Application::instance_

#define PHYSICSWORLD  Application::instance_->GetPhysicsWorld()
#define GRAPHICSWORLD Application::instance_->GetGraphicsWorld()
#define WORLD         Application::instance_->GetWorld()

class Application : public Window
{
public:
	Application();
	virtual ~Application();

	static Application* instance_;

	void Init();

	sf::Time getTime() const;
	PhysicsWorld*  GetPhysicsWorld();
	GraphicsWorld* GetGraphicsWorld();
	World*         GetWorld();

private:
	virtual void MainFunc();
	virtual void ReshapeFunc(int width, int height);
	virtual void CloseFunction();
	virtual void KeyboardFunc();
	virtual void PassiveMotionFunc(int x, int y);

	void GameMouseFunc(int x, int y);
	void MenuMouseFunc(int x, int y);

	sf::Clock     clocks_;
	sf::Time      prevFrameTime_;

	sf::Time UpdateAndCountTime();

	World*         world_;
	Player*        player_;
	AppState       currentState_;
	PhysicsWorld*  physicsWorld_;
	GraphicsWorld* graphicsWorld_;
};