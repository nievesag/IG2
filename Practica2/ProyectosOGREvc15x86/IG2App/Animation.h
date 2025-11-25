#pragma once
#include "IG2Object.h"

class Animative : public IG2Object
{
public:
	Animative(Vector3 a, SceneNode* b, SceneManager* c, String mesh);
	~Animative();

	void updateAnime(Real t);

	void setActive(bool f) { mNode->setVisible(f); }

private:
	// -- OBJECTS --
	IG2Object* floor;

	IG2Object* hero;
	Entity* sw1;
	Entity* sw2;

	IG2Object* villain;

	IG2Object* corrodedSphere;

	// -- ANIMATIONS --
	AnimationState* heroMoveAnim;
	AnimationState* villainMoveAnim;
	AnimationState* dance;
	AnimationState* runTop;
	AnimationState* runBot;

	// -- TIMING --
	Real time;
	bool run = false;
	bool sword = false;
};

