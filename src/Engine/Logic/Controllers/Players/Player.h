#pragma once

#include "../Controller.h"
#include "../../../Math/Camera.h"

class Player :
	public Controller
{
public:
	Player();
	~Player();

	Camera* GetCamera();

	virtual void OnKeyboard(int key);
	virtual void OnMouse(int x, int y);
	virtual void OnMouseMove(int DeltaX, int DeltaY);

	void UpdateCamera();

private:

	Camera* _camera;

	glm::vec3 _cameraPos;
};