#pragma once

#include "../GraphicsObjectManager.h"

class Skybox
{
	public:
				Skybox(GraphicsObjectManager* manager);
				~Skybox();

				void Draw(Camera* camera);
	private:
				GraphicsObject* skyboxAsset_;
};