#pragma once

#include "IG2Object.h"
#include "Object.h"

class Bomb : public Object
{
	Bomb(Vector3 a, SceneNode* b, SceneManager* c) : Object(a, b, c, true) {}


};

