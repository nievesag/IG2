#pragma once
#include "IG2Object.h"

class Engine : public IG2Object
{
public:
	Engine(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
	~Engine() {}

	void setEngine(bool on);

private:
	Entity* engineEnt = nullptr;
	SceneNode* engineNod = nullptr;

	ParticleSystem* fireSys = nullptr;
};