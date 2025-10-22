#include "Fisher.h"

Fisher::Fisher(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: Enemy(initPos, node, sceneMng, "penguin.mesh")//, mFisherNode(node)
{
	// -- pinguino
	// 1) pinguino
	/*Ogre::Entity* pinguino = mSM->createEntity("penguin.mesh");
	mPenguinNode = mFisherNode->createChildSceneNode();
	mPenguinNode->attachObject(pinguino);*/

	// 2) peluca pinguino
	Ogre::Entity* peluca = mSM->createEntity("sphere.mesh");
	mPelucaNode = mNode->createChildSceneNode();
	mPelucaNode->attachObject(peluca);
	mPelucaNode->scale(Ogre::Vector3(0.1, 0.07, 0.1));
	mPelucaNode->setPosition(Ogre::Vector3(0, 20, 5));
	peluca->setMaterialName("Suelo");

	// -- caña
	// 3) palo caña
	Ogre::Entity* palo = mSM->createEntity("cube.mesh");
	mPaloNode = mNode->createChildSceneNode();
	mPaloNode->attachObject(palo);
	mPaloNode->scale(Ogre::Vector3(0.03, 0.4, 0.03));
	mPaloNode->setPosition(Ogre::Vector3(22, 0, 0));
	mPaloNode->pitch(Ogre::Angle(-40));

	// 4) hilo caña
	Ogre::Entity* hilo = mSM->createEntity("cube.mesh");
	mHiloNode = mPaloNode->createChildSceneNode();
	mHiloNode->attachObject(hilo);

	// 5) pez caña 1
	Ogre::Entity* pez1 = mSM->createEntity("fish.mesh");
	mPez1Node = mHiloNode->createChildSceneNode();
	mPez1Node->attachObject(pez1);
	mPez1Node->scale(Ogre::Vector3(20, 5, 50));
	mPez1Node->pitch(Ogre::Angle(40));
	mPez1Node->setPosition(Ogre::Vector3(0, 10, -300));

	// 6) pez caña 2
	Ogre::Entity* pez2 = mSM->createEntity("fish.mesh");
	mPez2Node = mHiloNode->createChildSceneNode();
	mPez2Node->attachObject(pez2);
	mPez2Node->scale(Ogre::Vector3(20, 5, 50));
	mPez2Node->pitch(Ogre::Angle(40));
	mPez2Node->setPosition(Ogre::Vector3(0, 0, -400));

	// 7) pez caña 3
	Ogre::Entity* pez3 = mSM->createEntity("fish.mesh");
	mPez3Node = mHiloNode->createChildSceneNode();
	mPez3Node->attachObject(pez3);
	mPez3Node->scale(Ogre::Vector3(20, 5, 50));
	mPez3Node->pitch(Ogre::Angle(40));
	mPez3Node->setPosition(Ogre::Vector3(0, -10, -500));

	// -- serpiente 
	// 8) cuerpo serpiente
	/*Ogre::Entity* cuerpoSerp = mSM->createEntity("knot.mesh");
	mCuerpoSerpNode = mNode->createChildSceneNode();
	mCuerpoSerpNode->attachObject(cuerpoSerp);
	mCuerpoSerpNode->scale(0.5, 0.5, 0.5);

	// 9) cabeza serpiente
	Ogre::Entity* cabezaSerp = mSM->createEntity("fish.mesh");
	mCabezaSerpNode = mCuerpoSerpNode->createChildSceneNode();
	mCabezaSerpNode->attachObject(cabezaSerp);


	// 10) cola serpiente
	Ogre::Entity* colaSerp = mSM->createEntity("fish.mesh");
	mColaSerpNode = mCuerpoSerpNode->createChildSceneNode();
	mColaSerpNode->attachObject(colaSerp);*/
}

Fisher::~Fisher()
{

}

void Fisher::frameRendered(const Ogre::FrameEvent& evt)
{
	Enemy::frameRendered(evt);

	std::cout << "anim";
	// animacion ?

	mPez1Node->yaw(Ogre::Angle(3));
	mPez2Node->yaw(Ogre::Angle(-4));
	mPez3Node->yaw(Ogre::Angle(5));
}
