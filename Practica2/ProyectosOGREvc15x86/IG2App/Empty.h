#pragma once

#include "IG2Object.h"
#include "Object.h"

class Empty : public Object
{
public:
	Empty(Vector3 a, SceneNode* b, SceneManager* c) : Object(a, b, c, true) {}

};