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

	//! For basic logic
	BlockType GetType();
	void hit(int damage);
	bool isExist();

	//! For removing unlinked blocks
	bool isLinkedtoMain();
	void LinktoMain();
	void UnlinkfromMain();

	void Link  (Direction direction, Block* block);
	void Unlink(Direction direction);
	Block* GetBlockBy (Direction direction);

	void Draw(Camera* camera) const;
	virtual Block* Clone() const = 0; //TODO: Remove this

	float     GetMass();
	glm::vec3 GetRelatedCoords();
	glm::vec3 GetGlobalCoords();

	void      SetShip(Ship* ship);

	virtual const std::string& GetName() = 0;

	void UpdateAfterPhysicsStep(glm::vec3& shipGlobalCoords, glm::mat3& currRotation);

	void ExecuteCommand();

	virtual void SetStandartCommand();
	void DoNothing();

protected:
	glm::vec3 relatedCoords_;

	glm::vec3 currGlobalCoords_;
	glm::mat3 currRotation_;

	BlockType blockType_;

	float hits_;
	float mass_;
	
	bool isLinked_;

	GraphicsObject* graphicsAsset_;

	void (Block:: *Command_) ();

	std::map<Direction, Block*> links_;

	Ship* ship_;
};
