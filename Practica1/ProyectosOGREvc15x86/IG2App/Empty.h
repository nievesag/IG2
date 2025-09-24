#pragma once

#include "IG2Object.h"

class Empty : public IG2Object
{
public:
	Empty(Vector3 a, SceneNode* b, SceneManager* c) : IG2Object(a, b, c) {}
};