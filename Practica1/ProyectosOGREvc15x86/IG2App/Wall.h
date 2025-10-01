#pragma once

#include "IG2Object.h"
#include "Object.h"

class Wall : public Object
{
public:
	Wall(Vector3 a, SceneNode* b, SceneManager* c, String mesh) : Object(a, b, c, mesh, false) {}
};