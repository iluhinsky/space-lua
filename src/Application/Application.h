#pragma once

#include "Window.h"
//#include "Manager.h"

#include "../Engine/Logic/Controllers/Players/Player.h"

enum AppState
{
	Game = 1,
	Menu = 2
};

class World;

#define APPLICATION	Application::instance_

class Application : public Window
{
public:
	Application();
	virtual ~Application();

	static Application* instance_;

	void Init();

	sf::Time getTime() const;

private:
	virtual void DisplayFunc();
	virtual void ReshapeFunc(int width, int height);
	virtual void CloseFunction();
	virtual void KeyboardFunc();
	virtual void PassiveMotionFunc(int x, int y);

	void GameMouseFunc(int x, int y);
	void MenuMouseFunc(int x, int y);

	sf::Clock     clocks_;

	World*        world_;
	Player*       player_;
	AppState      currentState_;
};