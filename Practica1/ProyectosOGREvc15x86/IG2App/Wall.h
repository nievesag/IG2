#pragma once

#include "IG2Object.h"

class Wall : public IG2Object
{
public:
	Wall(Vector3 a, SceneNode* b, SceneManager* c, String mesh) : IG2Object(a, b, c, mesh) {}
};