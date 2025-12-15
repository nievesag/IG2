#pragma once
#include "Engine.h"
#include "IG2Object.h"
#include "SpaceShip.h"
#include <OgreTimer.h>

class EstrellaChip : public IG2Object
{
public:
	EstrellaChip(Vector3 initPos, SceneNode* node, SceneManager* sceneMng); // le pasas el node vacio
	~EstrellaChip() {}

	void frameRendered(const Ogre::FrameEvent& evt) override;

	void Takeoff();

private:
	// spaceship
	SpaceShip* spaceShip = nullptr;

	// engine
	Engine* engine = nullptr;

	// rockets
	SceneNode* rocketsRack = nullptr;

	float count = 0;

	bool active = false;

	Timer* timer = nullptr;
};
