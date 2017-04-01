#pragma once

#include <btBulletDynamicsCommon.h>

#include "..\..\..\Engine\Graphics\GraphicsObject\GraphicsObject.h"
#include "..\..\..\Engine\Math\Camera.h"
#include "..\..\..\Engine\Math\math_3d.h"


enum BlockType
{

#define BLOCKTYPE(TypeOfBlock) TypeOfBlock,
#include "BlockTypes.h"
#undef BLOCKTYPE
	UndefinedType
};


class Block
{
	friend class BlockFactory;
	friend class ObjectDataBase;

public:
	Block();
	~Block();

	BlockType GetType();

	void Draw(Camera* camera, btTransform& transform) const;
	virtual Block* Clone() const = 0; //TODO: Remove this

	float     GetMass();
	glm::vec3 GetRelatedCoords();

protected:
	glm::vec3 relatedCoords_;

	BlockType blockType_;

	float hits_;
	float mass_;

	GraphicsObject* graphicsAsset_;
};
