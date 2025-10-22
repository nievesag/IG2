#include "Fisher.h"

Fisher::Fisher(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: Enemy(initPos, node, sceneMng, "ogrehead.mesh"), mFisherNode(node)
{
	// -- pinguino
	// 1) pinguino
	Ogre::Entity* pinguino = mSM->createEntity("penguin.mesh");
	mPenguinNode = mFisherNode->createChildSceneNode();
	mPenguinNode->attachObject(pinguino);
	std::cout << "HOLA1" << std::endl;

	// 2) peluca pinguino
	Ogre::Entity* peluca = mSM->createEntity("sphere.mesh");
	mPelucaNode = mPenguinNode->createChildSceneNode();
	mPelucaNode->attachObject(peluca);

	// -- ca�a
	// 3) palo ca�a
	Ogre::Entity* palo = mSM->createEntity("cube.mesh");
	mPaloNode = mPenguinNode->createChildSceneNode();
	mPaloNode->attachObject(palo);

	// 4) hilo ca�a
	Ogre::Entity* hilo = mSM->createEntity("cube.mesh");
	mHiloNode = mPaloNode->createChildSceneNode();
	mHiloNode->attachObject(hilo);

	// 5) pez ca�a 1
	Ogre::Entity* pez1 = mSM->createEntity("fish.mesh");
	mPez1Node = mHiloNode->createChildSceneNode();
	mPez1Node->attachObject(pez1);

	// 6) pez ca�a 2
	Ogre::Entity* pez2 = mSM->createEntity("fish.mesh");
	mPez2Node = mHiloNode->createChildSceneNode();
	mPez2Node->attachObject(pez2);

	// 7) pez ca�a 3
	Ogre::Entity* pez3 = mSM->createEntity("fish.mesh");
	mPez3Node = mHiloNode->createChildSceneNode();
	mPez3Node->attachObject(pez3);

	// -- serpiente 
	// 8) cuerpo serpiente
	Ogre::Entity* cuerpoSerp = mSM->createEntity("knot.mesh");
	mCuerpoSerpNode = mPenguinNode->createChildSceneNode();
	mCuerpoSerpNode->attachObject(cuerpoSerp);

	// 9) cabeza serpiente
	Ogre::Entity* cabezaSerp = mSM->createEntity("fish.mesh");
	mCabezaSerpNode = mCuerpoSerpNode->createChildSceneNode();
	mCabezaSerpNode->attachObject(cuerpoSerp);

	// 10) cola serpiente
	Ogre::Entity* colaSerp = mSM->createEntity("fish.mesh");
	mColaSerpNode = mCuerpoSerpNode->createChildSceneNode();
	mColaSerpNode->attachObject(colaSerp);
}

Fisher::~Fisher()
{
}

void Fisher::frameRendered(const Ogre::FrameEvent& evt)
{
	Enemy::frameRendered(evt);

	// animacion ?
}
