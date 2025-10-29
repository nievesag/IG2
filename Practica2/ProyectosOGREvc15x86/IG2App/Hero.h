#pragma once

#include "Character.h"
#include "Constants.h"

class Hero :  public Character
{
public:
	Hero(Vector3 a, SceneNode* b, SceneManager* c, String mesh);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

	int getLives() { return lives; }
	void decreaseLives() { lives--; }

	virtual void stopCharacter() override;

private:
	char lastPressed = ' ';
	int lives = 3;
	Vector3 keyToDirection(char x);

	// estados de animacion
	Ogre::AnimationState* animationStateRunBase;
	Ogre::AnimationState* animationStateRunTop;

	// control de animacion
	bool isRunning = false;
};