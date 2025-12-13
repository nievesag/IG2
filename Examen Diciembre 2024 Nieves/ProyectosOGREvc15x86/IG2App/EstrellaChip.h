#pragma once
#include "Engine.h"
#include "IG2Object.h"
#include "SpaceShip.h"

class EstrellaChip : public IG2Object
{
public:
	EstrellaChip(Vector3 initPos, SceneNode* node, SceneManager* sceneMng); // le pasas el node vacio
	~EstrellaChip() {}

private:
	// spaceship
	SpaceShip* spaceShip = nullptr;

	// engine
	Engine* engine = nullptr;
};
