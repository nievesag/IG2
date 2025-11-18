#include "Bomb.h"

#include <OgreParticleSystem.h>

#include "Constants.h"

Bomb::Bomb(Vector3 a, SceneNode* b, SceneManager* c, String name)
	: Object(a, b, c, true)
{
	bomba = mSM->createEntity("sphere.mesh");
	mCuerpoNode = b->createChildSceneNode();
	mCuerpoNode->attachObject(bomba);
	mCuerpoNode->scale(Ogre::Vector3(0.5, 0.5, 0.5));

	mecha = mSM->createEntity("Barrel.mesh");
	mMechaNode = mCuerpoNode->createChildSceneNode();
	mMechaNode->scale(Ogre::Vector3(2, 20, 2));
	mMechaNode->setPosition(Ogre::Vector3(0, 100, 5));
	mMechaNode->attachObject(mecha);

	// sistemas de particulas
	sysMecha = mSM->createParticleSystem(name, "Examples/Smoke");
	sysMechaNode = b->createChildSceneNode();
	sysMechaNode->attachObject(sysMecha);
	sysMecha->setEmitting(false);
	sysMechaNode->setPosition(0,80,0);
}

Bomb::~Bomb()
{

}

void Bomb::update(Real t)
{
	// si esta activa
	if (active)
	{
		// si aun no ha explotado
		if (!exploded)
		{
			current += t;
			sysMechaNode->translate(0,-1,0);

			//mCuerpoNode->scale(1.05,1.05,1.05);
			Vector3 maxSize = mCuerpoNode->_getWorldAABB().getSize();
			std::cout << maxSize << std::endl;

			if (current > Constants::bombTick)
			{
				exploded = true;
				sysMecha->setEmitting(false);
				active = false;
				//clearBomb();
			}
		}
	}
}

void Bomb::clearBomb()
{
	active = false;
	current = 0;
	exploded = false;
	//sysHumo->setEmitting(false);
	//sysHumo->clear();
	sysMecha->setEmitting(false);
	sysMecha->clear();
	setVisible(false);
}

void Bomb::createBomb()
{
	active = true;
	current = 0;
	exploded = false;
	sysMecha->setEmitting(true);
	setVisible(true);
}
