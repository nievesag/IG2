#include "Fisher.h"

Fisher::Fisher(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: Enemy(initPos, node, sceneMng, "")
{
	// 1) pinguino
	mFisherNode = mSM->getRootSceneNode()->createChildSceneNode("fisher"); // esto fuera????
	// Cabeza
	Ogre::Entity* pinguino = mSM->createEntity("penguin.mesh");
	mPenguinNode = mFisherNode->createChildSceneNode();
	mPenguinNode->attachObject(pinguino);

	// 2) peluca pinguino
	Ogre::Entity* peluca = mSM->createEntity("sphere.mesh");
	mPelucaNode = mPenguinNode->createChildSceneNode();
	mPelucaNode->attachObject(peluca);

	// 3) palo caña


	// 4) hilo caña

	// 5) pez caña 1

	// 6) pez caña 2

	// 7) pez caña 3

	// 8) cuerpo serpiente

	// 9) cabeza serpiente

	// 10) cola serpiente

}

void Fisher::frameRendered(const Ogre::FrameEvent& evt)
{

}
