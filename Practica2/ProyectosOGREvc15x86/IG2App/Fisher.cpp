#include "Fisher.h"

Fisher::Fisher(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: Enemy(initPos, node, sceneMng, "penguin.mesh")//, mFisherNode(node)
{
	// -- pinguino
	// 1) pinguino
	/*Ogre::Entity* pinguino = mSM->createEntity("penguin.mesh");
	mPenguinNode = mFisherNode->createChildSceneNode();
	mPenguinNode->attachObject(pinguino);*/

	mNode->scale(Vector3(1.1, 1.1, 1.1));

	// 2) peluca pinguino
	Ogre::Entity* peluca = mSM->createEntity("sphere.mesh");
	mPelucaNode = mNode->createChildSceneNode();
	mPelucaNode->attachObject(peluca);
	mPelucaNode->scale(Ogre::Vector3(0.1, 0.07, 0.1));
	mPelucaNode->setPosition(Ogre::Vector3(0, 20, 5));
	peluca->setMaterialName("Suelo");

	// -- caña
	// 3) palo caña
	mPaloEmpt = mNode->createChildSceneNode();
	mPaloEmpt->setPosition(Ogre::Vector3(22, 5, 0));
	mPaloEmpt->pitch(Ogre::Angle(-40));

	Ogre::Entity* palo = mSM->createEntity("cube.mesh");
	mPaloNode = mPaloEmpt->createChildSceneNode();
	mPaloNode->attachObject(palo);
	mPaloNode->scale(Ogre::Vector3(0.05, 0.7, 0.05));
	//mPaloNode->setPosition(Ogre::Vector3(22, 5, 0));

	// 4) hilo 
	mNudoEmpt = mPaloEmpt->createChildSceneNode();
	mNudoEmpt->pitch(Ogre::Angle(40));
	mNudoEmpt->setPosition(Vector3(0, 30, 0));

	mHiloEmpt = mNudoEmpt->createChildSceneNode();
	//mHiloEmpt->pitch(Ogre::Angle(40));
	mHiloEmpt->setPosition(Vector3(0, -20, 0));

	Ogre::Entity* hilo = mSM->createEntity("cube.mesh");
	mHiloNode = mHiloEmpt->createChildSceneNode();
	mHiloNode->attachObject(hilo);
	mHiloNode->scale(Ogre::Vector3(0.02, 0.5, 0.02));
	//mHiloNode->pitch(Ogre::Angle(40));

	// 5) pez caña 1
	Ogre::Entity* pez1 = mSM->createEntity("fish.mesh");
	mPez1Node = mHiloEmpt->createChildSceneNode();
	mPez1Node->attachObject(pez1);
	mPez1Node->scale(Ogre::Vector3(2, 5, 5));
	mPez1Node->setPosition(Ogre::Vector3(0, 5, 0));

	// 6) pez caña 2
	Ogre::Entity* pez2 = mSM->createEntity("fish.mesh");
	mPez2Node = mHiloEmpt->createChildSceneNode();
	mPez2Node->attachObject(pez2);
	mPez2Node->scale(Ogre::Vector3(2, 2, 2));
	mPez2Node->setPosition(Ogre::Vector3(0, -10, 0));

	// 7) pez caña 3
	Ogre::Entity* pez3 = mSM->createEntity("fish.mesh");
	mPez3Node = mHiloEmpt->createChildSceneNode();
	mPez3Node->attachObject(pez3);
	mPez3Node->scale(Ogre::Vector3(2, 2, 5));
	mPez3Node->setPosition(Ogre::Vector3(0, -25, 0));

#pragma region Cana2
	// caña 2
	// 3) palo caña2
	mPaloEmpt2 = mNode->createChildSceneNode();
	mPaloEmpt2->setPosition(Ogre::Vector3(-22, 5, 0));
	mPaloEmpt2->pitch(Ogre::Angle(-40));

	Ogre::Entity* palo2 = mSM->createEntity("cube.mesh");
	mPaloNode2 = mPaloEmpt2->createChildSceneNode();
	mPaloNode2->attachObject(palo2);
	mPaloNode2->scale(Ogre::Vector3(0.05, 0.7, 0.05));
	//mPaloNode->setPosition(Ogre::Vector3(22, 5, 0));

	// 4) hilo 2
	mNudoEmpt2 = mPaloEmpt2->createChildSceneNode();
	mNudoEmpt2->pitch(Ogre::Angle(40));
	mNudoEmpt2->setPosition(Vector3(0, 30, 0));

	mHiloEmpt2 = mNudoEmpt2->createChildSceneNode();
	//mHiloEmpt->pitch(Ogre::Angle(40));
	mHiloEmpt2->setPosition(Vector3(0, -20, 0));

	Ogre::Entity* hilo2 = mSM->createEntity("cube.mesh");
	mHiloNode2 = mHiloEmpt2->createChildSceneNode();
	mHiloNode2->attachObject(hilo2);
	mHiloNode2->scale(Ogre::Vector3(0.02, 0.5, 0.02));
	//mHiloNode->pitch(Ogre::Angle(40));

	// 5) pez caña 1 2
	Ogre::Entity* pez12 = mSM->createEntity("fish.mesh");
	mPez1Node2 = mHiloEmpt2->createChildSceneNode();
	mPez1Node2->attachObject(pez12);
	mPez1Node2->scale(Ogre::Vector3(2, 5, 5));
	mPez1Node2->setPosition(Ogre::Vector3(0, 5, 0));

	// 6) pez caña 2 2
	Ogre::Entity* pez22 = mSM->createEntity("fish.mesh");
	mPez2Node2 = mHiloEmpt2->createChildSceneNode();
	mPez2Node2->attachObject(pez22);
	mPez2Node2->scale(Ogre::Vector3(2, 2, 2));
	mPez2Node2->setPosition(Ogre::Vector3(0, -10, 0));

	// 7) pez caña 3 2
	Ogre::Entity* pez32 = mSM->createEntity("fish.mesh");
	mPez3Node2 = mHiloEmpt2->createChildSceneNode();
	mPez3Node2->attachObject(pez32);
	mPez3Node2->scale(Ogre::Vector3(2, 2, 5));
	mPez3Node2->setPosition(Ogre::Vector3(0, -25, 0));
#pragma endregion


	// -- serpiente 
	mSerpEmpt = mNode->createChildSceneNode();
	mSerpEmpt->setPosition(Ogre::Vector3(0, 32, 3));

	// 8) cuerpo serpiente
	Ogre::Entity* cuerpoSerp = mSM->createEntity("knot.mesh");
	mCuerpoSerpNode = mSerpEmpt->createChildSceneNode();
	mCuerpoSerpNode->attachObject(cuerpoSerp);
	mCuerpoSerpNode->scale(0.2, 0.2, 0.2);

	// 9) cabeza serpiente
	Ogre::Entity* cabezaSerp = mSM->createEntity("fish.mesh");
	mCabezaSerpNode = mSerpEmpt->createChildSceneNode();
	mCabezaSerpNode->attachObject(cabezaSerp);
	mCabezaSerpNode->scale(Ogre::Vector3(4, 3, 6));
	mCabezaSerpNode->setPosition(Vector3(15, 15, 10));
	mCabezaSerpNode->yaw(Angle(80));

	// 10) cola serpiente
	/*Ogre::Entity* colaSerp = mSM->createEntity("fish.mesh");
	mColaSerpNode = mCuerpoSerpNode->createChildSceneNode();
	mColaSerpNode->attachObject(colaSerp);*/
}

Fisher::~Fisher()
{

}

void Fisher::frameRendered(const Ogre::FrameEvent& evt)
{
	Enemy::frameRendered(evt);

	current += evt.timeSinceLastEvent;

	if (current > M_PI * 2)
		current -= M_PI * 2;

	float tilt = cos(current) * 0.25;

	mPaloEmpt->pitch(Angle(tilt));
	mNudoEmpt->pitch(Angle(-tilt));
	mPaloEmpt2->pitch(Angle(-tilt));
	mNudoEmpt2->pitch(Angle(tilt));

	// animacion
	mPez1Node->yaw(Ogre::Angle(3));
	mPez2Node->yaw(Ogre::Angle(-4));
	mPez3Node->yaw(Ogre::Angle(5));
	mPez1Node2->yaw(Ogre::Angle(-3));
	mPez2Node2->yaw(Ogre::Angle(4));
	mPez3Node2->yaw(Ogre::Angle(-5));

	mCabezaSerpNode->yaw(Angle(tilt * 0.5));
}
