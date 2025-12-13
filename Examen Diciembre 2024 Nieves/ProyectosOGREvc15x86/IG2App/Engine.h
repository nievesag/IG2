#pragma once
#include "IG2Object.h"

class Engine : public IG2Object
{
public:
	Engine(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
	~Engine() {}

private:
	Entity* engineEnt = nullptr;
	SceneNode* engineNod = nullptr;

};

