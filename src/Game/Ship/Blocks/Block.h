#pragma once

#include "..\..\..\Engine\Objects\GameObject.h"

enum BlockType
{
	
#define BLOCKTYPE(TypeOfBlock) TypeOfBlock,
#include "BlockTypes.h"
#undef BLOCKTYPE
	UndefinedType
};




class Block :
	public GameObject
{
	friend class BlockFactory;
	friend class ObjectDataBase;

public:
	Block();
	~Block();

	BlockType GetType();

	virtual void Draw(Camera* camera, glm::vec3 coords_) const;
	virtual Block* Clone() const = 0; //TODO: Remove this 

protected:
	glm::vec3 relatedCoords_;

	BlockType blockType_;
	
	float hits_;
	float mass_;
};

