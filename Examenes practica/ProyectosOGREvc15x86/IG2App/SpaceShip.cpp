#include "SpaceShip.h"
#include "DataSizes.h"

SpaceShip::SpaceShip(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	// nodo y entidad
	spaceShipEnt = sceneMng->createEntity("uv_sphere.mesh");
	spaceShipNod = node->createChildSceneNode(); // hijo del nodo vacio padre
	spaceShipNod->attachObject(spaceShipEnt); // los attacheas

	spaceShipNod->setPosition({ 0,DataSizes::SPACESHIP_BODY_SIZE.y/2,0 });
	spaceShipNod->_update(false, false);
	spaceShipNod->setScale(DataSizes::SPACESHIP_BODY_SIZE / spaceShipNod->_getWorldAABB().getSize());
	spaceShipEnt->setMaterialName("Cuerpo");
}