#include "Rocket.h"
#include "DataSizes.h"
#include <OgreParticleSystem.h>

Rocket::Rocket(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int i)
	: IG2Object(initPos, node, sceneMng)
{
	// cube
	rocketCubeEnt = sceneMng->createEntity("cube.mesh");
	rocketCubeNod = node->createChildSceneNode();
	rocketCubeNod->attachObject(rocketCubeEnt);
	rocketCubeNod->setPosition(initPos);

	if (i % 2 == 0)
	{
		rocketCubeNod->yaw(Ogre::Angle(DataSizes::ROCKET_DEGREE));
		rocketSys = mSM->createParticleSystem("rocketSys" + std::to_string(i), "RocketPar");
	}
	else
	{
		rocketCubeNod->yaw(Ogre::Angle(-DataSizes::ROCKET_DEGREE));
		rocketSys = mSM->createParticleSystem("rocketSys" + std::to_string(i), "RocketImpar");
	}
	rocketCubeNod->attachObject(rocketSys);
	rocketSys->setEmitting(true);

	rocketCubeNod->_update(false, false);
	rocketCubeNod->setScale(DataSizes::ROCKET_CUBE_SIZE / rocketCubeNod->_getWorldAABB().getSize());
	rocketCubeEnt->setMaterialName("Cubo");

	// sphere
	rocketSphereEnt = sceneMng->createEntity("uv_sphere.mesh"); 
	rocketSphereNod = node->createChildSceneNode();
	rocketSphereNod->attachObject(rocketSphereEnt);
	rocketSphereNod->setPosition({ initPos.x,initPos.y - DataSizes::ROCKET_CUBE_SIZE.y/2, initPos.z });

	rocketSphereNod->_update(false, false);
	rocketSphereNod->setScale(DataSizes::ROCKET_SPHERE_SIZE / rocketSphereNod->_getWorldAABB().getSize());
	rocketSphereEnt->setMaterialName("Esfera");
}