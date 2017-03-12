#pragma once

#include "../Include.h"
#include "../Platform/Win/Platform.h"

class Window
{
public:
	Window();
	virtual ~Window();

	bool InitWindow (sf::Vector2u size, std::string title);

	void MainLoop();
	void StopLoop();

	sf::Vector2u GetWindowSize();

	void SetCursor(int x, int y);
	void ShowCursor(bool state);
	void ClipCursorInWindow();

protected:
	virtual void DisplayFunc(void)                  = 0;
	virtual void ReshapeFunc(int width, int height) = 0;
	virtual void CloseFunction()                    = 0;
	virtual void KeyboardFunc()                     = 0;
	virtual void PassiveMotionFunc(int x, int y)    = 0;

	sf::Window*  _window;
	Platform*    _platform;

	std::vector<sf::Keyboard::Key> _keys;

	sf::Vector2i _prevMousePos;

private:
	bool        _isLoopRunning;
};