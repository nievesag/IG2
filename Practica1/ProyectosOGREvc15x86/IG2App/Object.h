#pragma once
#include "IG2Object.h"

class Object : public IG2Object
{
public:
	Object(Vector3 a, SceneNode* b, SceneManager* c, String mesh, bool empt) : IG2Object(a, b, c, mesh) {}
	Object(Vector3 a, SceneNode* b, SceneManager* c, bool empt) : IG2Object(a, b, c) {}

	bool isEmpty() { return empty; }

private:
	bool empty;
};

