#pragma once
#include "IG2Object.h"

class SpaceShip : public IG2Object
{
public:
	SpaceShip(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
	~SpaceShip() {}

private:
	Ogre::Entity* spaceShipEnt = nullptr;
	Ogre::SceneNode* spaceShipNod = nullptr;
};