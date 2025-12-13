#include "Rocket.h"
#include "DataSizes.h"

Rocket::Rocket(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	// cube
	rocketCubeEnt = sceneMng->createEntity("cube.mesh");
	rocketCubeNod = node->createChildSceneNode();
	rocketCubeNod->attachObject(rocketCubeEnt);
	rocketCubeNod->scale(DataSizes::ROCKET_CUBE_SIZE);
	// sphere
	rocketSphereEnt = sceneMng->createEntity("sphere.mesh"); 
	rocketSphereNod = rocketCubeNod->createChildSceneNode();
	rocketSphereNod->attachObject(rocketCubeEnt);
	rocketSphereNod->scale(DataSizes::ROCKET_SPHERE_SIZE);

}