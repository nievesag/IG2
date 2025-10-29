#pragma once

#include "Character.h"
#include "Constants.h"

class Enemy : public Character
{
public:
	Enemy(Vector3 a, SceneNode* b, SceneManager* c, String mesh);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

	bool getAlive() { return alive; }

	void setLastPosibleDirection(Vector3 _lastPosibleDirection) 
	{
		lastPosibleDirection = _lastPosibleDirection;
	}

private:
	bool alive = true;
};