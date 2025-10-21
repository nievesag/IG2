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

	// 3) palo ca�a


	// 4) hilo ca�a

	// 5) pez ca�a 1

	// 6) pez ca�a 2

	// 7) pez ca�a 3

	// 8) cuerpo serpiente

	// 9) cabeza serpiente

	// 10) cola serpiente

}

void Fisher::frameRendered(const Ogre::FrameEvent& evt)
{

}
