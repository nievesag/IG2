#include "Engine.h"
#include "DataSizes.h"

Engine::Engine(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	engineEnt = sceneMng->createEntity("Barrel.mesh");
	engineNod = node->createChildSceneNode();
	engineNod->attachObject(engineEnt);
	engineNod->scale(DataSizes::ENGINE_BASE_SIZE);
}