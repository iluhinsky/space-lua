#include "BlockFactory.h"

#include "BlockMain.h"
#include "BlockShield.h"

ObjectDataBase::ObjectDataBase()
{

}


ObjectDataBase::~ObjectDataBase()
{

}

void ObjectDataBase::Fill(std::string name)
{
	#define BLOCKYPE(TypeOfBlock) dictionary[#TypeOfBlock] = TypeOfBlock;
	#include "BlockTypes.h"
	#undef BLOCKTYPE	

	; //! WTF!&!&!&

	std::string pathToDB = "../bin/resources/DB/" + name;

	FILE* file = fopen(pathToDB.c_str(), "r");

	char string[30] = {};
	float n;
	float rate;

	fscanf(file, "%s", string);

	while (strcmp(string, "END") != 0)
	{
		BlockType blockType = GetTypeOf(string);
		Block* newBlock = nullptr;


		float hits = 0;
		float mass = 0.1;

		fscanf(file, ": hits: %f mass: %f", &hits, &mass);
		
		newBlock->hits_ = hits;
		newBlock->mass_ = mass;

		

		switch (blockType)
		{
		case blockTypeShield:
			newBlock = new BlockShield;

			fscanf(file, "| shieldPowerMax: %f recoveryRate: %f", &n, &rate);
			
			((BlockShield*)newBlock)->shieldPowerMax_ = n;
			((BlockShield*)newBlock)->recoveryRate_   = rate;

			break;

		default:
			break;
		}

		db_[blockType] = newBlock;
	}

	fclose(file);
}

Block* ObjectDataBase::GetCopyOf(BlockType blockType)
{

}


BlockType ObjectDataBase::GetTypeOf(std::string blockTypeName)
{
	return dictionary_[blockTypeName];
}


BlockFactory::BlockFactory()
{
}


BlockFactory::~BlockFactory()
{
}


void BlockFactory::Init()
{
	dataBase_.Fill("BlocksDB.txt");
}


Block* BlockFactory::GetBlock(FILE* file)
{
	Block* newBlock = nullptr;

	BlockShield* newBlockShield = nullptr;

	char blockTypeName[30] = {};

	fscanf(file, "%s", blockTypeName);

	if (strcmp(blockTypeName, "END") != 0)
	{
		BlockType blockType = dataBase_.GetTypeOf(blockTypeName);
		newBlock            = dataBase_.GetCopyOf(blockType);

		switch (blockType)
		{
		case blockTypeShield:
			fscanf(file, "| %s", blockTypeName);

			newBlockShield = (BlockShield*) newBlock;
			newBlockShield->name_ = blockTypeName;
			break;

		default:
			break;
		}

		return newBlock;
	}

	return nullptr;
}