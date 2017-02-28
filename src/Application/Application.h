#pragma once

#include "Window.h"
#include "Manager.h"

#include "../Engine/Logic/Controllers/Players/Player.h"

enum AppState
{
	Game = 1,
	Menu = 2
};

class World;

#define APPLICATION	Application::_instance

class Application : public Window
{
public:
	Application();
	virtual ~Application();

	static Application* _instance;

	void Init();

	Manager* _manager;

private:
	virtual void DisplayFunc();
	virtual void ReshapeFunc(int width, int height);
	virtual void CloseFunction();
	virtual void KeyboardFunc();
	virtual void PassiveMotionFunc(int x, int y);

	void GameMouseFunc(int x, int y);
	void MenuMouseFunc(int x, int y);

	World*        _world;
	Player*       _player;
	AppState      _currentState;
};