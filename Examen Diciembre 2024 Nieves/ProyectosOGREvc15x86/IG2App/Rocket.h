#pragma once
#include "IG2Object.h"

class Rocket : public IG2Object
{
public:
	Rocket(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
	~Rocket() {}

private:
	Entity* rocketSphereEnt = nullptr;
	SceneNode* rocketSphereNod = nullptr;

	Entity* rocketCubeEnt = nullptr;
	SceneNode* rocketCubeNod = nullptr;
};

