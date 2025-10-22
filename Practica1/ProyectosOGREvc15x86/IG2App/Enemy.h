#pragma once

#include "Character.h"
#include "Constants.h"

class Enemy : public Character
{
public:
	Enemy(Vector3 a, SceneNode* b, SceneManager* c, String mesh);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

	bool getAlive() { return alive; }
	Vector3 getRandomDirection();

private:
	bool alive = true;
};