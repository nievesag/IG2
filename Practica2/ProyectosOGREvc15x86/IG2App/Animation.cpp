#include "Animation.h"
#include "Constants.h"
#include <iostream>

Animative::Animative(Vector3 a, SceneNode* b, SceneManager* c, String mesh) : IG2Object(a, b, c, mesh)
{
	floor = new IG2Object(Vector3(0, 50, 0), mNode->createChildSceneNode("floorNode"), c, "cube.mesh");
	hero = new IG2Object(Vector3(0, 100, 0), mNode->createChildSceneNode("heroAnimNode"), c, "Sinbad.mesh");
	sword1 = new IG2Object(Vector3(-50, 100, 0), mNode->createChildSceneNode("sword1Node"), c, "Sword.mesh");
	sword2 = new IG2Object(Vector3(50, 100, 0), mNode->createChildSceneNode("sword2Node"), c, "Sword.mesh");
	villain = new IG2Object(Vector3(0, 100, -100), mNode->createChildSceneNode("villainAnimNode"), c, "ogrehead.mesh");
	
	floor->setScale(Vector3(5, 0.5, 5));
	hero->setScale(Vector3(5, 5, 5));
	sword1->setScale(Vector3(5, 5, 5));
	sword2->setScale(Vector3(5, 5, 5));
	floor->setMaterialName("Muro");
}

Animative::~Animative()
{ 
}

void Animative::frameRendered(const Ogre::FrameEvent& evt)
{

}
