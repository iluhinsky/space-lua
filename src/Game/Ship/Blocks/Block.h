#pragma once

#include <btBulletDynamicsCommon.h>

#include "..\..\..\Engine\Graphics\GraphicsObject\GraphicsObject.h"
#include "..\..\..\Engine\Math\Camera.h"
#include "..\..\..\Engine\Math\math_3d.h"


class Ship;


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
	void hit(int damage);
	bool isExist();
	bool isLinked();

	void Draw(Camera* camera) const;
	virtual Block* Clone() const = 0; //TODO: Remove this

	float     GetMass();
	glm::vec3 GetRelatedCoords();
	glm::vec3 GetGlobalCoords();

	void      SetShip(Ship* ship);

	const std::string& GetName();

	void UpdateAfterPhysicsStep(glm::vec3& shipGlobalCoords, glm::mat3& currRotation);

	void ExecuteCommand();

	virtual void SetStandartCommand();
	void DoNothing();

protected:
	std::string name_;

	BlockType   blockType_;
	glm::vec3   relatedCoords_;

	float       hits_;
	float       mass_;

	glm::vec3   currGlobalCoords_;
	glm::mat3   currRotation_;

	bool isLinked_;

	GraphicsObject* graphicsAsset_;

	void (Block:: *Command_) ();

	Ship* ship_;
};
