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
	#define BLOCKTYPE(TypeOfBlock) dictionary_[#TypeOfBlock] = TypeOfBlock;
	#include "BlockTypes.h"
	#undef BLOCKTYPE	

	std::string pathToDB = "../bin/resources/DB/" + name;
	FILE* file = fopen(pathToDB.c_str(), "r");
	assert(file);

	char string[30] = {};
	float n = 0.0f;
	float rate = 0.0f;

	fscanf(file, "%s", string);

	while (strcmp(string, "END") != 0 && !feof(file))
	{	
		BlockType blockType = GetTypeOf(string);

		Block* newBlock = nullptr;

		float hits = 0.0f;
		float mass = 0.1f;
		fscanf(file, ": hits: %f mass: %f", &hits, &mass);

		GraphicsObjectInfo assetNames = {};
		char model[30] = {};
		char texture[30] = {};
		char vertexShader[30] = {};
		char fragmentShader[30] = {};
		fscanf(file, "model: %s texture: %s vertexShader: %s fragmentShader: %s", model, texture, vertexShader, fragmentShader);
		assetNames.modelName_ = model;
		assetNames.textureName_ = texture;
		assetNames.shaderNames_._vertexShaderName = vertexShader;
		assetNames.shaderNames_._fragmentShaderName = fragmentShader;

		manager_.Get(assetNames);

		switch (blockType)
		{
		case blockTypeMain:
			newBlock = new BlockMain;

			break;

		case blockTypeShield:
			newBlock = new BlockShield;

			fscanf(file, "shieldPowerMax: %f recoveryRate: %f", &n, &rate);
			
			// why don't we initialize newBlock->name_ and newBlock->shieldPower ?
			((BlockShield*)newBlock)->shieldPowerMax_ = n;
			((BlockShield*)newBlock)->recoveryRate_   = rate;

			break;

		default:
			break;
		}

		newBlock->hits_ = hits;
		newBlock->mass_ = mass;

		db_[blockType] = newBlock;

		fscanf(file, "%s", string);
	}

	fclose(file);
}

Block* ObjectDataBase::GetCopyOf(BlockType blockType)
{
	Block* block = db_[blockType];

	return block;
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
