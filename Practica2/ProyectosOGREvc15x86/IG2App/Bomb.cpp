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
	mMechaNode->setPosition(Ogre::Vector3(0, 150, 5));
	mMechaNode->attachObject(mecha);

	// sistemas de particulas
	sysMecha = mSM->createParticleSystem(name, "Examples/Smoke");
	sysMechaNode = b->createChildSceneNode();
	sysMechaNode->attachObject(sysMecha);
	sysMecha->setEmitting(false);
	sysMechaNode->setPosition(0,100,0);
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

			// -- Cambio de posicion
			float newPos = Ogre::Math::lerp(initMechaPos, initBombaPos, (current/Constants::bombTick));
			sysMechaNode->setPosition(sysMechaNode->getPosition().x, newPos, sysMechaNode->getPosition().z);

			// -- Cambio de escala
			float currSize = mCuerpoNode->_getWorldAABB().getSize().x;
			currentAnim += t;

			if (increasing) // si se esta haciendo grande
			{
				if (currSize < Constants::bigBombSize.x)
				{
					float newSize = Ogre::Math::lerp(Constants::normalBombSize.x, Constants::bigBombSize.x, (currentAnim/Constants::bombAnimTransTime));
					float factor = (newSize / currSize);
					mCuerpoNode->scale(factor,factor,factor);
				}
				else
				{
					increasing = false;
					currentAnim = 0;
				}
			}
			else // si se esta haciendo pequena
			{
				if (currSize > Constants::smallBombSize.x)
				{
					float newSize = Ogre::Math::lerp(Constants::normalBombSize.x, Constants::smallBombSize.x, currentAnim / Constants::bombAnimTransTime);
					float factor = (newSize / currSize);
					mCuerpoNode->scale(factor, factor, factor);
				}
				else
				{
					increasing = true;
					currentAnim = 0;
				}
			}

			if (current > Constants::bombTick)
			{
				exploded = true;
				sysMecha->setEmitting(false);
				active = false;
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
	initMechaPos = sysMechaNode->getPosition().y;
	initBombaPos = mCuerpoNode->getPosition().y;
	active = true;
	current = 0;
	exploded = false;
	sysMecha->setEmitting(true);
	setVisible(true);
}
