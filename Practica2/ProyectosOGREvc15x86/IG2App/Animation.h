#pragma once
#include "IG2Object.h"

class Animative : public IG2Object
{
public:
	Animative(Vector3 a, SceneNode* b, SceneManager* c, String mesh);
	~Animative();

	virtual void frameRendered(const Ogre::FrameEvent& evt);

private:
	// -- OBJECTS --
	IG2Object* floor;

	IG2Object* hero;
	IG2Object* sword1;
	IG2Object* sword2;

	IG2Object* villain;

	// -- ANIMATIONS --
	AnimationState* dance;
	AnimationState* runTop;
	AnimationState* runBot;
};

