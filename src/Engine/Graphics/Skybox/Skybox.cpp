#include "Skybox.h"

const float SKYBOX_GRAPHICS_SCALE = 200.0f;

Skybox::Skybox(GraphicsObjectManager* manager)
{
	GraphicsObjectInfo skyboxInfo;

	skyboxInfo.modelName_ = "skybox.3ds";
	skyboxInfo.textureName_ = "skybox.png";
	skyboxInfo.shaderNames_._vertexShaderName = "skybox_vertex.glsl";
	skyboxInfo.shaderNames_._fragmentShaderName = "skybox_fragment.glsl";
	skyboxInfo.isInfinite_ = true;

	skyboxAsset_ = manager->Get(skyboxInfo);
	skyboxAsset_->SetScale(SKYBOX_GRAPHICS_SCALE);
}

Skybox::~Skybox()
{
	delete skyboxAsset_;
}


void Skybox::Draw(Camera* camera)
{
	glm::vec3 globalCoord	= glm::vec3(0, 0, 0);
	glm::mat3 rotation		= glm::mat3(1.0f);

	skyboxAsset_->Draw(camera, globalCoord, rotation);
}