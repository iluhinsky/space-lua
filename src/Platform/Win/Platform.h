#pragma once

#include <windows.h>

class Platform
{
public:
	Platform();
	~Platform();

	void PlatformClipCursor(int x1, int y1, int x2, int y2);
};

