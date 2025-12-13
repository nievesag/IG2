#include "SpaceShip.h"
#include "DataSizes.h"

SpaceShip::SpaceShip(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	// nodo y entidad
	spaceShipEnt = sceneMng->createEntity("sphere.mesh");
	spaceShipNod = node->createChildSceneNode(); // hijo del nodo vacio padre
	spaceShipNod->attachObject(spaceShipEnt); // los attacheas
	spaceShipNod->scale(DataSizes::SPACESHIP_BODY_SIZE);
}