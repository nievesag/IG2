#include "Engine.h"
#include "DataSizes.h"

#include <OgreParticleSystem.h>

Engine::Engine(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	engineEnt = sceneMng->createEntity("Barrel.mesh");
	engineNod = node->createChildSceneNode();
	engineNod->attachObject(engineEnt);

	engineNod->setPosition(initPos);

	engineNod->_update(false, false);

	engineNod->setScale(DataSizes::ENGINE_BASE_SIZE / engineNod->_getWorldAABB().getSize());

	engineEnt->setMaterialName("Motor");

	fireSys = mSM->createParticleSystem("FireSystem", "Fire");
	engineNod->attachObject(fireSys);
	fireSys->setEmitting(false);
}

void Engine::setEngine(bool on)
{
	fireSys->setEmitting(on);

	if (!on)
	{
		fireSys->clear();
	}
}
