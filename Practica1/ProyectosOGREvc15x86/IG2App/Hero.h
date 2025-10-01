#pragma once

#include "Character.h"
#include "Constants.h"

class Hero :  public Character
{
public:
	Hero(Vector3 a, SceneNode* b, SceneManager* c, String mesh);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

private:
	char lastPressed = ' ';
	
	Vector3 keyToDirection(char x);

	
};

