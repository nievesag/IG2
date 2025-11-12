#include "Bomb.h"

#include <OgreParticleSystem.h>

#include "Constants.h"

Bomb::Bomb(Vector3 a, SceneNode* b, SceneManager* c, String name)
	: Object(a, b, c, true)
{
	Ogre::Entity* bomba = mSM->createEntity("sphere.mesh");
	mCuerpoNode = b->createChildSceneNode();
	mCuerpoNode->attachObject(bomba);
	mCuerpoNode->scale(Ogre::Vector3(0.5, 0.5, 0.5));

	Ogre::Entity* mecha = mSM->createEntity("Barrel.mesh");
	mMechaNode = mCuerpoNode->createChildSceneNode();
	mMechaNode->scale(Ogre::Vector3(2, 20, 2));
	mMechaNode->setPosition(Ogre::Vector3(0, 100, 5));
	mMechaNode->attachObject(mecha);

	// sistemas de particulas
	sysHumo = mSM->createParticleSystem(name, "Examples/Smoke");
	b->attachObject(sysHumo);
	sysHumo->setEmitting(true);
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

			if (current > Constants::bombTick)
			{
				exploded = true;
				sysHumo->setEmitting(false);
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
	sysHumo->setEmitting(false);
	sysHumo->clear();
	sysMecha->setEmitting(false);
	sysMecha->clear();
}
